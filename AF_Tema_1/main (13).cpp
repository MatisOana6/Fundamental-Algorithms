/*
 Matiș Oana-Antonia
 Grupa 30228

 Am implementat 3 variante de algoritmi de sortare: Bubble Sort, Selection Sort si Insertion Sort

 Prima variantă implementată este Bubble Sort.
 Pe best case, atunci când elementele vectorului sunt aranjate în ordinea crescătoare a valorilor se parcurge vectorul o
 singură dată şi se execută n-1 comparaţii, avand o complexitate O(N).
 Pe worst case, atunci când elementele vectorului sunt aranjate în ordinea descrescătoare a valorilor, se
 execută  n(n-1)/2 operaţii de bază, iar elementele vectorului se parcurg de n ori, deci algoritmul este de ordinul O(N^2).
 Pe average case, complexitatea algoritmului este O(N^2).

 A doua variantă implementată este Selection Sort.
 Pe best case, algoritmul are o complexitate O(N^2).
 Pe worst case are o complexitate O(N^2).
 Pe average case are o complexitate O(N^2).

 A treia variantă implementată este Insertion Sort. Am ales să folosesc metoda de Binary Insertion Sort.
 Pe best case, algoritmul are complexitatea O(N log N).
 Pe worst case, algoritmul are complexitatea O(N^2).
 Pe average case, algoritmul are complexitatea O(N^2).

 Am observat că pe average case, cand am folosit aceleasi date de intrare pentu cele 3 metode de sortare, la partea de atribuiri, cel mai rapid
 algoritm a fost Binary Insertion Sort, la partea de comparații, cel mai bun algoritm a fost Binary Insertion Sort, la partea de total,
 cel mai bun algoritm a fost Binary Insertion Sort.

 Pe worst case, cel mai rapid algoritm a fost la partea de atribuiri, Selection Sort, la partea de comparații, Binary Insertion Sort
 si la partea de total, Selection Sort.

 Pe best case, cel mai rapid algoritm a fost la partea de atribuiri, Selection Sort, la partea de comparații, Bubble Sort și la partea de total,
 Bubble Sort.

 Pe average case, cand am generat date de intrare diferite pentru cele 3 metode de sortare, cel mai eficient algoritm la atribuiri a fost
 Selection Sort, la comparatii Binary Insertion Sort și la total Binary Insertion Sort.

*/
#include <stdio.h>
#include "Profiler.h"
#define MAX_SIZE 1000
#define STEP_SIZE 100
#define NR_TESTS 5

Profiler p("Average");

void print(int array[], int n)
{
    int i;
    for (i=0; i < n; i++)
        printf("%d ", array[i]);
}

void BubbleSort(int array[], int n)
{   Operation opComp=p.createOperation("array1-comp",n);
    Operation opAttr=p.createOperation("array1-attr",n);

    int i, j,aux,sorted=0;
    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {   opComp.count();
            if (array[j] > array[j+1])
            {   opAttr.count(3);
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

void SelectionSort(int array[], int n)
{
    Operation opComp=p.createOperation("array2-comp",n);
    Operation opAttr=p.createOperation("array2-attr",n);

    int i,j,min_position,aux;
    for(i=0;i<n-1;i++)
    {
        min_position=i;
        for(j=i+1;j<n;j++)
        { opComp.count();
            if(array[j]<array[min_position])
            {
                min_position=j;
            }
        }
        if(min_position!=i)
        {
            opAttr.count(3);
            aux = array[i];
            array[i] = array[min_position];
            array[min_position] = aux;
       }
    }
}
int BinarySearch(int const a[],int n, int beg, int end,int value)
{
    Operation opComp=p.createOperation("array3-comp",n);
    while (end >= beg)
    {
        int middle = (beg+end) / 2;
        opComp.count();
        if (a[middle] == value)
            return middle + 1;
        else
            opComp.count();
            if (a[middle] < value)
             beg=middle+1;
        else
            end=middle-1;
    }
    return beg;
}

 void BinaryInsertionSort(int array[], int n)
{
    Operation opComp=p.createOperation("array3-comp",n);
    Operation opAttr=p.createOperation("array3-attr",n);
    int i,j,value,location;
    for(i=1;i<n;i++)
    {   j=i-1;
        opAttr.count();
        value=array[i];
        location=BinarySearch(array,n,0,j,value);
        while(j>=location)
        {
            opAttr.count();
            array[j+1]=array[j];
            j--;
        }
        opAttr.count();
        array[j+1]=value;
    }
}

void perf1()
{
    int arr[MAX_SIZE];
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        int test;
        for (test = 0; test < NR_TESTS; test++) {
            FillRandomArray(arr, n);
            BubbleSort(arr, n);
            SelectionSort(arr,n);
            BinaryInsertionSort(arr,n);
        }
    }
    //Bubble Sort
    p.divideValues("array1-attr", NR_TESTS);
    p.divideValues("array1-comp", NR_TESTS);
    p.addSeries("array1", "array1-attr", "array1-comp");

    //Selection Sort
    p.divideValues("array2-attr", NR_TESTS);
    p.divideValues("array2-comp", NR_TESTS);
    p.addSeries("array2", "array2-attr", "array2-comp");

    //Binary Insertion Sort
    p.divideValues("array3-attr", NR_TESTS);
    p.divideValues("array3-comp", NR_TESTS);
    p.addSeries("array3", "array3-attr", "array3-comp");


    p.createGroup("Attributions","array1-attr","array2-attr","array3_attr");
    p.createGroup("Comparisons","array1-comp","array2-comp","array3-comp");
    p.createGroup("Total","array1","array2","array3");
    p.showReport();

}

void perf2(int order) {
    int arr[MAX_SIZE],arr1[MAX_SIZE],arr2[MAX_SIZE];
    int n;
    for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        int test;
        for (test = 0; test < NR_TESTS; test++) {
            FillRandomArray(arr, n,10, 50000,false,order);
            CopyArray(arr1,arr,MAX_SIZE);
            CopyArray(arr2,arr,MAX_SIZE);
            BubbleSort(arr, n);
            SelectionSort(arr1,n);
            BinaryInsertionSort(arr2,n);
        }
    }
    //Bubble Sort
    p.divideValues("array1-attr", NR_TESTS);
    p.divideValues("array1-comp", NR_TESTS);
    p.addSeries("array1", "array1-attr", "array1-comp");

    //Selection Sort
    p.divideValues("array2-attr", NR_TESTS);
    p.divideValues("array2-comp", NR_TESTS);
   p.addSeries("array2", "array2-attr", "array2-comp");

    //Binary Insertion Sort
    p.divideValues("array3-attr", NR_TESTS);
    p.divideValues("array3-comp", NR_TESTS);
    p.addSeries("array3", "array3-attr", "array3-comp");

    //total
    p.createGroup("Attributions","array1-attr","array2-attr","array3_attr");
    p.createGroup("Comparisons","array1-comp","array2-comp","array3-comp");
    p.createGroup("Total","array1","array2","array3");

}

void perf_all()
{
    perf2(UNSORTED);
    p.reset("Best");
    perf2(ASCENDING);
    p.reset("Worst");
    perf2(DESCENDING);
    p.showReport();
}

void demo()
{
    int a1[] = {16, 3, 25, 12, 11};
    int n1 = sizeof(a1)/sizeof(*a1);
    int a2[] = {10, 2, 27, 11, 9};
    int n2 = sizeof(a2)/sizeof(*a2);
    int a3[] = { 3, 65, 12, 10, 1};
    int n3 = sizeof(a3)/sizeof(*a3);

    BubbleSort(a1, n1);
    printf("The sorted array is: \n");
    print(a1, n1);

    SelectionSort(a2,n2);
    printf("\n");
    printf("The sorted array is: \n");
    print(a2, n2);

    BinaryInsertionSort(a3,n3);
    printf("\n");
    printf("The sorted array is: \n");
    print(a3, n3);
}

int main() {
    demo();
    perf1();
    perf_all();
    return 0;
}
