#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stackqueue.h" 


#define MAX_SIZE 100
typedef enum {false, true} bool;

typedef struct _GNode {
	int id;
	char data;
	struct _GNode* next;
} GNode;

typedef struct {
	int num;
	GNode** heads;
} Graph;


void CreateGraph(Graph* pgraph, int num, char* data);

void DestroyGraph(Graph* pgraph);

void AddEdge(Graph* pgraph, int src, int dest);

void RemoveEdge(Graph* pgraph, int src, int dest, int* edge);

int Check(Graph* pgraph, int src, int dest);

void PrintEdge(Graph* pgraph, int* edge);



int main() {
	Graph g;

	int node, edge, src, des;
	char* a;

	scanf("%d %d", &node, &edge);
	getchar();

	a = malloc(sizeof(char) * (node + 1));
	scanf("%s", a);
	getchar();

	CreateGraph(&g, node, a);
	for (int i = 0; i < edge; i++)
	{
	   scanf("%d %d", &src, &des);
	   AddEdge(&g, src, des);
    
	   getchar();
	}

	PrintEdge(&g, &node);

	DestroyGraph(&g);

	return 0;
}

void CreateGraph(Graph* pgraph, int num, char* data)
{
	pgraph->num = num;
	pgraph->heads = (GNode **)malloc(sizeof(GNode*)* num);
	for (int i = 0; i < num; i++)
	{
		pgraph->heads[i] = (GNode *)malloc(sizeof(GNode));
		pgraph->heads[i]->next = NULL;
	}
}
void DestroyGraph(Graph* pgraph)
{
	for (int i = 0; i < pgraph->num; i++)
	{
		GNode* cur = pgraph->heads[i];
		while (cur != NULL)
		{
			GNode* temp = cur;
			cur = cur->next;
			free(temp);
		}
	}
	free(pgraph->heads);
}
void AddEdge(Graph* pgraph, int src, int dest)
{
	GNode* newNode1, *newNode2, *cur;

	newNode1 = (GNode *)malloc(sizeof(GNode));
	newNode1->id = dest;
	newNode1->next = NULL;

	cur = pgraph->heads[src];
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = newNode1;

	newNode2 = (GNode *)malloc(sizeof(GNode));
	newNode2->id = src;
	newNode2->next = NULL;

	cur = pgraph->heads[dest];
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = newNode2;
}
void RemoveEdge(Graph* pgraph, int src, int dest, int * edge)
{
	GNode* cur;

	cur = pgraph->heads[src];
	while (cur->next->id != dest)
		cur = cur->next;

	cur->next = cur->next->next;

	cur = pgraph->heads[dest];
	while (cur->next->id != src)
		cur = cur->next;

	cur->next = cur->next->next;

	edge--;
}
int Check(Graph* pgraph, int src, int dest)
{
	Stack stack;
	bool* visited = (bool *)malloc(sizeof(bool) * pgraph->num);
	for (int i = 0; i < pgraph->num; i++)
		visited[i] = false;
	
	InitStack(&stack);
	Push(&stack, src);
	while (!IsSEmpty(&stack))
	{
		GNode* cur;
		int vtx = SPeek(&stack);
		Pop(&stack);

		if (visited[vtx])
			continue;
		else
		{
			visited[vtx] = true;
		}

		cur = pgraph->heads[vtx]->next;
		while (cur != NULL)
		{
			if (cur->id == dest)
				return 1;
			if (!visited[cur->id])
				Push(&stack, cur->id);
			cur = cur->next;
		}
	}
	return 0;
}
void PrintEdge(Graph* pgraph, int * edge)
{
	while (*edge + 1 > pgraph->num)
	{
		for (int i = 0; i < pgraph->num; i++)
		{
			for (GNode* cur = pgraph->heads[i]->next; cur != NULL; cur->next)
			{
				int src, dest;
				src = i;
				dest = cur->id;
				RemoveEdge(pgraph, src, dest, edge);
				if (!Check(pgraph, src, dest))
				{
					AddEdge(pgraph, src, dest);
				}
				else
				{
					printf("%d %d\n", src, dest);
					pgraph->num--;
					break;
				}
			}
			
		}
	}
}