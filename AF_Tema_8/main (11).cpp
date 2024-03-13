/*
Matis Oana-Antonia
Grupa 30228

    Am implementat algoritmii de parcurgere iterativa si recursiva a unui
arbore binar si de hibridizare pentru quicksort.
    Pentru a realiza algoritmul de hibridizare quicksort am folosit insertion
sort din tema 1 si quicksort din tema 3.
    Pentru a realiza algoritmul de parcurgere iterativa am folosit structura
unei stive, functiile de pop si push implementate la SDA.
    La parcurgerea arborelui binar am folosit preorder.

    Din analiza comparativa a versiunii iterative si a celei recursive, reiese
ca acestea au complexitatea O(n), graficul fiind liniar.
    Ca timp de executie, quicksort hibridizat este mai optim decat quicksort, quicksort
hibridizat executa mai putine operatii.
    Ca numar de operatii, quickSort hibridizat este mai optim decat quicksort.
    Din numarul de operatii pentru quicksort hibridizat, reiese un grafic liniar.
    Pentru prag, am obtinut un grafic care reprezinta aproximativ o parabola, pragul iese aproximativ intre 10-15.

    Pe cazul average, cand elementele din vector nu sunt nici crescatoare, nici
descrescatoare, complexitatea algoritmului quicksort este O(nlogn), pe best are
complexitatea O(nlogn), iar pe worst are complexitatea O(n^2).
 Pe best case, algoritmul de insertion sort are complexitatea O(N),pe worst case, algoritmul
 are complexitatea O(N^2), iar pe average case, algoritmul are complexitatea O(N^2).

 Complexitatea algoritmului de quicksort hibridizat este O(n^2).

*/

#include <iostream>
#include <stdio.h>
#include "Profiler.h"

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5
#define NR_TESTS2 100
Profiler p("Tema8_Hibridizare_QuickSort");
int printeaza=0;

typedef struct binarySearchTree
{
    int data;
    struct binarySearchTree *left;
    struct binarySearchTree *right;
}binarySearchTree;

binarySearchTree *binarySearchTree_new(int data)
{
    binarySearchTree *tree =(binarySearchTree *) malloc(sizeof (binarySearchTree));
    tree->left = NULL;
    tree->right = NULL;
    tree->data=data;
    return tree;
}

binarySearchTree *binarySearchTree_add(binarySearchTree *tree, int value)
{
    if(tree==NULL)
        return binarySearchTree_new(value);
    if(value<=tree->data)
        tree->left= binarySearchTree_add(tree->left, value);
    else if(value>tree->data)
        tree->right= binarySearchTree_add(tree->right, value);
    return tree;
}

void binarySearchTree_preorder(binarySearchTree *tree, Operation op) {
    if (tree != NULL) {
        op.count();
       if(printeaza==0)
       {
           printf("%d ", tree->data);
       }
            binarySearchTree_preorder(tree->left, op);
            binarySearchTree_preorder(tree->right, op);

    }
}
void binaryTree_print(binarySearchTree *tree, int space)
{
    if(tree != NULL) {
        for(int i=0; i<space; i++)
            printf("    ");
        printf("%d\n", tree->data);
        binaryTree_print(tree->left, space+1);
        binaryTree_print(tree->right, space+1);
    }
}

typedef struct stack // node defining for stack
{
     binarySearchTree* data;
     struct stack* next;
}stack;

void push(stack** top,binarySearchTree *node) //push node in stack
{
    stack* new_node = (struct stack*)malloc(sizeof(struct stack));
    new_node->data = node;
    new_node->next = (*top);
    (*top) = new_node;
}

//checks if stack is empty, if it is empty then it returns 1, else
//it returns 0
int isEmpty(struct stack* top) // check if stack is empty
{
    if(top==NULL)
        return 1;
    else
        return 0;
}

//is used to remove the node from the stack and return it
binarySearchTree * pop(stack** top_node) // pop the node from stack
{
    binarySearchTree * value;
    stack* top;
    top = *top_node;
    value = (binarySearchTree *)(top->data);
    *top_node = top->next;
    return value;
}

//in this function we print the node and traverse the tree left node
//until we find null, where exists null we backtrack in tree with the help
//of the stack and pop the element and print it

//we check if there is the right child of that node and is yes, then
//we traverse the left of the node again

//we do these until tree_new is empty and stack is empty
int treeIterativePreorder(binarySearchTree * tree,Operation op)
{
    binarySearchTree * tree_new = tree;
    stack* stack_new = NULL;
    int ok = 1;
    while(tree_new!=NULL || !isEmpty(stack_new)) //Loop run until temp is null and stack is empty
    {
        if(tree_new!=NULL)
        {
            op.count();
            if(printeaza==0)
            {
                printf("%d ",tree_new->data);
            }
            push(&stack_new,tree_new);
            tree_new = tree_new->left;
        }
        else
        {
                tree_new = pop(&stack_new);
                tree_new = tree_new->right;
        }

    }
}

void swap(int *x, int *y) {
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

void print(int array[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", array[i]);
}

//   QuickSort
int Partition(int array[], int p, int r, Operation op)
{
    op.count();
    int pivot= array[r];
    int i=p-1;
    for(int j=p;j<r;j++)
    { op.count();
        if(array[j]<pivot)
        {
            i=i+1;
            op.count(3);
            swap(&array[i],&array[j]);

        }
    }
   op.count(3);
    swap(&array[i+1],&array[r]);
    return i+1;
}


void QuickSort(int array[], int min, int max, int n,Operation op)
{
    if(min<max)
    {
        int q=Partition(array, min ,max,op);
        QuickSort(array, min, q-1, n,op);
        QuickSort(array, q+1, max, n,op);
    }
}

void insertionSort(int array[],int l, int n,Operation op)
{
    int i,sort,var;
    for(i=l;i<=n;i++)
    { op.count();
        sort=i-1;
        var=array[i];
        op.count();
        //move the elements of the array that are greater than the key
        //to one position ahead of their current position
        while(sort>=l && array[sort]>var)
        {
            op.count();
            array[sort+1]=array[sort];
            sort=sort-1;
        }
        op.count();
        array[sort+1]=var;
    }
}


void hybridQuickSort(int array[],int l, int r, Operation op)
{
    //condition to stop recursion
        if (l<r)
        {//if size of array < threshold, then it will apply insertion
            //sort and stop recursion
            if (r - l < 30)
                insertionSort(array, l, r, op);
            else {
                int index = Partition(array, l, r, op);
                //if left side of pivot/index < right side, then it will
                //sort left part and move to the right part of the array
                hybridQuickSort(array, l, index - 1, op);
                //if right side of pivot/index < left side, then it will
                //sort right side and move to the left side of the array
                hybridQuickSort(array, index + 1, r, op);
            }
        }
}

void hybridQuickSort_prag(int array[],int l, int r, Operation opquick, int prag) {
    if (l < r)
    {
        if (r - l < prag)
            insertionSort(array, l, r, opquick);
        else {
            int index = Partition(array, l, r, opquick);
            hybridQuickSort_prag(array, l, index - 1, opquick, prag);
            hybridQuickSort_prag(array, index + 1, r, opquick, prag);
        }
    }
}

void demo()
{   int i;
    int n1;
    Operation op=p.createOperation("op_parcurgere", n1);
    Operation op1=p.createOperation("op_quicksort", n1);
    binarySearchTree *tree=NULL;
    tree=binarySearchTree_add(tree,4);
    binarySearchTree_add(tree,2);
    binarySearchTree_add(tree,6);
    binarySearchTree_add(tree,1);
    binarySearchTree_add(tree,3);
    binarySearchTree_add(tree,5);
    binarySearchTree_add(tree,7);
    printf("\nThe binary search tree is:\n");
    binaryTree_print(tree,0);
    printf("\nPreorder:");
    binarySearchTree_preorder(tree,op);
    printf("\nIterative preorder:");
    treeIterativePreorder(tree,op);
    printf("\n");
    int array[]={1,2,56,34,7,27,90,64,72,125,
                 38,18,9,49,89,140,13,80,55,63,6};
    int n = sizeof(array)/sizeof(*array);
    printf("Quicksort este: ");
    QuickSort(array,0,n-1,n,op);
    for(i=0;i<n;i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("Quicksort hibridizat este: ");
    hybridQuickSort(array,0,n-1,op);
    for(i=0;i<n;i++)
    {
        printf("%d ", array[i]);
    }
}

void parcurgere_average() {
    int arr[MAX_SIZE];
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {       Operation op_recursiv=p.createOperation("op_recursiv", n);
            Operation op_iterativ=p.createOperation("op_iterativ", n);
            FillRandomArray(arr, n, 10, 50000, false, 0);
            binarySearchTree *tree=NULL;
            for(int i=0;i<n;i++)
            {
                tree= binarySearchTree_add(tree,arr[i]);
            }
        binarySearchTree_preorder(tree,op_recursiv);
        treeIterativePreorder(tree,op_iterativ);
    }
    p.createGroup("Comparison_binarySearchTree","op_recursiv", "op_iterativ");
    p.showReport();
}

void QuickSort_average(int order)
{
    int arr[MAX_SIZE], arr1[MAX_SIZE];
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        int test;
        for (test = 0; test < NR_TESTS2; test++)
        {
            Operation op1= p.createOperation("op_quickSort", n);
            Operation op2= p.createOperation("op_quickSortHybrid", n);
            FillRandomArray(arr, n, 10, 50000, false,order);
            CopyArray(arr1, arr, n);
            QuickSort(arr,0,n-1,n,op1);
            hybridQuickSort(arr1,0,n-1,op2);
        }
    }
    //QuickSort and Hybrid quicksort in average
    p.divideValues("op_quickSort", NR_TESTS2);
    p.divideValues("op_quickSortHybrid", NR_TESTS2);
    p.createGroup("Total_build_Average", "op_quickSort", "op_quickSortHybrid");
    p.showReport();
}

void QuickSortHybrid_average(int order)
{
    int arr[MAX_SIZE], arr1[MAX_SIZE];
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        int test;
        for (test = 0; test < NR_TESTS2; test++)
        {
            Operation op2= p.createOperation("op_quickSortHybrid", n);
            FillRandomArray(arr, n, 10, 50000, false,order);
            hybridQuickSort(arr,0,n-1,op2);
        }
    }
    p.divideValues("op_quickSortHybrid", NR_TESTS2);
    p.showReport();
}

void quickSort_time()
{
    int arr[MAX_SIZE], arr1[MAX_SIZE], arr2[MAX_SIZE];
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        int test;
        FillRandomArray(arr, n, 10, 50000, false, 0);
        Operation op1= p.createOperation("op_quickSort", n);
        Operation op2= p.createOperation("op_quickSortHybrid", n);
        p.startTimer("QuickSort", n);
        for (test = 0; test < NR_TESTS2; test++)
        {
            FillRandomArray(arr, n, 10, 50000, false, 0);
            QuickSort(arr,0,n-1,n,op1);

        }
        p.stopTimer("QuickSort", n);

        p.startTimer("hybridQuickSort", n);
        for (test = 0; test < NR_TESTS2; test++)
        {
            FillRandomArray(arr1, n, 10, 50000, false, 0);
            hybridQuickSort(arr1,0,n-1,op2);
        }
        p.stopTimer("hybridQuickSort", n);
    }
    p.createGroup("Total_QuickSort_TIME", "QuickSort", "hybridQuickSort");
    p.showReport();
}

void prag()
{
    int quicksort[MAX_SIZE], hybrid[MAX_SIZE];
    int prag;
    for (prag = 1; prag <= 100; prag += 1)
    {
        printf("%d",prag);
        int test;
        for (test = 0; test < 500; test++)
        {   Operation opquick = p.createOperation("Quicksort hybrid operations", prag);
            FillRandomArray(hybrid, MAX_SIZE);
            hybridQuickSort_prag(hybrid,0,MAX_SIZE-1,opquick,prag);
        }
    }
    p.divideValues("prag_quickSortHybrid", 500);
    p.showReport();
}

int main()
{
    demo();
   //parcurgere_average();
   //QuickSort_average(UNSORTED);
   //QuickSortHybrid_average(UNSORTED);
   //quickSort_time();
   //prag();
    return 0;
}
