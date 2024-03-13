/*
   Matiș Oana-Antonia
   Grupa 30228

   Am implementat 3 algoritmi:două metode de construire a structurii de date
Heap i.e. “de jos în sus” (bottom-up) și “de sus în jos” (top-down) si de asemenea,
algoritmul heapsort.
   Procedura Max-Heapify, care are o complexitate de O(lg n), este cheia pentru a mentine proprietatea de max-heap.
   Procedura Build-Max-heap, care are o complexitate liniara O(n), face un max-heap dintr-un vector neordonat.
   Procedura de sortare HeapSort, care are o complexitate O(n lg n), sorteaza un vector.
   Max-Heap-insert, Heap-Increase-Key au o complexitate O(lg n) si ajuta la implementarea unui priority queue.
   Algoritmul Build-Heap sau Bottom-Up are o complexitate O(n). Heapify pentru un singur nod are o complexitate
O(log n), unde n este numarul total de noduri. Pentru construirea intregului Heap se vor folosi n operatii si
complexitatea totala va fi O(n*log n).
   Algoritmul Heap-Sort sorteaza un array introdus ca data de intrare. Pe Worst are o complexitate O(nlog n)
pe Average are o complexitate O(n log n) si este instabil pentru ca operatiile pe heap pot schimba ordinea relativa a elementelor egale.
   Algoritmul Heapify are o complexitate O(log n).
   Algoritmul Heap-Increase pentru un heap de n elemente are o complexitate O(lg n).
   Insertion in Heap are o complexitate O(n).
   Top-Down are o complexitate O(n log n).
   Pe average, Bottom-up este mai eficient decat Top-down.
   Pe worst, Bottom-up este mai eficient decat Top-down.

*/
#include <stdio.h>
#include "Profiler.h"

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5

const int INF = 100000;
//int heap_size;
Profiler p("Heap");

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

void Heapify(int *array, int n, int i, Operation op) {
    int aux;
    int largest = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;
    op.count();
    if (left < n && array[left] > array[largest])
    {
        largest = left;
    } else largest = i;
    op.count();
    if (right < n && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != i) {
        op.count(3);
        swap(&array[largest], &array[i]);
        Heapify(array, n, largest,op);
    }

}

void BuildHeap(int array[], int n) {
    Operation op= p.createOperation("op_bottom", n);
    //index of last non-leaf node
    int i, index = (n / 2) - 1;
    //performs level order traversal from the last non-leaf node yo the root node and heapify the nodes
    for (i = index; i >= 0; i--) {
        Heapify(array, n, i,op);
    }
}

void HeapSort(int array[], int n) {
    Operation op= p.createOperation("op_heapsort", n);
    int aux, i;
    BuildHeap(array, n);
    for (i = n - 1; i >= 1; i--) {
        swap(&array[0], &array[i]);
        Heapify(array, i, 0, op);
    }
}

void IncreaseValue(int array[], int i, int value, Operation op) {

    op.count();
    array[i] = value;
    while (i > 0) {
        op.count();
        if (array[(i - 1) / 2] < array[i])
        { op.count(3);
            swap(&array[i], &array[(i-1)/2]);
            i = (i - 1) / 2;
        }
        else
            break;
    }
}

void BuildHeapMax(int array[], int n)
{ Operation op= p.createOperation("op_top", n);
    int i;
    int  heap_size = 0;
    for (i = 1; i < n; i++)
    {
        heap_size++;
        IncreaseValue(array,heap_size, array[i],op);
    }
}

void demo() {
    int array[] = {3, 2, 8, 5, 9, 1, 4};
    int array2[] = {3, 2, 8, 5, 9, 1, 4};
    int n = sizeof(array) / sizeof(array[0]);

    // Function call
    BuildHeap(array, n);
    printf("Bottom-up heap is\n");
    print(array, n);
    printf("\n");

    HeapSort(array, n);
    printf("Sorted heap is\n");
    print(array, n);
    printf("\n");

    BuildHeapMax(array2, n);
    printf("Top-down heap is\n");
    print(array2, n);
    printf("\n");

}

void heap_average(int order) {
    int arr[MAX_SIZE], arr1[MAX_SIZE];
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        int test;
        for (test = 0; test < NR_TESTS; test++) {
            FillRandomArray(arr, n, 10, 50000, false, order);
            CopyArray(arr1, arr, n);
            BuildHeap(arr, n);
            BuildHeapMax(arr1, n);

        }
    }
    //Bottom-up
    p.divideValues("op_bottom", NR_TESTS);
    p.divideValues("op_top", NR_TESTS);
    p.createGroup("Total_build_Average","op_bottom", "op_top");

    p.showReport();

}
void heap_worst(int order) {
    int arr[MAX_SIZE], arr1[MAX_SIZE];
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
            FillRandomArray(arr, n, 10, 50000, false, order);
            CopyArray(arr1, arr, n);
            BuildHeap(arr, n);
            BuildHeapMax(arr1, n);
    }

    p.createGroup("Total_build_Worst","op_bottom", "op_top");
    p.showReport();

}

void perf_all() {
    heap_average(UNSORTED);
    heap_worst(ASCENDING);
}

int main() {

    demo();
    perf_all();
}
