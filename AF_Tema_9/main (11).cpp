/* Matiș Oana-Antonia
 * Grupa 30228
 *
 *  Am implementat operațiile de bază pe mulțimi disjuncte: make_set, find_set, union_set si algoritmul kruskal
 *pentru gasirea arborelui de acoperire minima.
 *  Pentru implementarea operatiilor pe multimile disjuncte am folosit o padure de arbori si am extins fiecare
 *arbore cu un camp rank.
 *  In urma reprezentarii grafice, reiese ca algoritmul Krusakal are o complxitate liniara.
 *  Am numarat operatiile din functiile make_set, union_set si find_set si link_set.
 *  Pentru a obtine graficul am variat n de la 100 la 10000 cu un step size de 100.
 *  Graficul generat random este conex, neorientat și aleatoriu si are n noduri si 4*n muchii.
 *  Algoritmul Kruskal are o complexitate O(ElogE).
 *
 */
#include <iostream>
#include <stdio.h>
#include "Profiler.h"
#include <string.h>

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5


Profiler p("Tema9_DisjointSets");

typedef struct Node
{   int key;
    struct Node *parent;
    int rank;
}Node;

/*The makeSet function creates a new node in the disjoint set data structure with a given key value.
 *This function initializes the node with a rank of 0, sets the node's parent to point to itself, and sets
 * the key value of the node to the given value.*/
Node *makeSet(int value, Operation op)
{ op.count(3);
    Node *node = (Node*)(malloc(sizeof(Node)));
    node->rank=0;
    node->parent=node;
    node->key=value;
    return node;
}


//The function compares the rank of the two nodes, and makes the node with the lower rank a child of the node
// with the higher rank. If the ranks of the two nodes are equal, the rank of the parent node is incremented by 1
void linkSet(Node *node1,Node *node2 , Operation op)
{op.count();
    if(node1->rank>node2->rank)
    {op.count();
        node2->parent=node1;
    }
    else
    { op.count(2);
        node1->parent=node2;
        if(node1->rank==node2->rank)
        { op.count();
            node2->rank=node2->rank+1;
        }
    }
}

Node *findSet(Node *node, Operation op)
{op.count();
    if(node!=node->parent)
    { op.count();
        node->parent = findSet(node->parent, op);
    }
    return node->parent;
}

// takes in a node, and returns the root of the set that the node is in
Node *findSet2(Node *node)
{
    if(node!=node->parent)
    {
        node->parent = findSet2(node->parent);
    }
    return node->parent;
}

void unionSet(Node *node1, Node *node2 , Operation op)
{
    linkSet(findSet(node1,op),findSet(node2,op),op);
}

typedef struct edge
{
    int left;
    int right;
    int weight;
}edge;

void swap(edge *x, edge *y) {
    edge aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

int Partition(edge *array, int p, int r)
{
    edge pivot= array[r];
    int i=p-1;
    for(int j=p;j<r;j++)
    {
        if(array[j].weight<pivot.weight)
        {
            i=i+1;
            swap(&array[i],&array[j]);

        }
    }
    swap(&array[i+1],&array[r]);
    return i+1;
}

void QuickSort(edge *array, int min, int max)
{
    if(min<max)
    {
        int q=Partition(array, min ,max);
        QuickSort(array, min, q-1);
        QuickSort(array, q+1, max);
    }
}

typedef struct Graph
{
    int nrOfNodes;
    int nrOfEdges;
    edge *arrayOfEdges;
};

edge *Kruskal(Graph *graph, Operation op)
{
    int i,j,minCost;
    Node *arrayOfNodes[graph->nrOfNodes];
    for(i=0;i<graph->nrOfNodes;i++)
    {
        arrayOfNodes[i]=makeSet(i+1,op);//it creates an array of sets, with one set per node of the graph, using the makeSet function

    }
    QuickSort(graph->arrayOfEdges,0,graph->nrOfNodes-1);
    edge *array=(edge*)calloc(graph->nrOfNodes-1,sizeof(edge));//the number of edges equal to the number of nodes minus one,
    // which is the maximum number of edges in a MST(minimum spanning tree)of a graph.
    int contor=0;
    for(i=0;i<graph->nrOfEdges;i++)
    { if(contor==graph->nrOfNodes-1)
            break;
        else
        {
            edge edge_new=graph->arrayOfEdges[i];
            if(findSet(arrayOfNodes[edge_new.right],op)!=findSet(arrayOfNodes[edge_new.left],op)) {
                array[contor] = edge_new;
                unionSet(arrayOfNodes[edge_new.right], arrayOfNodes[edge_new.left],op);
                contor++;
            }
        }
    }
    return array;
}

Graph *newGraph(int nrNodes)
{
    Graph *graph=(Graph *)malloc(sizeof(Graph));
    graph->nrOfNodes=nrNodes;
    graph->nrOfEdges=4*nrNodes;
    graph->arrayOfEdges=(edge *)malloc(sizeof(edge)*graph->nrOfEdges);
}

Graph *rand_graph(int nrNodes)
{
    Graph *graph=newGraph(nrNodes);
    for(int i=1;i<nrNodes;i++)
    {
        graph->arrayOfEdges[i-1].right=rand()%i;
        graph->arrayOfEdges[i-1].left=i;
        graph->arrayOfEdges[i-1].weight=rand()%500+1;
    }
    int n=nrNodes-1;
    while(n<graph->nrOfEdges)
    {   int ok=1;
        int right = rand()%nrNodes;
        int left = rand()%nrNodes;
        if(right!=left)
        {
            for(int i=0;i<n;i++)
                if((graph->arrayOfEdges[i].right==right && graph->arrayOfEdges[i].left==left) || (graph->arrayOfEdges[i].right==left && graph->arrayOfEdges[i].left==right))
                {
                    ok=0;
                }
        }
        else ok=0;
        if(ok==1)
        {
            graph->arrayOfEdges[n].right=right;
            graph->arrayOfEdges[n].left=left;
            graph->arrayOfEdges[n].weight=rand()%500+1;
            n++;
        }
    }
    return graph;

}


/* * The output of this code would be a series of lines, each containing an integer, another integer, and a newline. The first integer on each
 * line would be the key of one of the nodes in the array arbore.
 * The second integer on each line would be the key of the parent node of the first node (as determined by the findSet2 function).

The second loop of the function would print the edges of the minimum spanning tree generated by the Kruskal algorithm,
 where each edge is represented by 3 integers separated by space: the left vertex, the right vertex and the weight of the edge.
 * */
void demo()
{   Operation op= p.createOperation("Kruskal", 3);
    int n = 10;
    int i;
    Node *arbore[10];
    for(i=0;i<n;i++)
    {
        arbore[i]=makeSet(i+1,op);

    }

    unionSet(arbore[2],arbore[4],op);
    unionSet(arbore[3],arbore[4],op);
    unionSet(arbore[5],arbore[6],op);
    unionSet(arbore[6],arbore[8],op);
    unionSet(arbore[3],arbore[8],op);

    for (i = 0; i < n; i++) {
        printf("%d %d\n", arbore[i]->key, findSet2(arbore[i])->key);
    }

    Graph *graph= rand_graph(n);
    edge *edge_new=Kruskal(graph,op);
    for(int i=0;i<n-1;i++)
    {
        printf("%d %d %d\n", edge_new[i].right+1, edge_new[i].left+1, edge_new[i].weight);
        //left si right sunt pozitiile pe care le-ar avea arborele
    }
}

void perf()
{
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        int test;
        for (test = 0; test < NR_TESTS; test++)
        {
            Operation op= p.createOperation("Kruskal", n);
            Graph *graph= rand_graph(n);
            edge *edge_new=Kruskal(graph,op);
        }
    }
    p.divideValues("Kruskal", NR_TESTS);
    p.showReport();
}

int main()
{
    //demo();
    perf();
    return 0;
}

