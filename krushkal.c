#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
	int x,y,w;
}edge;

typedef struct 
{
	int rep;
	int rank;
}node;

int E,V;


void swapedge(edge *i,edge *j){
	edge temp = *i;
	*i = *j;
	*j = temp;
}

int Partiton(edge *a,int begin,int end){
	int i = begin,j = end;
	int p = a[begin].w;
	while(1){
		while(i <= end && a[i].w <= p)i++;
		while(a[j].w > p)j--;
		if (i < j)
			swapedge(&a[i],&a[j]);
		else 
			break;
	}
	swapedge(&a[begin],&a[j]);
	return j;
}

void QS(edge *a,int begin,int end){
	if (begin < end){
		swapedge(&a[end],&a[begin]);
		int i = Partiton(a,begin,end);
		QS(a,begin,i - 1);
		QS(a,i + 1,end);
	}
}

int FindElem(node arr[],int key){
	int temp = key;
	while(arr[temp].rep != temp){
		temp = arr[temp].rep;
	}
	return temp;
}


void Union(node arr[],edge e){
	int xset = FindElem(arr,e.x);
	int yset = FindElem(arr,e.y);
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
}

void Kruskal(node arr[],edge list[]){
	QS(list,0,E-1);
	// for (int i = 0; i < E; ++i)
	// {
	// 	printf("%d %d %d\n",list[i].x,list[i].y,list[i].w );
	// }
	edge Result[E];
	int c = 0;
	for (int i = 0; i < E; ++i)
	{
		if (FindElem(arr,list[i].x) != FindElem(arr,list[i].y))
		{
			Result[c++] = list[i];
			Union(arr,list[i]);
		}	
	}

	printf("\n---------------------\nMinimum Spanning Tree\n");
	for (int i = 0; i < c; ++i)
	{
		printf("%d -- %d = %d\n",Result[i].x,Result[i].y,Result[i].w );
	}
}

int main(int argc, char const *argv[])
{
	printf("Enter G(V E): ");
	scanf("%d",&V);
	scanf("%d",&E);
	node arr[V+1];
	for (int i = 0; i < V + 1; ++i)
	{
		arr[i].rep = i;
		arr[i].rank = 1;
	}
	edge list[E];

	for (int i = 0; i < E; ++i)
	{
		printf("Enter The edge %d (x y w): ",i+1);
		scanf("%d",&list[i].x);
		scanf("%d",&list[i].y);
		scanf("%d",&list[i].w);		
	}

	Kruskal(arr,list);
	return 0;
}