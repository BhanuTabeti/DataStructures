#include <stdio.h>
#include <stdlib.h>


int FindElem(int arr[],int key){
	int temp = key;
	while(arr[temp]!= temp){
		temp = arr[temp];
	}
	return temp;
}
void FindSet(int arr[]){
	printf("Enter Element to Find:");
	int key;
	scanf("%d",&key);
	
	printf("%d is in %d Set\n",key,FindElem(arr,key) );

}


void Union(int arr[]){
	printf("Enter Elements to Union(x y): ");
	int x,y;
	scanf("%d",&x);
	scanf("%d",&y);
	int xset = FindElem(arr,x);
	int yset = FindElem(arr,y);
	if (xset != yset)
	{
		arr[xset] = yset;
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
	int arr[len+1];
	printf("Enter %d Elements: ",len);
	for (int i = 0; i <= len; ++i) arr[i] = i;

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