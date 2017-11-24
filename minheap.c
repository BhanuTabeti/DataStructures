#include <stdio.h>
#include <stdlib.h>
int len,size = 0,*heap;

void swap(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}

void heapify(int i){
	while (heap[i/2] > heap[i])
	{
		swap(&heap[i],&heap[i/2]);
		i /= 2; 
	}
}

void Insert(){
	if (size == len)
	{
		printf("Heap is Full\nCannot Add AnyMore\n");
		return;
	}
	int loc;
	printf("Enter No: ");
	scanf("%d",&heap[++size]);
	heapify(size);
	return;
}

void FindMin(){
	printf("Min : %d\n",heap[1] );
	return;
}

void PrintHeap(){
	for (int i = 0; i < size; ++i)
	{
		printf("%d ",heap[i+1] );
	}
	printf("\n");
}
void DeleteMin(){
	if (size == 0)
	{
		printf("Nothing to Delete\n");
		return;
	}
	// swap(1,size--);
	// heap[1] = heap[size--];
	// printf("%d %d\n",heap[1],heap[size] );
	swap(&heap[1],&heap[size--]);
	int i = 1;
	// printf("%d %d\n",heap[1],heap[size] );
	while((heap[i] > heap[2*i]) || (heap[i] > heap[2*i + 1]) && (i <= len/2)){
		if (size == 2*i && (heap[i] > heap[2*i]))
		{
			// printf("1\n");
			swap(&heap[i],&heap[2*i]);
			i *= 2;
			// break;
		}
		else if (heap[2*i] < heap[2*i + 1])
		{
			// printf("2\n");
			if (2*i > size)
				break;
			swap(&heap[i],&heap[2*i]);
			i *= 2;
		}
		else
		{
			// printf("3\n");
			if (2*i + 1 > size)
				break;
			swap(&heap[i],&heap[2*i+1]);
			i *= 2;
			i++;
			// printf("4\n");
		}
	}
}

// void heapSort(){
// 	while(size > 0){
// 		DeleteMin();
// 	}
// }

// void PrintSorted(){
// 	for (int i = 0; i < len; ++i)
// 	{
// 		printf("%d ",heap[i+1] );
// 	}
// 	printf("\n");
// }

int main(int argc, char const *argv[])
{
	printf("Initializing Heap\n");
	printf("Enter the length of heap: ");
	scanf("%d",&len);
	int opt;
	heap = (int *)malloc((len+1)*sizeof(int));
	do{
		printf("Menu\n1.Insert\n2.Get Min\n3.Delete Min\n0.Exit\nEnter your choice: ");
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
			// case 4:
			// 	heapSort();
			// 	PrintSorted();
			case 0:
				break;
			default:
				printf("Retry\n");
				break;
		}
		PrintHeap();
	} while (opt != 0);
	free(heap);
	return 0;
}