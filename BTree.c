#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define degree 3
#define Min_keys degree - 1
#define Max_keys 2*degree - 1

struct btreeNode
{
	int numkeys;
	int keys[Max_keys];
	bool leaf;
	struct btreeNode* child[Max_keys+1];
};

// int out = 0;
struct btreeNode* root = NULL;

void CreateEmptyTree(){
	struct btreeNode* ptr = (struct btreeNode*)malloc(sizeof(struct btreeNode));
	ptr->numkeys = 0;
	ptr->leaf = true;
	root = ptr;
	return;
}

void display(struct btreeNode *ptr, int blanks){
    if (ptr)
    {
        int i;
        for(i=1; i<=blanks; i++)
            printf(" ");
        for (i=0; i < ptr->numkeys; i++){
        	out++;
            printf("%d ",ptr->keys[i]);
        }
        printf("\n");
        for (i=0; i <= ptr->numkeys; i++)
            display(ptr->child[i], blanks+10);
    }
}

void SplitChild(struct btreeNode* ptr,int pos){
	struct btreeNode* old = ptr->child[pos];
	struct btreeNode* new = (struct btreeNode*)malloc(sizeof(struct btreeNode));

	new->leaf = old->leaf;
	// display(ptr,0);

	// Pushing Middle Element to Top
	for (int i = ptr->numkeys - 1; i >=pos; --i)
	{
		printf("%d %d\n",ptr->keys[i],ptr->keys[i+1] );

		ptr->keys[i+1] = ptr->keys[i];
		printf("%d %d\n",ptr->keys[i],ptr->keys[i+1] );
	}

	ptr->keys[pos] = old->keys[Min_keys];

	// Updating Value of new pointer
	for (int i = ptr->numkeys ; i >=pos + 1; --i)
	{
		ptr->child[i+1] = ptr->child[i];
	}

	ptr->child[pos+1] = new;

	ptr->numkeys++;
	
	// Coping keys from old to new
	for (int i = Min_keys+1,j=0; i < Max_keys; ++i)
	{
		new->keys[j++] = old->keys[i]; 
	}

	// Coping child pointers from old to new
	if (!(new->leaf))
		for (int i = degree,j = 0; i < Max_keys + 1; ++i)
		{
			new->child[j++] = old->child[i];
		}
	new->numkeys = Min_keys;
	old->numkeys = Min_keys;
	// display(ptr,0);
	return;
}

void InsertinNode(struct btreeNode* ptr,int key){
	// display(ptr,0);
	if (ptr->leaf)
	{
		int i = ptr->numkeys-1;
		while(i>=0 && key < ptr->keys[i]){
			ptr->keys[i+1] = ptr->keys[i];
			i--;
		}
		ptr->keys[++i] = key;
		ptr->numkeys++;
	}
	else
	{
		int pos = ptr->numkeys-1;
		while(pos >= 0 && key<ptr->keys[pos]){
			pos--;
		}
		pos++;
		// printf("%d\n",pos );
		if (ptr->child[pos]->numkeys == Max_keys)
		{
			SplitChild(ptr,pos);
			if (key > ptr->keys[pos])
				pos++;
		}
		InsertinNode(ptr->child[pos],key);
	}
}

void Insert(){
	int key;
	printf("Enter the key: ");
	scanf("%d",&key);

	if (root == NULL)
		CreateEmptyTree();

	if (root->numkeys == Max_keys)
	{
		struct btreeNode* ptr = (struct btreeNode*)malloc(sizeof(struct btreeNode));
		ptr->numkeys = 0;
		ptr->leaf = false;
		ptr->child[0] = root;
		root = ptr;
		SplitChild(root,0);
	}
	
	InsertinNode(root,key);
}

struct btreeNode* FindNode(int key,struct btreeNode* ptr){
	int i = 0;
	while((i < ptr->numkeys) && (key>ptr->keys[i])){
		i++;
	}
	if (key == ptr->keys[i])
	{
		return ptr;
	}
	else if (!ptr->leaf)
	{
		return FindNode(key,ptr->child[i]);
	}
	else
	{
		return NULL;
	}
}

void Search(){
	int key;
	printf("Enter key to find: ");
	scanf("%d",&key);

	if (FindNode(key,root) == NULL)
	{
		printf("Not Found\n");
	}
	else
	{
		printf("Found\n");
	}
}

int getLeftMax(struct btreeNode* ptr){
	if (ptr->leaf)
	{
		return ptr->keys[ptr->numkeys - 1];
	}
	else
		return getLeftMax(ptr->child[ptr->numkeys]);
}

int getRightMax(struct btreeNode* ptr){
	if (ptr->leaf)
	{
		return ptr->keys[0];
	}
	else
		return getRightMax(ptr->child[0]);
}

void mergeChildren(struct btreeNode* ptr,int index,struct btreeNode* prevPtr,struct btreeNode* nextPtr){
	prevPtr->keys[Min_keys] = ptr->keys[index];
	for (int i = Min_keys + 1,j = 0; i < Max_keys; ++i)
	{
		prevPtr->keys[i] = nextPtr->keys[j++];
	}

	if (!nextPtr->leaf)
	{
		for (int i = Min_keys + 1, j = 0; i < Max_keys + 1; ++i)
		{
			prevPtr->child[i] = nextPtr->child[j++];
		}
	}

	for (int i = index; i < ptr->numkeys; ++i)
	{
		ptr->keys[i] = ptr->keys[i + 1];
		ptr->child[i+1] = ptr->child[i+2];
	}

	ptr->numkeys--;
	if (ptr->numkeys == 0 && ptr == root)
	{
		root = prevPtr; 
	}
	prevPtr->numkeys = Max_keys;
	free(nextPtr);
	return;
}

void Borrowfromleft(struct btreeNode* ptr,int index,struct btreeNode* leftbro,struct btreeNode* prevPtr){
	for (int i = Min_keys - 1; i >= 0; --i)
	{
		prevPtr->keys[i] = prevPtr->keys[i-1];
	}
	prevPtr->keys[0] = ptr->keys[index];
	prevPtr->numkeys++;

	ptr->keys[index] = leftbro->keys[leftbro->numkeys - 1];

	if (!leftbro->leaf)
	{
		for (int i = Min_keys; i >= 0; --i)
		{
			prevPtr->child[i] = prevPtr->child[i-1];
		}
	}

	prevPtr->child[0] = leftbro->child[leftbro->numkeys];
	leftbro->numkeys--;
}

void Borrowfromright(struct btreeNode* ptr,int index,struct btreeNode* prevPtr,struct btreeNode* nextPtr){
	prevPtr->keys[prevPtr->numkeys] = ptr->keys[index];
	prevPtr->numkeys++;
	ptr->keys[index] = nextPtr->keys[0];
	for (int i = 0; i < nextPtr->numkeys; ++i)
	{
		nextPtr->keys[i] = nextPtr->keys[i+1];
	}
	if (!nextPtr->leaf)
	{
		prevPtr->child[prevPtr->numkeys] = nextPtr->child[0];
		for (int i = 0; i < nextPtr->numkeys + 1; ++i)
		{
			nextPtr->child[i] = nextPtr->child[i+1];
		}
	}
	nextPtr->numkeys--;
}

void DeleteNode(int key,struct btreeNode* ptr){
	if (ptr->leaf)
	{
		int i = 0;
		while(i < ptr->numkeys && key > ptr->keys[i]){
			i++;
		}
		if (key == ptr->keys[i])
		{
			for (; i < ptr->numkeys; ++i)
			{
				ptr->keys[i] = ptr->keys[i+1];
			}
			ptr->numkeys--;
		}
		else
			printf("Element not in Tree\n");
	}
	else
	{
		int i = 0;
		struct btreeNode* prevPtr = NULL ,*nextPtr = NULL;
		while (i < ptr->numkeys && key > ptr->keys[i]){
			i++;
		}
		if (i < ptr->numkeys && key == ptr->keys[i])
		{
			prevPtr = ptr->child[i];
			nextPtr = ptr->child[i+1];

			if (prevPtr->numkeys > Min_keys)
			{
				int temp = getLeftMax(prevPtr);
				ptr->keys[i] = temp;
				DeleteNode(temp,prevPtr);
			}
			else if (nextPtr->numkeys > Min_keys)
			{
				int temp = getRightMax(nextPtr);
				ptr->keys[i] = temp;
				DeleteNode(temp,nextPtr);
			}
			else
			{
				mergeChildren(ptr,i,prevPtr,nextPtr);
				DeleteNode(key,prevPtr);
			}
		}
		else{
			prevPtr = ptr->child[i];
			struct btreeNode* leftbro = NULL;
			if (i<ptr->numkeys)
			{
				nextPtr =ptr->child[i+1];
			}
			if (i > 0)
			{
				leftbro = ptr->child[i - 1];
			}

			if (Min_keys == prevPtr->numkeys)
			{
				if (leftbro != NULL && leftbro->numkeys > Min_keys)
				{
					Borrowfromleft(ptr,i-1,leftbro,prevPtr);
				}
				else if (nextPtr != NULL && nextPtr->numkeys > Min_keys)
				{
					Borrowfromright(ptr,i,prevPtr,nextPtr);
				}
				else if (leftbro != NULL)
				{
					mergeChildren(root,i-1,leftbro,prevPtr);
					prevPtr = leftbro;
				}
				else
					mergeChildren(root,i,prevPtr,nextPtr);
			}
			DeleteNode(key,prevPtr);
		}

	}
}

void Delete(){
	int key;
	printf("Enter key to Delete: ");
	scanf("%d",&key);
	DeleteNode(key,root);
}

int main(int argc, char const *argv[])
{
	int opt;
	do{
		// system("clear");
		// printtree();
		printf("Menu\n1.Insert\n2.Search\n3.Delete\n4.Display\n0.Exit\nEnter your choice: ");
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
			case 4 :
				display(root,0);
			case 0:
				break;
			default:
				printf("Retry\n");
				break;
		}
		// Insert();
		// out = 0;
		// display(root,0);
		// printf("Total: %d\n",out );
		// system("clear");
		
	} while (opt != 0);
	return 0;
}