#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	char* name;
	char* clg;
	char* Gender;
	struct node* next;	
};

struct node* Head = NULL;

void Insert(void){
	struct node* ptr = (struct node*)malloc(sizeof(struct node));
	char* name = (char*)malloc(10*sizeof(char));
	char* clg  = (char*)malloc(10*sizeof(char));
	char* Gender  = (char*)malloc(10*sizeof(char));

	printf("\nEnter Name(10 char limit): "); 
	scanf("%s",name);
	printf("Enter College Name(10 char limit): ");
	scanf("%s",clg);
	printf("Enter Gender: ");
	scanf("%s",Gender);
	ptr->name = name;
	ptr->clg = clg;
	ptr->Gender = Gender;
	ptr->next = Head;
	Head = ptr;
}

void Del(struct node* del,struct node* delprev){
	if (del == Head)
	{
		Head = Head->next;
		free(del);
	}
	else{
		delprev->next = del->next;
		free(del);
	}
}

void Delete(void){
	char* name = (char*)malloc(10*sizeof(char));
	printf("Enter the name to Delete : ");
	scanf("%s",name);
	struct node* ptr = Head;
	struct node* prev = NULL;
	while(ptr != NULL){
		if (strcmp(name,ptr->name) == 0)
		{
			Del(ptr,prev);
			break;
		}
		else{
			prev = ptr;
			ptr = ptr->next;

		}
	}
}

void Search(void){
	char* name = (char*)malloc(10*sizeof(char));
	printf("Enter the name to Search : ");
	scanf("%s",name);
	struct node* ptr = Head;
	struct node* prev = NULL;
	while(ptr != NULL){
		if (strcmp(name,ptr->name) == 0)
		{
			printf("Found\n");
			return;
		}
		else{
			prev = ptr;
			ptr = ptr->next;
		}
	}
	printf("Not Found\n");
}
void printlist(void){
	struct node* ptr =Head;
	while(ptr != NULL){
		printf("%s %s %s\n",ptr->name,ptr->clg,ptr->Gender );
		ptr = ptr->next;
	}
}

int main(int argc, char const *argv[])
{
	int opt;
	do
	{
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
		printlist();
	} while (opt != 0);
	return 0;
}