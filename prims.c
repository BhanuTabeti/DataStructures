#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct 
{
	int x,w;
}vertex;

int len,size = 0;
int E,V;
vertex *heap;
vertex p;


void swap(vertex *a,vertex *b){
	vertex temp = *a;
	*a = *b;
	*b = temp;
	return;
}

void heapify(int i){
	while (heap[i/2].w >= heap[i].w)
	{
		swap(&heap[i],&heap[i/2]);
		i /= 2; 
	}
}
void MakeHeap(int V){
	for (int i = 1; i <= V; ++i)
	{
		heap[i].x = i-1;
		heap[i].w = INT_MAX;
		size++;
	}
	heap[1].w = 0;
	return;
}

vertex FindMin(){
	return heap[1];
}

void PrintHeap(){
	for (int i = 0; i < size; ++i)
	{
		printf("%d-%d\n ",heap[i+1].x,heap[i+1].w );
	}
	printf("\n");
}

void DeleteMin(){
	swap(&heap[1],&heap[size--]);
	// heap[1] = heap[size--];
	int i = 1;
	while((heap[i].w >= heap[2*i].w) || (heap[i].w >= heap[2*i + 1].w) && (i <= len/2)){
		if (size == 2*i && (heap[i].w >= heap[2*i].w))
		{
			swap(&heap[i],&heap[2*i]);
			i *= 2;
		}
		else if (heap[2*i].w < heap[2*i + 1].w)
		{
			// printf("hii\n");
			if (2*i > size)
				break;
			swap(&heap[i],&heap[2*i]);
			i *= 2;
		}
		else
		{
			// printf("hello\n");
			if (2*i + 1 > size)
				break;
			swap(&heap[i],&heap[2*i+1]);
			i *= 2;
			i++;
		}
	}
}

int UpdateHeap(int v,int val){
	for (int i = 1; i <= size; ++i)
	{
		if (heap[i].x == v)
		{
			if(heap[i].w > val){
				heap[i].w = val;
				heapify(i);
				return 1;
			}
			return 0;
		}
	}
}
void Prims(int graph[V][V]){
	// printf("hi\n");
	// for (int i = 0; i < V; ++i)
	// {
	// 	for (int j = 0; j < V; ++j)
	// 	{
	// 		printf("%d ",graph[i][j] );
	// 	}
	// 	printf("\n");
	// }
	bool minSet[V];
	int parent[V];
	for (int i = 0; i < V; ++i)
	{
		minSet[i] = false;
	}
	while(size > 0){
		// PrintHeap();
		p = FindMin();
		DeleteMin();
		// printf("%d\n",p.x );
		for (int i = 0; i < V; ++i)
		{
			if (graph[p.x][i] != 0 && !minSet[i]){
				if(UpdateHeap(i,graph[p.x][i])){
					parent[i] = p.x;
				}
			}
		}
		minSet[p.x] = true;
	}
	printf("\n---------------------\nMinimum Spanning Tree\n");
	for (int i = 1; i < V; ++i)
	{
		printf("%d -- %d = %d\n",parent[i],i,graph[i][parent[i]]);
	}
}

int main(int argc, char const *argv[])
{
	printf("Enter G(V E): ");
	scanf("%d",&V);
	scanf("%d",&E);
	heap = (vertex *)malloc((V+1)*sizeof(vertex));
	MakeHeap(V);
	int graph[V][V],x,y,w;

	// Input as Edges
	printf("Vetices are from 0 to V\n");
	for (int i = 0; i < V; ++i)
	{
		for (int j = 0; j < V; ++j)
		{
			graph[i][j] = 0;
		}
	}
	for (int i = 0; i < E; ++i)
	{
		printf("Enter The edge %d (x y w): ",i+1);
		scanf("%d",&x);
		scanf("%d",&y);
		scanf("%d",&w);	
		graph[x][y] = w;
		graph[y][x] = w;
	}

	Prims(&graph[0]);
	return 0;
}