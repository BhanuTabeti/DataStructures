#include <stdio.h>
#include <stdlib.h>

#define ANSI_RED "\x1b[31m"
#define ANSI_CLEAR "\x1b[0m"
#define ANSI_BLACK "\x1b[34m"

struct node
{
	int name;
	char color;
	struct node* left;
	struct node* right;
	struct node* p;
};

struct node* NIL = NULL;
struct node* Root = NULL;

void printRed(int k){
	printf(ANSI_RED "%d" ANSI_CLEAR,k );
}

void printBlack(int k){
	printf(ANSI_BLACK "%d" ANSI_CLEAR,k );
}

void print2DUtil(struct node *root,int space){
	
	/*if (Head == NULL)
	{
		printf("Empty Tree 🙃\n");
	}*/
    // Base case
    if (root == NULL){
        return;
    }
 
    // Increase distance between levels
    space += 4;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = 4; i < space; i++)
        printf(" ");
    // printf("%d\n", root->name);
    switch(root->color){
    	case 'r':
    		printRed(root->name);
    		printf("\n");
    		break;
    	case 'b':
    		printBlack(root->name);
    		printf("\n");
    }
 
    // Process left child
    print2DUtil(root->left, space);
}

void printtree(){
	// printf("Printing Tree.....\n");
	print2DUtil(Root,0);
}

struct node* getNode(struct node* Head,int name){
	struct node* ptr = Head;
	while(1){
		if (name < ptr->name)
		{
			if (ptr->left == NULL)
				return ptr;
			else	
				ptr = ptr->left;
		}
		else{
			if (ptr->right == NULL)
				return ptr;
			else
				ptr = ptr->right;
		}
	}
	return ptr;
}

struct node* parent(struct node* ptr){
	return ptr->p;
}

struct node* uncle(struct node* ptr){
	return (parent(ptr) == parent(parent(ptr))->left) ? parent(parent(ptr))->right : parent(parent(ptr))->left;
}

void RotateLeft(struct node* ptr){
    if (parent(ptr) != NIL)
		if (parent(ptr)->left == ptr)
			parent(ptr)->left = ptr->right;
		else
			parent(ptr)->right = ptr->right;
	ptr->right->p = ptr->p;
	ptr->p = ptr->right;
	ptr->right = ptr->right->left;
	ptr->p->left = ptr;
	if (ptr->right != NIL)
	{
		ptr->right->p = ptr;
	}
}

void RotateRight(struct node* ptr){
	if (parent(ptr) != NIL)
		if (parent(ptr)->left == ptr)
			parent(ptr)->left = ptr->left;
		else
			parent(ptr)->right = ptr->left;

	ptr->left->p = ptr->p;
	ptr->p = ptr->left;
	ptr->left = ptr->left->right;
	ptr->p->right = ptr;

	if (ptr->left != NIL)
		ptr->left->p = ptr;

}

void FixTree_1(struct node* ptr){
	ptr->color = 'b';
}

struct node* FixTree_2(struct node* ptr){
	parent(ptr)->color = 'b';
	uncle(ptr)->color = 'b';
	parent(parent(ptr))->color = 'r';
	return parent(parent(ptr));
}

void FixTree_3(struct node* ptr){
	if (parent(parent(ptr))->left != NIL && parent(parent(ptr))->left->right == ptr)
	{
		RotateLeft(parent(ptr));
		ptr = ptr->left;
	}
	else if (parent(parent(ptr))->right != NIL && parent(parent(ptr))->right->left == ptr)
	{
		RotateRight(parent(ptr));
		ptr = ptr->right;
	}
	ptr->p->color = 'b';
	ptr->p->p->color = 'r';
	if (ptr == ptr->p->left){
		RotateRight(ptr->p->p);
	}
	else{
		RotateLeft(ptr->p->p);
	}
}

void FixTree(struct node* ptr){
	while(1){
		if (ptr->p == NIL){
			FixTree_1(ptr); 	// Root Node
			break;
		}
		else if (parent(ptr)->color == 'r')
			if (uncle(ptr) != NIL && uncle(ptr)->color == 'r'){
				ptr = FixTree_2(ptr);
				continue;
			}
			else
			{
				FixTree_3(ptr);
				break;
			}
		else
			break;
	}	

}

void Insert(){
	struct node* ptr = (struct node*)malloc(sizeof(struct node));
	int name;
	printf("Enter Name:");
	scanf("%d",&name);
	
	ptr->name   =  name;
	ptr->left 	=  NIL;
	ptr->right  =  NIL;
	ptr->color 	=  'r';

	if (Root == NULL)
	{
		Root = ptr;
		ptr->p = NIL;
	}
	else
	{
		struct node* loc = getNode(Root,name);
		ptr->p = loc;
		if (name > loc->name)
		{
			loc->right = ptr;
		}
		else if(name < loc->name){
			loc->left = ptr;
		}
		else
			loc->right = ptr;
	}
	FixTree(ptr);

	Root = ptr;
	while(parent(Root) != NIL){
		Root = parent(Root);
	}
}

int main(int argc, char const *argv[])
{
	int opt;
	do{
		printf("Menu\n1.Insert\n2.PrintTree\n0.Exit\nEnter your choice: ");
		scanf("%d",&opt);
		switch(opt){
			case 1:
				Insert();
				break;
			case 2:
				printtree();
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
