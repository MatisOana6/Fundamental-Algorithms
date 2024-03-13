#include <iostream>
#include <stdio.h>
#include "Profiler.h"
#include <stack>
#include <cmath>

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5

Profiler p("DFS");
int t = 0;
int index = 0;
int nrComponents = 0;
int ciclu = 0;

enum {
	COLOR_WHITE = 0,
	COLOR_GRAY,
	COLOR_BLACK
};

typedef struct Node {
	struct Lista* adj;
	int key;
	int color;
	int d;
	int f;
	struct Node* parent;

	int index;
	int lowLink;
	int onStack;
	int comp;
	int vertex;
	struct Node* next;
}Node;

typedef struct Lista
{
	Node* nod;
	Lista* next;
}Lista;


typedef struct {
	int nrNodes;
	Node** v;
	int nrOfEdges;
	Lista adjList;
}Graph;



Node* newNode(int n)
{
	Node* nodeNew = (Node*)(malloc(sizeof(Node)));
	nodeNew->vertex = n;
	nodeNew->next = NULL;
	return nodeNew;
}

Graph* newGraph(int nrOfNodes)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->nrNodes = nrOfNodes;
	graph->v = (Node**)malloc(graph->nrNodes * sizeof(Node));
	for (int i = 0; i < nrOfNodes; i++) {
		graph->v[i] = (Node*)calloc(1,sizeof(Node));
		//memset(graph->v[i], 0, sizeof(Node));
		graph->v[i]->key = i;
	}
	return graph;
}

Lista* insertLast_Lists(Lista* lists, Node* node)
{
	Lista* nod_nou_lista = (Lista*)malloc(sizeof(Lista));
	nod_nou_lista->nod = node;
	nod_nou_lista->next = NULL;
	Lista* p = lists;
	if (lists!= NULL) {
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = nod_nou_lista;
	}
	else
		lists = nod_nou_lista;
	return lists;
}


void newEdge(Graph* graph, int left, int right)
{
	graph->v[left]->adj = insertLast_Lists(graph->v[left]->adj, graph->v[right]);
	graph->v[right]->adj = insertLast_Lists(graph->v[right]->adj, graph->v[left]);
}


void DFS_Visits(Graph* graph, Node* u)
{
	t = t + 1;
	u->d = t;
	u->color = COLOR_GRAY;
	Lista* p = u->adj;
	while (p != NULL)
	{
		if (p->nod->color == COLOR_WHITE)
		{
			p->nod->parent = u;
			DFS_Visits(graph, p->nod);
		}
		p = p->next;
	}
	u->color = COLOR_BLACK;
	t++;
	u->f = t;
}


void DFS_Visits2(Graph* graph, Node* u)
{
	t = t + 1;
	u->d = t;
	u->color = COLOR_GRAY;
	Lista* p = u->adj;
	while (p != NULL)
	{
		if (p->nod->color == COLOR_WHITE)
		{
			p->nod->parent = u;
			DFS_Visits(graph, u);
		}
		p = p->next;
	}
	u->color = COLOR_BLACK;
	t++;
	u->f = t;
}

void DFS(Graph* graph)
{
	for (int i = 0; i < graph->nrNodes; i++) {
		graph->v[i]->color = COLOR_WHITE;
		graph->v[i]->parent = NULL;
	}
	t = 0;
	for (int i = 0; i < graph->nrNodes; i++) {
		if (graph->v[i]->color == COLOR_WHITE)
		{
			DFS_Visits(graph, graph->v[i]);
		}
	}
}

void pretty_print(Graph* graph, int index, int indentation)
{
	if (index == -1)
	{
		printf("0\n");
		pretty_print(graph, 0, indentation + 1);
	}
	else
	{
		for (int i = 1; i < graph->nrNodes; i++)
		{
			if (graph->v[i]->parent->key == index)
			{
				printf("%d\n", graph->v[i]->key);
				pretty_print(graph, i, indentation + 1);
			}
		}
	}

}

void prettyPrintParent(Graph* graph, int parent, int numberOfSpaces) {
    for (int i = 0; i < graph->nrNodes; i++) {
        if (graph->v[i]->parent && graph->v[i]->parent->key == parent) {
            for (int j = 0; j < numberOfSpaces; j++) {
                printf("    ");
            }
            numberOfSpaces++;
            printf("%d\n", graph->v[i]->key);
            prettyPrintParent(graph, graph->v[i]->key, numberOfSpaces);
        }
    }
}


Lista* DFS_Topological(Graph* graph, int u, Lista* sortedList) {
    // Mark the node as GRAY
    t++;
    graph->v[u]->d = t;
    graph->v[u]->color = COLOR_GRAY;
    // Recursively visit all the adjacent nodes
    Lista* p = graph->v[u]->adj;
    while (p != NULL) {
        if (graph->v[p->nod->key]->color == COLOR_GRAY) {
            ciclu = 1;
        }
        if (graph->v[p->nod->key]->color == COLOR_WHITE) {
            DFS_Topological(graph, p->nod->key, sortedList);
        }
        p = p->next;
    }
    // Mark the node as BLACK and insert it at the front of the sorted list
    graph->v[u]->color = COLOR_BLACK;
    t++;
    graph->v[u]->f = t;
    sortedList = insertLast_Lists(sortedList, graph->v[u]);
    return sortedList;
}

void TopologicalSort(Graph* graph) {
    // Initialize all nodes with color WHITE
    for (int i = 0; i < graph->nrNodes; i++) {
        graph->v[i]->color = COLOR_WHITE;
    }
    int time = 0;
    ciclu = 0;
    // Initialize an empty list to store the sorted nodes
    Lista* sortedList = NULL;
    // Perform DFS on all nodes that haven't been visited yet
    for (int i = 0; i < graph->nrNodes; i++) {
        if (graph->v[i]->color == COLOR_WHITE) {
            sortedList = DFS_Topological(graph, i, sortedList);
        }
    }
    // Print the sorted list if no cycle is detected
    if (ciclu == 0) {
        Lista* p = sortedList;
        while (p != NULL) {
            printf("%d ", p->nod->key);
            p = p->next;
        }
    } else {
        printf("The graph has a cycle\n");
    }
}



void StrongConnect(Graph* graph, Node* u, std::stack<Node*>& stiva)
{
    u->index = u->lowLink = index;
    index++;
    stiva.push(u);
    u->onStack = true;
    Lista* p = u->adj;
    while (p != NULL)
    {
        if (p->nod->index == -1)
        {
            StrongConnect(graph, p->nod, stiva);
            u->lowLink = std::min(u->lowLink, p->nod->lowLink);
        }
        else if (p->nod->onStack)
        {
            u->lowLink = std::min(u->lowLink, p->nod->index);
        }
        p = p->next;
    }
    Node* v;
    if (u->lowLink == u->index)
    {
        nrComponents++;
        do {
            v = stiva.top();
            stiva.pop();
            v->onStack = false;
            v->comp = nrComponents;
        } while (v != u);
    }
}

void Tarjan(Graph* graph)
{
    index = 0;
    nrComponents = 0;
    std::stack<Node*> stiva;
    for (int i = 0; i < graph->nrNodes; i++)
    {
        graph->v[i]->index = graph->v[i]->lowLink = -1;
        graph->v[i]->onStack = false;
        graph->v[i]->comp = 0;
    }
    for (int i = 0; i < graph->nrNodes; i++)
    {
        if (graph->v[i]->index == -1)
            StrongConnect(graph, graph->v[i], stiva);
    }
}

void printTarjan(Graph* graph) {
    for (int i = 0; i < graph->nrNodes; i++) {
        printf("%d:%d,%d,%d\n", i, graph->v[i]->index, graph->v[i]->lowLink, graph->v[i]->comp);
    }
}

void demo() {
    Graph *graph = newGraph(9);

    newEdge(graph, 0, 1);
    newEdge(graph, 0, 3);
    newEdge(graph, 1, 2);
    newEdge(graph, 3, 4);
    newEdge(graph, 4, 5);
    newEdge(graph, 4, 6);
    newEdge(graph, 5, 7);
    newEdge(graph, 8, 7);

    for (int i = 0; i < graph->nrNodes; i++) {
        Lista *p = graph->v[i]->adj;
        printf("\n%d: ", i);
        while (p != NULL) {
            printf("%d ", p->nod->key);
            p = p->next;
        }
    }
    printf("\n");
    DFS(graph);
    graph->v[0]->parent = newNode(-1);
    graph->v[0]->parent->key = -1;
    prettyPrintParent(graph, -1, 0);
    printf("\nTopological Sort: ");
    TopologicalSort(graph);

    Graph *graph_tarjan = newGraph(9);

    newEdge(graph_tarjan, 0, 1);
    newEdge(graph_tarjan, 0, 3);
    newEdge(graph_tarjan, 1, 2);
    newEdge(graph_tarjan, 3, 4);
    newEdge(graph_tarjan, 4, 5);
    newEdge(graph_tarjan, 4, 6);
    newEdge(graph_tarjan, 5, 7);
    printf("\nTarjan: ");
    Tarjan(graph_tarjan);
    printTarjan(graph_tarjan);
}

    int main() {
	demo();
	return 0;
}