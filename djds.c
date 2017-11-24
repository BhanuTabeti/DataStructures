#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
	int rep;
	int rank;
}node;

int FindElem(node arr[],int key){
	int temp = key;
	while(arr[temp].rep != temp){
		temp = arr[temp].rep;
	}
	return temp;
}

void FindSet(node arr[]){
	printf("Enter Element to Find:");
	int key;
	scanf("%d",&key);
	
	printf("%d is in %d Set\n",key,FindElem(arr,key) );

}


void Union(node arr[]){
	printf("Enter Elements to Union(x y): ");
	int x,y;
	scanf("%d",&x);
	scanf("%d",&y);
	int xset = FindElem(arr,x);
	int yset = FindElem(arr,y);
	if (xset != yset)
	{
		if (arr[xset].rank > arr[yset].rank)
		{
			arr[yset].rep = xset;
			arr[yset].rank += arr[xset].rank;
		}
		else{
			arr[xset].rep = yset;
			arr[xset].rank += arr[yset].rank;
		}
	}
	else
		printf("Both are in same Set\n");
}

int main(int argc, char const *argv[])
{
	printf("Initializing DisJoint Set\n");
	printf("No of Vetices: ");
	int len;
	scanf("%d",&len);
	node arr[len+1];
	printf("Enter %d Elements: ",len);
	for (int i = 0; i <= len; ++i) {
		arr[i].rep = i;
		arr[i].rank = 1;
	}

	int opt;
	do{
		printf("\n-------------\nMenu\n1.Find Set\n2.Union Set\n0.Exit\nEnter your choice: ");
		scanf("%d",&opt);
		switch(opt){
			case 1:
				FindSet(arr);
				break;
			case 2:
				Union(arr);
				break;
			case 0:
				break;
			default:
				printf("Retry\n");
				break;
		}
		// PrintHeap();
	} while (opt != 0);
	return 0;
}