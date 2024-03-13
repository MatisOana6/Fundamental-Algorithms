/*
 Matiș Oana-Antonia
 Grupa 30228

 Am implementat un algoritm de interclasare a k liste folosind heapify, min-heap si algoritmul K-WAY-MERGE.
 Complexitatea algoritmului este O(n logk).
 Pentru a implementa algortimul am folosit notiunile de lista si heap.
 Am generat k liste cu elemente generate random.
 Am generat un grafic pe cazul average folosind 3 valori diferite pentru k: k1=5, k2=10, k3=100 si cel mai eficient este
cel pentru k=5.

*/

#include <iostream>
#include <stdio.h>
#include "Profiler.h"

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5
Profiler p("Lists");

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Lista {
    Node *first = NULL;
    Node *last = NULL;

} Lista;

Node *Create_Node(int value) {
    Node *p = (Node *) malloc(sizeof(Node));
    p->next = NULL;
    p->data = value;
    return p;
}

Lista *creare_lista() {
    Lista *list = (Lista *) calloc(1, sizeof(Lista));
    list->first = NULL;
    list->last = NULL;
    return list;
}

Lista **generare_liste(int k) {
    Lista **lists = (Lista **) calloc(k, sizeof(Lista*));
    for (int i = 0; i < k; i++) {
        //op.count(2);
        lists[i] = (Lista *) calloc(1, sizeof(Lista));
        lists[i]->first = NULL;
        lists[i]->last = NULL;
    }
    return lists;
}

void insertLast(Lista *list, int value) {
    if (list == NULL)
        return;
    Node *p = Create_Node(value);
    if (list->last == NULL)
        list->first = p;
    else
        list->last->next = p;
    list->last = p;
}

void insertLast_Lists(Lista *lists, int value) {
    if (lists == NULL)
        return;
    Node *p = Create_Node(value);
    if (lists->last == NULL) {
        lists->first = lists->last = p;
    }
    else {
        lists->last->next = p;
    }
    lists->last = p;
}

void print_list(Lista *list) {
    if (list != NULL) {
        printf("[");
        for (Node *p = list->first; p != NULL; p = p->next)
            printf("%d ", p->data);
        printf("]\n");
    }
}

void print_lists(Lista **lists, int k) {
    if (lists != NULL) {
        for (int i = 0; i < k; i++) {
            printf("[");
            //op.count();
            if (lists[i]->first != NULL)
                for (Node *p = lists[i]->first; p != NULL; p = p->next)
                    printf("%d ", p->data);
            printf("]\n");
        }
    }
    printf("\n");
}

void umplere_siruri(Lista **lists, int k,int n) {
    for (int i = 0; i < k; i++)
    {
        int v[MAX_SIZE];
        FillRandomArray(v, n/k, 10, 50000, false, ASCENDING);
        for (int j = 0; j < n/k; j++)
        {
            insertLast_Lists(lists[i], v[j]);
        }
    }
}

void swap(int *x, int *y) {
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

void swap_list(Lista **list, int i, int j) {
    Lista *aux = list[i];
    list[i] = list[j];
    list[j] = aux;
}


void print(int array[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", array[i]);
}

void Heapify_Min(int *array, int n, int i) {

    int smallest = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;
    if (left < n && array[left] < array[smallest]) {
        smallest = left;
    } else smallest = i;
    if (right < n && array[right] < array[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&array[smallest], &array[i]);
        Heapify_Min(array, n, smallest);
    }

}

void Heapify_Min_list(Lista **list, int n, int i, Operation op)
{
    int smallest = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;
    op.count();
    if (left < n && list[left]->first->data < list[smallest]->first->data) {
        smallest = left;
    }
    op.count();
    if (right < n && list[right]->first->data < list[smallest]->first->data) {
        smallest = right;
    }

    if (smallest != i) {
        op.count(3);
        swap_list(list, i, smallest);
        Heapify_Min_list(list, n, smallest,op);
    }

}

void BuildHeap_Min(Lista **list, int n) {
    Operation op= p.createOperation("op_heap", n);
    //index of last non-leaf node
    int i, index = (n / 2) - 1;
    //performs level order traversal from the last non-leaf node To the root node and heapify the nodes
    for (i = index; i >= 0; i--) {
        Heapify_Min_list(list, n, i,op);
    }
}

void K_WAY_MERGE(Lista **list, int k, Operation op) {
    int vect[MAX_SIZE], i = 0;
    int heapsize = k;
    BuildHeap_Min(list, k);
    while (heapsize > 0) {
        op.count(3);
        vect[i] = list[0]->first->data;
        i++;
        list[0]->first = list[0]->first->next;
        if (list[0]->first == NULL) {
            op.count();
            list[0] = list[heapsize - 1];
            heapsize = heapsize - 1;
        }
        Heapify_Min_list(list, heapsize, 0,op);
    }
    /*for (int j = 0; j < i; j++) {
        printf(" %d", vect[j]);
    }
     */
}

void demo() {
    Operation op= p.createOperation("op", 3);
    Lista **lists = generare_liste(4);
    umplere_siruri(lists, 4, 20);
    print_lists(lists, 4);
    K_WAY_MERGE(lists, 4,op);
}

void list_average() {
    int arr[MAX_SIZE];
    int n,k1=5,k2=10,k3=100;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {

        Operation op1=p.createOperation("op1", n);
        Lista **list1=generare_liste(k1);
        umplere_siruri(list1, k1,n);
        K_WAY_MERGE(list1, k1, op1);

        Operation op2=p.createOperation("op2", n);
        Lista **list2=generare_liste(k2);
        umplere_siruri(list2, k2,n);
        K_WAY_MERGE(list2, k2, op2);

        Operation op3=p.createOperation("op3", n);
        Lista **list=generare_liste(k3);
        umplere_siruri(list, k3,n);
        K_WAY_MERGE(list, k3, op3);
        }

    p.createGroup("Total_Merge_Lists","op1", "op2", "op3");
    p.showReport();

}

void perf() {
    int k;
    int n=MAX_SIZE;
    for (k = 10; k <= 500; k += 10)
    {
        Operation op_k=p.createOperation("op_k", k);
        Lista **list=generare_liste(k);
        umplere_siruri(list, k,n);
        K_WAY_MERGE(list, k, op_k);
    }
    p.showReport();
}

int main() {
    //demo();
    //perf();
    //list_average();
    return 0;
}
