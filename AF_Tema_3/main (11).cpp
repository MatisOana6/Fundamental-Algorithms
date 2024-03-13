/*
Matiș Oana-Antonia
Grupa 30228

 Am implementat algoritmii: QuickSort, HeapSort, Bubble Sort-atat in varianta iterativa cat si in varianta recursiva si QuickSelection.
 QuickSort sau Sortarea rapidă este o metodă eficientă de sortare a unui array.Pentru un set de n valori oarecare algoritmul efectuează
 O(nlogn) comparații, dar în cazul cel mai nefavorabil se efectuează O(n^2) comparații.
 Algoritmul este de tip divide et impera; el sortează o secvență a tabloului (inițial întreg tabloul), astfel:
    -se alege un element special al listei, numit pivot;
    -se ordonează elementele listei, astfel încât toate elementele din stânga pivotului să fie mai mici sau egale cu acesta,
și toate elementele din dreapta pivotului să fie mai mari sau egale cu acesta;
    -se continuă recursiv cu secvența din stânga pivotului și cu cea din dreapta lui.
    Cea mai complexă problemă în cadrul algoritmului de sortare rapidă o reprezintă alegerea corectă a pivotului, căci corespunzător alegerii
corecte a pivotului algoritmul se comportă eficient.
    Complexitate: O(nlogn)
       - worst_case: O(n^2)
       - best_case: O(nlogn)- simple partition
                    O(n) - three way partition
       - average: O(nlogn)
       Nu este un algoritm stabil.

    Algoritmul Build-Heap sau Bottom-Up are o complexitate O(n).
    Heapify pentru un singur nod are o complexitate O(log n), unde n este numarul total de noduri. Pentru construirea intregului Heap se vor
folosi n operatii si complexitatea totala va fi O(n*log n).
   Algoritmul Heap-Sort sorteaza un array introdus ca data de intrare. Pe Worst are o complexitate O(nlog n)
pe Average are o complexitate O(n log n) si este instabil pentru ca operatiile pe heap pot schimba ordinea relativa a elementelor egale.
   Algoritmul Heapify are o complexitate O(log n).

   Am comparat cei doi algoritmi QuickSort si HeapSort si din compararea lor reiese faptul ca pe average, QuickSort este mai eicient decat HeapSort,
pe best, QuickSort este mai eficient, pe worst, HeapSort este mai eficient.

 Am implementat BubbleSort iterativ si recursiv.
 La Bubble Sort iterativ, pe best case, atunci când elementele vectorului sunt aranjate în ordinea crescătoare a valorilor se parcurge vectorul o singură dată şi se
 execută n-1 comparaţii, avand o complexitate O(N).
 Pe worst case, atunci când elementele vectorului sunt aranjate în ordinea descrescătoare a valorilor, se
 execută  n(n-1)/2 operaţii de bază, iar elementele vectorului se parcurg de n ori, deci algoritmul este de ordinul O(N^2).
 Pe average case, complexitatea algoritmului este O(N^2).
 La Bubble Sort iterativ, complexitatea este de O(n*n).
 Varianta iterativa este mai eficienta decat varianta recursiva.


*/
#include <iostream>
#include <stdio.h>
#include "Profiler.h"

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5

//int heap_size;
Profiler p("Tema3_HeapSort_QuickSort");

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
int Partition(int array[], int p, int r, Operation op1)
{
    op1.count();
 int pivot= array[r];
 int i=(p-1);
 for(int j=p;j<=r-1;j++)
{ op1.count();
    if(array[j]<pivot)
    {
        i=i+1;
        op1.count(3);
        swap(&array[i],&array[j]);
    }
}
 op1.count(3);
 swap(&array[i+1],&array[r]);
 return (i+1);
}

int Partition_best(int array[], int p, int r, Operation op1)
{
    op1.count();
    int pivot= array[(r-p)/2+p];
    int i=(p-1);
    for(int j=p;j<=r-1;j++)
    { op1.count();
        if(array[j]<pivot)
        {
            i=i+1;
            op1.count(3);
            swap(&array[i],&array[j]);
        }
    }
    op1.count(3);
    swap(&array[i+1],&array[r]);
    return (i+1);
}

// Standard partition process of QuickSort().
// It considers the last element as pivot
// and moves all smaller element to left of
// it and greater elements to right
int Partition_Select(int array[], int p, int r)
{

    int pivot= array[r];
    int i=(p-1);
    for(int j=p;j<=r-1;j++)
    {
        if(array[j]<pivot)
        {
            i=i+1;
            swap(&array[i],&array[j]);
        }
    }
    swap(&array[i+1],&array[r]);
    return (i+1);
}

void QuickSort(int array[], int min, int max, int n)
{
    Operation op1= p.createOperation("op_quickSort", n);
    if(min<max)
    {
        int q=Partition(array, min ,max,op1);
        QuickSort(array, min, q-1, n);
        QuickSort(array, q+1, max, n);
    }
}

void QuickSort_best(int array[], int min, int max, int n)
{
    Operation op1= p.createOperation("op_quickSort", n);
    if(min<max)
    {
        int q=Partition_best(array, min ,max,op1);
        QuickSort_best(array, min, q-1, n);
        QuickSort_best(array, q+1, max, n);
    }
}

// This function returns k'th smallest
// element in arr[left..right] using QuickSort
// based method
int QuickSelect(int array[], int left, int right, int k)
{
    if(k>0 && k<=(right-left+1))
    {
        int index=Partition_Select(array, left, right);
        if(index-left==k-1)
            return array[index];
        if(index-left>k-1)
            return QuickSelect(array, left, index-1, k);
        return QuickSelect(array, index+1, right, k-index+left-1);

    }


}

// HeapSort
void Heapify(int *array, int n, int i, Operation op) {

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

void BuildHeap(int array[], int n, Operation op) {
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
    BuildHeap(array, n, op);
    for (i = n - 1; i >= 1; i--) {
        swap(&array[0], &array[i]);
        Heapify(array, i, 0,op);
    }
}

void BubbleSort_iterative(int array[], int n)
{  Operation op= p.createOperation("op_bubble_it", n);
    int i, j,aux,sorted=0;
    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        { op.count();
            if (array[j] > array[j+1])
            { op.count(3);
                aux=array[j];
                array[j]=array[j+1];
                array[j+1]=aux;
                sorted++;
            }
        }
        if(sorted==0)
            break;
    }
}

void BubbleSort_recursive(int array[], int n, Operation op)
{
    int i;
    int sorted=0;
    for (i = 0; i < n-1; i++)
    {
        op.count();
        if (array[i] > array[i + 1])
        {
            op.count(3);
            swap(&array[i], &array[i + 1]);
            sorted++;
        }
    }
    if(sorted==0)
        return;
    BubbleSort_recursive(array,n-1,op);
}


void demo() {
    int array[] = {10, 7, 8, 9, 1, 5};
    int array2[] = {10, 7, 8, 9, 1, 5};
    int array3[] = {10, 4, 5, 8, 6, 11, 26};
    int n = sizeof(array) / sizeof(array[0]);
    int k = 3;
    Operation op= p.createOperation("op_bubble_rec", n);
    printf("Unsorted array:\n");
    print(array,n);
    printf("\n");

    QuickSort(array,0,n-1,n);
    printf("Quick sort:\n");
    print(array,n);
    printf("\n");

    HeapSort(array, n);
    printf("Heap sort:\n");
    print(array, n);
    printf("\n");

    BubbleSort_iterative(array, n);
    printf("Bubble sort iterative:\n");
    print(array, n);
    printf("\n");

    BubbleSort_recursive(array2, n,op);
    printf("Bubble sort recursive:\n");
    print(array2, n);
    printf("\n");

    printf("Quick select: %d ", QuickSelect(array3, 0, n-1,k));

}

void QuickSort_average(int order) {
    int arr[MAX_SIZE], arr1[MAX_SIZE];
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        int test;
        for (test = 0; test < NR_TESTS; test++) {
            FillRandomArray(arr, n, 10, 50000, false, order);
            CopyArray(arr1, arr, n);
            QuickSort(arr,0,n-1,n);
            HeapSort(arr1,n);

        }
    }
    //QuickSort and Heapsort in average
    p.divideValues("op_quickSort", NR_TESTS);
    p.divideValues("op_heapsort", NR_TESTS);
    p.createGroup("Total_build_Average", "op_quickSort", "op_heapsort");
    p.showReport();

}
void QuickSort_worst(int order) {
    int arr[MAX_SIZE], arr1[MAX_SIZE];
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        FillRandomArray(arr, n, 10, 50000, false, order);
       CopyArray(arr1, arr, n);
        QuickSort(arr,0,n-1,n);
        HeapSort(arr1,n);
    }
    p.createGroup("Total_build_Worst","op_quickSort", "op_heapsort");
    p.showReport();

}
void interschimbare(int array1[],int array2[], int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        array2[i]=array1[n-i-1];
    }
}


void QuickSort_best(int order) {
    int arr[MAX_SIZE], arr1[MAX_SIZE];
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        FillRandomArray(arr, n, 10, 50000, false, order);
        //CopyArray(arr1, arr, n);
        interschimbare(arr,arr1,n);
        HeapSort(arr1,n);
        QuickSort_best(arr,0,n-1,n);
    }
    p.createGroup("Total_build_Best","op_quickSort", "op_heapsort");
    p.showReport();
}

void perf_all()
{
    QuickSort_average(UNSORTED);
    QuickSort_best(ASCENDING);
    QuickSort_worst(ASCENDING);
}

void Bubble_Sort_helper(int array[], int n)
{
    Operation op= p.createOperation("op_bubble_rec", n);
    BubbleSort_recursive(array,n,op);
}

void BubbleSort_average(int order) {
    int arr[MAX_SIZE], arr1[MAX_SIZE];
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        int test;
        for (test = 0; test < NR_TESTS; test++) {
            FillRandomArray(arr, n, 10, 50000, false, order);
            CopyArray(arr1, arr, n);
            BubbleSort_iterative(arr,n);
            Bubble_Sort_helper(arr1,n);

        }
    }
    //BubbleSort
    p.divideValues("op_bubble_it", NR_TESTS);
    p.divideValues("op_bubble_rec", NR_TESTS);
    p.createGroup("Total_Bubble_Average", "op_bubble_it", "op_bubble_rec");
    p.showReport();

}

void BubbleSort_time(int order) {
    int arr[MAX_SIZE], arr1[MAX_SIZE], arr2[MAX_SIZE];
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        int test;
        FillRandomArray(arr, n, 10, 50000, false, order);
        CopyArray(arr1, arr, n);
        CopyArray(arr2, arr, n);
        p.startTimer("Bubble_iterative", n);
        for (test = 0; test < NR_TESTS; test++)
        {
            BubbleSort_iterative(arr,n);
            CopyArray(arr, arr2, n);
            //BubbleSort_recursive(arr1,n);
        }
        p.stopTimer("Bubble_iterative", n);

        p.startTimer("Bubble_recursive", n);
        for (test = 0; test < NR_TESTS; test++)
        {
            Bubble_Sort_helper(arr1,n);
            CopyArray(arr1, arr2, n);
        }
        p.stopTimer("Bubble_recursive", n);
    }
    //BubbleSort
    p.divideValues("Bubble_iterative", NR_TESTS);
    p.divideValues("Bubble_recursive", NR_TESTS);
    p.createGroup("Total_Bubble_TIME", "Bubble_iterative", "Bubble_recursive");
    p.showReport();

}

void perf_Bubble()
{
    BubbleSort_average(UNSORTED);
    BubbleSort_time(UNSORTED);
}

int main()
{
   demo();
   perf_all();
   perf_Bubble();
    return 0;
}
