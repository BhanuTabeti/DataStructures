#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node{
	int value;
	int degree;
	struct node *parent;
	struct node *child;
	struct node *sibling;
};

struct heap{
	struct node *head;
};

struct heap *root = NULL;

struct node *reverselist(struct node *head){
	struct node* prev = NULL;
	struct node* curr = head;
	struct node* next;
	while(curr){
		next = curr->sibling;
		curr->sibling = prev;
		prev = curr;
		curr = next;
	}
	return prev;
}

struct heap *makeBinomialHeap(){
	struct heap *temp = (struct heap *)malloc(sizeof(struct heap));
	temp->head = NULL;
	return temp;
}

struct node *binomialHeapMerge(struct heap *H1,struct heap *H2){
	struct node *head1 = H1->head,*head2 = H2->head,*head;

	if (head1 == NULL && head2 != NULL)
		return head2;
	else if (head1 != NULL && head2 == NULL)
		return head1;
	else if (head1 == NULL && head2 == NULL)
		return NULL;
	else{
		if (head1->degree > head2->degree){
			head = head2;
			head2 = head2->sibling;
		}
		else{
			head = head1;
			head1 = head1->sibling;
		}
	}

	struct node *temp = head;

	while(head1!=NULL && head2 != NULL) {
		if (head1->degree < head2->degree) {
			temp->sibling = head1;
			head1 = head1->sibling;
		}
		else {
			temp->sibling = head2;
			head2 = head2->sibling;
		}
		temp = temp->sibling;
	}

	if (head1 != NULL)	temp->sibling = head1;
	else if (head2 != NULL)	temp->sibling = head2;
/*
	temp = head;
	while(temp != NULL){
		printf("(%d %d) ",temp->value,temp->degree );
		temp = temp->sibling;
	}
	printf("\n");*/
	return head;
}

void binomialLink(struct node *A,struct node *B){
	A->parent = B;
	A->sibling = B->child;
	B->child = A;
	B->degree++;
}

struct heap *binomialHeapUnion(struct heap *H1,struct heap *H2){
	struct heap *H = makeBinomialHeap();
	struct node *prevx, *nextx, *x,*temp; 

	H->head = binomialHeapMerge(H1,H2);
	free(H1);free(H2);

	if (H->head == NULL) return H;

	prevx = NULL;
	x	  = H->head;
	nextx = x->sibling;

	while(nextx != NULL){
		if ((x->degree != nextx->degree) || (nextx->sibling != NULL && nextx->sibling->degree == x->degree))
		{
			prevx = x;
			x = nextx;
		}
		else if (x->value <= nextx->value)
		{
			x->sibling = nextx->sibling;
			binomialLink(nextx,x);
		}
		else
		{
			if (prevx == NULL) H->head = nextx;
			else prevx->sibling = nextx;
			binomialLink(x,nextx);
			x = nextx;
		}
		nextx = x->sibling;
	}
	return H;
}

void Insert(){
	int key;
	printf("Enter value to Insert: ");
	scanf("%d",&key);
	if (root == NULL)
		root = makeBinomialHeap();

	struct heap *temp = makeBinomialHeap();
	struct node *x = (struct node *)malloc(sizeof(struct node));
	x->value	= key;
	x->degree	= 1;
	x->parent	= NULL;
	x->child	= NULL;
	x->sibling	= NULL;
	temp->head = x;

	root = binomialHeapUnion(root,temp);
}

void PrintHeap(struct heap *H){
	struct node *head = H->head;
	if (head == NULL)
		printf("Empty heap");
	while(head != NULL){
		printf("(%d %d) ",head->value,head->degree );
		head = head->sibling;
	}
	printf("\n");
}

void DeleteMin(){
	struct node* xprev = NULL,*x = root->head,*ptr = root->head,*prevptr = NULL,*nextx;
	int min = ptr->value;
	while(ptr){
		if (min > ptr->value)
		{
			x = ptr;
			xprev = prevptr;
			min = x->value;
		}
		prevptr = ptr;
		ptr = ptr->sibling;
	}
	// printf("1\n");
	if (xprev != NULL)
	{
		xprev->sibling = x->sibling;
	}
	else
		root->head = x->sibling;
	// printf("2\n");
	struct heap *H1 = makeBinomialHeap();

	H1->head = reverselist(x->child);

	H1 = binomialHeapUnion(root,H1);

	xprev = NULL;
	x	  = H1->head;
	nextx = x->sibling;

	while(nextx != NULL){
		if ((x->degree != nextx->degree) || (nextx->sibling != NULL && nextx->sibling->degree == x->degree))
		{
			xprev = x;
			x = nextx;
		}
		else if (x->value <= nextx->value)
		{
			x->sibling = nextx->sibling;
			binomialLink(nextx,x);
		}
		else
		{
			if (xprev == NULL) H1->head = nextx;
			else xprev->sibling = nextx;
			binomialLink(x,nextx);
			x = nextx;
		}
		nextx = x->sibling;
	}

	root = H1;
}

void FindMin(){
	struct node *ptr = root->head;
	int min = ptr->value;
	while(ptr){
		if (min > ptr->value)
		{
			min = ptr->value;
		}
		ptr = ptr->sibling;
	}
	printf("Min : %d\n",min );
}

int main(int argc, char const *argv[])
{
	int opt;
	do{
		printf("\n............\nMenu\n1.Insert\n2.Get Min\n3.Delete Min\n4.PrintHeads\n0.Exit\nEnter your choice: ");
		scanf("%d",&opt);
		switch(opt){
			case 1:
				Insert();
				break;
			case 2:
				FindMin();
				break;
			case 3:
				DeleteMin();
				break;
			case 4:
				printf("\n\nPrinting Heads \n");		
				PrintHeap(root);
				break;
			case 0:
				break;
			default:
				printf("Retry\n");
				break;
		}

	} while (opt != 0);
	return 0;
}
