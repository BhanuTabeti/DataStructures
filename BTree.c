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

int out = 0;
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
		// printf("%d %d\n",ptr->keys[i],ptr->keys[i+1] );

		ptr->keys[i+1] = ptr->keys[i];
		// printf("%d %d\n",ptr->keys[i],ptr->keys[i+1] );
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
	printf("Entered Merging Nodes \nParent Key: %d Left:%d Right :%d\n",ptr->keys[index],prevPtr->keys[0],nextPtr->keys[0]);
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
		ptr->child[i + 1] = ptr->child[i+2];
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
	prevPtr->numkeys++;
	for (int i = prevPtr->numkeys - 1; i > 0; --i)
	{
		prevPtr->keys[i] = prevPtr->keys[i-1];
	}
	prevPtr->keys[0] = ptr->keys[index];

	ptr->keys[index] = leftbro->keys[leftbro->numkeys - 1];

	if (!leftbro->leaf)
	{
		for (int i = prevPtr->numkeys; i >= 0; --i)
		{
			prevPtr->child[i] = prevPtr->child[i-1];
		}
	}

	prevPtr->child[0] = leftbro->child[leftbro->numkeys];
	leftbro->numkeys--;
}

void Borrowfromright(struct btreeNode* ptr,int index,struct btreeNode* nextPtr,struct btreeNode* prevPtr){
	printf("Entered Borrowfromright\nParent Key: %d Left:%d Right :%d\n",ptr->keys[index],nextPtr->keys[0],prevPtr->keys[0] );
	nextPtr->keys[nextPtr->numkeys] = ptr->keys[index];
	nextPtr->numkeys++;
	ptr->keys[index] = prevPtr->keys[0];
	for (int i = 0; i < prevPtr->numkeys - 1; ++i)
	{
		nextPtr->keys[i] = nextPtr->keys[i+1];
	}
	if (!prevPtr->leaf)
	{
		nextPtr->child[nextPtr->numkeys] = prevPtr->child[0];
		for (int i = 0; i < prevPtr->numkeys; ++i)
		{
			prevPtr->child[i] = prevPtr->child[i+1];
		}
	}
	prevPtr->numkeys--;
}

void DeleteNode(int key,struct btreeNode* ptr){
	printf("\n\nEntered DeleteNode : key is %d , ptr of node : %d\n",key,ptr->keys[0] );
	if (ptr->leaf)
	{
		printf("Entered leaf condition : key is %d , ptr of node : %d\n",key,ptr->keys[0] );
		int i = 0;
		while(i < ptr->numkeys && key > ptr->keys[i]){
			i++;
		}
		printf("i is %d\n",i );
		if (key == ptr->keys[i])
		{
			for (; i < ptr->numkeys - 1; ++i)
			{
				ptr->keys[i] = ptr->keys[i+1];
			}
			ptr->numkeys--;
		}
		else{
			printf("Element not in Tree\n");
			return;
		}
	}
	else
	{
		printf("Entered Not Leaf\n");
		int i = 0;
		struct btreeNode* prevPtr = NULL ,*nextPtr = NULL;
		while (i < ptr->numkeys && key > ptr->keys[i]){
			i++;
		}
		printf("i is %d , ptr of node : %d\n",i,ptr->keys[0]);
		if (i < ptr->numkeys && key == ptr->keys[i])
		{
			printf("Entered key present in non leaf node condition\n");
			prevPtr = ptr->child[i];
			nextPtr = ptr->child[i+1];

			if (prevPtr->numkeys > Min_keys)
			{
				printf("Entered Left Child More\n");
				int temp = getLeftMax(prevPtr);
				ptr->keys[i] = temp;
				DeleteNode(temp,prevPtr);
			}
			else if (nextPtr->numkeys > Min_keys)
			{
				printf("Entered Right Child More\n");
				int temp = getRightMax(nextPtr);
				ptr->keys[i] = temp;
				DeleteNode(temp,nextPtr);
			}
			else
			{
				printf("Entered No Child have more\n");
				mergeChildren(ptr,i,prevPtr,nextPtr);
				DeleteNode(key,prevPtr);
			}
		}
		else{
			printf("Entered key not present in non leaf node condition\n");
			prevPtr = ptr->child[i];
			struct btreeNode* leftbro = NULL;
			if (i<ptr->numkeys)
			{
				// printf("Entered key not present in last child\n");
				nextPtr =ptr->child[i+1];
			}
			if (i > 0)
			{
				// printf("Entered key not present in first child\n");
				leftbro = ptr->child[i - 1];
			}

			if (Min_keys == prevPtr->numkeys)
			{
				printf("Entered Child contains Exact Min_keys\n");
				if (leftbro != NULL && leftbro->numkeys > Min_keys)
				{
					printf("Entered key not present in first child && left child more than minimum\n");
					Borrowfromleft(ptr,i-1,leftbro,prevPtr);
				}
				else if (nextPtr != NULL && nextPtr->numkeys > Min_keys)
				{
					printf("Entered key not present in last child && Right child more than minimum\n");
					Borrowfromright(ptr,i,prevPtr,nextPtr);
				}
				else if (leftbro != NULL)
				{
					printf("Entered key not present in first child && left child not more than minimum\n");
					printf("Merging %d %d nodes\n",leftbro->keys[0],prevPtr->keys[0] );
					mergeChildren(ptr,i-1,leftbro,prevPtr);
					prevPtr = leftbro;
				}
				else{
					printf("Entered key not present in last child && left child not more than minimum\n");
					printf("Merging %d %d nodes\n",prevPtr->keys[0],nextPtr->keys[0] );
					mergeChildren(ptr,i,prevPtr,nextPtr);
				}
			}
			printf("Recursing DeleteNode!\n\n");
				out = 0;
				display(root,0);
				printf("%d\n",out );
			DeleteNode(key,prevPtr);
		}

	}
}

void Delete(){
	int key;
	printf("Enter key to Delete: ");
	scanf("%d",&key);
	printf("--------------------\nDeletion Process\n");
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
				out = 0;
				display(root,0);
				printf("No of Current Nodes in Tree : %d\n",out );
				break;
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