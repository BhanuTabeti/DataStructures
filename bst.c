#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct node
{
	int name;
	// char* clg;
	// char* Gender;
	struct node* p;
	struct node* right;
	struct node* left;
};

struct node* Head  = NULL;

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

void print2DUtil(struct node *root,int space)
{	
	if (Head == NULL)
	{
		printf("Empty Tree 🙃\n");
	}
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
    printf("%d\n", root->name);
 
    // Process left child
    print2DUtil(root->left, space);
}

void printtree(){
	printf("Printing Tree.....\n");
	print2DUtil(Head,0);
}

void Insert(){
	struct node* ptr = (struct node*)malloc(sizeof(struct node));
	int name;
	printf("Enter Name:");
	scanf("%d",&name);
	
	ptr->name   =  name;
	ptr->left 	=  NULL;
	ptr->right  =  NULL;

	if (Head == NULL)
	{
		Head = ptr;
		ptr->p = NULL;
	}
	else
	{
		struct node* loc = getNode(Head,name);
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
}

struct node* FindNode(int key){
	struct node* ptr = Head;
	if (Head == NULL)
	{
		return NULL;
	}
	while(1){
		if (ptr->name == key)
		{
			// printf("Found!\n");
			return ptr;
		}
		else if (key < ptr->name)
		{
			if (ptr->left == NULL)
			{
				// printf("Not Found!\n");
				return NULL;
			}
			else
				ptr = ptr->left;
		}
		else
		{
			if (ptr->right == NULL)
			{
				// printf("Not Found\n");
				return NULL;
			}
			else
				ptr = ptr->right;
		}
	}
}

void Search(){
	printf("Enter Name: ");
	int key;
	scanf("%d",&key);
	if (FindNode(key) != NULL)
		printf("Found!\n");
	else
		printf("Not Found!\n");
}


void Delete(){
	printf("Enter Name To Delete: ");
	int key;
	scanf("%d",&key);
	struct node* ptr = FindNode(key);
	struct node* ptrdel;
	// printf("hi\n");
	if (ptr == NULL)
	{
		printf("Element Doesnt exit!\n");
		return;
	}

	if (ptr->left == NULL)
	{
		if (ptr == Head){
			Head = ptr->right;
		}
		else{
			if(ptr->right != NULL)
				ptr->right->p = ptr->p;
			if (ptr->p->left == ptr){
				ptr->p->left = ptr->right;
			}
			else{
				ptr->p->right = ptr->right;
			}
		}
		free(ptr);
	}
	else if (ptr->right == NULL)
	{
		if (ptr == Head)
			Head = ptr->left;
		else{
			ptr->left->p = ptr->p;
			if (ptr->p->left == ptr)
				ptr->p->left = ptr->left;
			else
				ptr->p->right = ptr->left;
		}
		free(ptr);
	}
	else
	{
			ptrdel = getNode(ptr->right,INT_MIN);			
			ptr->name = ptrdel->name;
			if (ptrdel->p->left == ptrdel)
			{
				if (ptrdel->right != NULL)
					ptrdel->right->p = ptrdel->p;
				ptrdel->p->left = ptrdel->right;
			}
			else{
				if (ptrdel->right != NULL)
				{
					ptrdel->p->right = ptrdel->right;
					ptrdel->right->p = ptrdel->p;
				}
				else
				{
					ptrdel->p->right = ptrdel->right;
				}
			}
			free(ptrdel);
	}
	return;
}
int main(int argc, char const *argv[])
{
	int opt;
	do{
		system("clear");
		printtree();
		printf("Menu\n1.Insert\n2.Search\n3.Delete\n0.Exit\nEnter your choice: ");
		scanf("%d",&opt);
		switch(opt){
			case 1:
				Insert();
				break;
			case 2:
				Search();
				break;
			case 3:
				Delete();
				break;
			case 0:
				break;
			default:
				printf("Retry\n");
				break;
		}
		// system("clear");
		
	} while (opt != 0);
	return 0;
}