#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define degree 4
#define Min_keys degree - 1
#define Max_keys 2*degree - 1

struct btreeNode
{
	int numkeys;
	int keys[Max_keys];
	bool leaf;
	struct btreeNode* child[Max_keys+1];
};

struct btreeNode* root = NULL;

void CreateEmptyTree(){
	struct btreeNode* ptr = (struct btreeNode*)malloc(sizeof(struct btreeNode));
	ptr->numkeys = 0;
	ptr->leaf = true;
	root = ptr;
	return;
}

void SplitChild(struct btreeNode* ptr,int pos){
	struct btreeNode* old = ptr->child[pos];
	struct btreeNode* new = (struct btreeNode*)malloc(sizeof(struct btreeNode));

	new->leaf = old->leaf;

	// Pushing Middle Element to Top
	for (int i = ptr->numkeys - 1; i > pos; --i)
	{
		ptr->keys[i+1] = ptr->keys[i];
	}

	ptr->keys[pos] = old->keys[Min_keys];

	// Updating Value of new pointer
	for (int i = ptr->numkeys ; i > pos + 1; ++i)
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
	if (!new->leaf)
		for (int i = degree+1,j = 0; i < Max_keys + 1; ++i)
		{
			new->child[j] = old->child[i];
		}

	new->numkeys = Min_keys;
	old->numkeys = Min_keys;

	return;
}

void InsertinNode(struct btreeNode* ptr,int key){
	if (ptr->leaf)
	{
		int i = ptr->numkeys;
		while(i>=0 && key < ptr->keys[i]){
			i--;
		}
		ptr->keys[i] = key;
		ptr->numkeys++;
	}
	else
	{
		int pos = 0;
		int len = ptr->numkeys;
		while(pos < len && key<ptr->keys[pos]){
			pos++;
		}
		pos++;
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


void display(struct btreeNode *ptr, int blanks)
{
    if (ptr)
    {
        int i;
        for(i=1; i<=blanks; i++)
            printf(" ");
        for (i=0; i < ptr->numkeys; i++)
            printf("%d ",ptr->keys[i]);
        printf("\n");
        for (i=0; i <= ptr->numkeys; i++)
            display(ptr->child[i], blanks+10);
    }/*End of if*/
}/*End of display()*/

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
				// Search();
				break;
			case 3:
				// Delete();
				break;
			case 4 :
				display(root,0);
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