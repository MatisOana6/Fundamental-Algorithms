/*
Matiș Oana-Antonia
Grupa 30228

    Am implementat operatiile de inserare, cautare si stergere intr-un hash table.
    Am generat o functie de hash care preia o valoare si o insereaza pe o anuminta pozitie in hash table.
    Folosesc functia de hash pentru a umple un tabel de marime fixa, adica hash table.
    Am folosit adresarea deschisa, care se refera la faptul ca adresa finală (poziția finală) nu este complet determinata
de către codul hash; poziția depinde și de elementele care sunt deja în tabela. ex: linear/quadratic probing (verificare liniara/patratica)
    Am folosit verificarea patratica, care se refera la faptul ca se poate stoca doar un singur element pe o anumita pozitie.
    Pentru functiile de insert, delete, complexitatea este O(1).
    De asemenea, pentru functia de search, complexitatea este O(1).

    Efort mediu = efort_total / nr_elemente
    Efort maxim = număr maxim de accese efectuat de o operație de căutare

    Am realizat evaluarea operației de căutare în tabele de dispersie cu adresare deschisa și
verificare pătratică, în cazul mediu statistic si rezultatele cautarii sunt afisate in tabel pentru factorii de umplere:0.8, 0.85, 0.9, 0.95, 0.99.
    Efortul mediu la elementele gasite creste liniar si are valori mici.
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Profiler.h"

#define MAX_SIZE 10007

typedef struct
{
    int id;
    char nume[30];

}entry;

int hash_function(int key, int size)
{ //sa aiba grija ca elemntul pe care il pun sa nu fie in afara hash-ului
    return (key%size);
}

int hash_function2(int key, int size, int i)
{
    return (hash_function(key,size)+2*i+3*i*i)%size;
}

void hash_init(entry *v, int size)
{
    for(int i=0;i<size;i++)
        v[i].id=NULL;
    //parcurge vectorul si face elementele intregi din vector nule -- id devine null
}

void hash_insert(entry *v, int size, int value)
{
    int i=0;
    do
    {
        int j=hash_function2(value,size,i);
        if(v[j].id==NULL || v[j].id==-1)
        {
            v[j].id=value;
            return ;
        }
        else i=i+1;//daca exista o valoare pe pozitia din vector atunci trece la pozitia urmatoare
    } while(i<=size);
            //printf("Hash table overflow");

}

int hash_search(entry *v, int size, int value) {
    int i = 0, j;
    do {
        j=hash_function2(value,size,i);
        if(v[j].id==value)
        {
            return j;
        }
        else i=i+1;
    } while(v[j].id!=NULL && i!=size);
    return -1;
}

void hash_delete(entry *v, int size, int value) {
    int i = 0, j;
    do {
        j=hash_function2(value,size,i);
        if(v[j].id==value)
        {
            strcpy(v[j].nume, "deleted");
            v[j].id=NULL;
            return;
        }
        else i=i+1;
    } while(v[j].id!=NULL && i!=size);
    return ;
    printf("element not found");
}

void hash_print(entry *v, int size)
{
    for(int i=0;i<size;i++)
    { if(v[i].id!=NULL)
        printf("%d ", v[i].id);
        else
            printf("- ");
    }
}

int hash_search_count(entry *v, int size, int value) {
    int i = 0, j;
    do {
        j=hash_function2(value,size,i);
        if(v[j].id==value)
        {
            return i+1;//i=nr iteratii, i+1=nr parcurgeri
        }
        else i=i+1;
    } while(v[j].id!=NULL  && i!=size);
    return i+1;
}


int factor_umplere(entry *v, int size, float f)
{
    float nr_elem = size * f;//f-factorul de umplere se inmulteste cu size de hash
    int a[size];
    FillRandomArray(a, (int) nr_elem, 0, 30);//genereaza nr de elemente in functie de factorul de umplere
    hash_init(v,size);//intializeaza cu 0 vectorul
    for (int i = 0; i < (int) nr_elem; i++) //parcurge si insereaza elementele care s-au generat random in functie de factorul de umplere
    {
        hash_insert(v, size, a[i]);
    }
}

int factor_de_umplere(entry *v, int size, float f) {
    float nr_elem = size * f;//f-factorul de umplere se inmulteste cu size de hash
    int a[MAX_SIZE];
    int k;
    int negasite[MAX_SIZE];
    float efort_maxim_gasite=0, efort_mediu_gasite=0, efort_maxim_negasite=0, efort_mediu_negasite=0;
    printf("                                                 \n");
    for (k = 0; k < 5; k++) //face 5 teste
         {
        FillRandomArray(a, (int) nr_elem, 1, 30000);//genereaza nr de elemente in functie de factorul de umplere
        hash_init(v,MAX_SIZE);//intializeaza cu 0 vectorul
        for (int i = 0; i < (int) nr_elem; i++) //parcurge si insereaza elementele care s-au generat random in functie de factorul de umplere
        {
            hash_insert(v, size, a[i]);
        }
        for (int i = 0; i < 1500; i++) //selectez random 1500 de elemente pe care stiu ca exista in hash table
        {
            int contor;
            int index = rand() % (int) nr_elem;// iau o pozitie random din vectorul de elemente random
            contor = hash_search_count(v, size, a[index]);//returneaza numarul de pozitii accesate in procesul de cautare al valorii cautate
            if(efort_maxim_gasite<contor)
            {
                efort_maxim_gasite=contor;
            }
            efort_mediu_gasite+=contor;//se aduna contorul pentru cazul mediu
        }

        FillRandomArray(negasite, (int) nr_elem, 30001, 50000);//generez element despre care stiu ca nu exista in hash
        for (int i = 0; i < 1500; i++) {
            int contor;
            contor = hash_search_count(v, size, negasite[i]);//returneaza numarul de pozitii accesate in procesul de cautare al elementelor
            if(efort_maxim_negasite<contor) {
                efort_maxim_negasite=contor;
            }
            efort_mediu_negasite+=contor;
        }
    }
    efort_mediu_gasite=(efort_mediu_gasite/(1500.0*5));//impart la 1500 pentru average
    efort_mediu_negasite=(efort_mediu_negasite/(1500.0*5));
    printf("|     %.0f \t|     %.2f  \t|      %.0f\t|     %.2f \t|", efort_maxim_gasite, efort_mediu_gasite, efort_maxim_negasite, efort_mediu_negasite);
}

int factor_de_umplere_delete(entry *v, int size, float f) {
    float nr_elem = size * f;//f-factorul de umplere se inmulteste cu size de hash
    int a[MAX_SIZE];
    int k;
    int negasite[MAX_SIZE];
    float efort_maxim_gasite=0, efort_mediu_gasite=0, efort_maxim_negasite=0, efort_mediu_negasite=0;
    for (k = 0; k < 5; k++) //face 5 teste
    {
        FillRandomArray(a, (int) nr_elem, 1, 30000);//genereaza nr de elemente in functie de factorul de umplere
        hash_init(v,MAX_SIZE);//intializeaza cu 0 vectorul
        for (int i = 0; i < (int) nr_elem; i++) //parcurge si insereaza elementele care s-au generat random in functie de factorul de umplere
        {
            hash_insert(v, size, a[i]);
        }
        for (int i = 0; i < 1900; i++) //selectez random 1900 de elemente pe care stiu ca exista in hash table
        {
            int contor;
            int index = rand() % (int) nr_elem;// iau o pozitie random din vectorul de elemente random
            hash_delete(v,size,a[index]);
        }

        for (int i = 0; i < 1500; i++) //selectez random 1500 de elemente despre care stiu ca exista in hash table
        {
            int contor;
            int index = rand() % (int) nr_elem;// iau o pozitie random din vectorul de elemente random
            contor = hash_search_count(v, size, a[index]);//returneaza numarul de pozitii accesate in procesul de cautare al valorii cautate
            if(efort_maxim_gasite<contor)
            {
                efort_maxim_gasite=contor;
            }
            efort_mediu_gasite+=contor;//se aduna contorul pentru cazul mediu
        }

        FillRandomArray(negasite, (int) nr_elem, 30001, 50000);//generez element despre care stiu ca nu exista in hash
        for (int i = 0; i < 1500; i++) {
            int contor;
            contor = hash_search_count(v, size, negasite[i]);//returneaza numarul de pozitii accesate in procesul de cautare al elementelor
            if(efort_maxim_negasite<contor)
            {
                efort_maxim_negasite=contor;
            }
            efort_mediu_negasite+=contor;
        }
    }
    efort_mediu_gasite=(efort_mediu_gasite/(1500.0*5));//impart la 1500 pentru average
    efort_mediu_negasite=(efort_mediu_negasite/(1500.0*5));
    printf("|        %.0f      \t|          %.2f     \t|           %.0f            \t|           %.2f       \t|", efort_maxim_gasite, efort_mediu_gasite, efort_maxim_negasite, efort_mediu_negasite);
    printf("\n");
}

void demo_search()
{
  entry v[10];
  int size=5;
  hash_init(v,size);
  hash_insert(v, size, 1);
  hash_insert(v, size, 2);
  hash_insert(v, size, 2);
  hash_insert(v, size, 4);
  //hash_print(v,size);
  printf("%d ",hash_search(v,size,2));

}
void demo_delete()
{
    entry v[10];
    int size=5;
    hash_init(v,size);
    hash_insert(v, size, 1);
    hash_insert(v, size, 2);
    hash_insert(v, size, 2);
    hash_insert(v, size, 4);
    hash_print(v,size);
    printf("\n");
    hash_delete(v,size, 2);
    hash_print(v,size);
}

void demo_umplere()
{
    entry v[20];
    int size=10;
    hash_init(v,size);
    factor_umplere(v,size, 0.95);
    hash_print(v, size);
}

void perf()
{
    entry v[MAX_SIZE];
    printf("-----------------------------------------------------------------\n");
    printf("| efort maxim \t|  efort mediu \t|  efort maxim \t|  efort mediu\t|\n");
    printf("|   gasite \t|    gasite \t|   negasite \t|   negasite\t|");
    printf("\n-----------------------------------------------------------------");
    hash_init(v,MAX_SIZE);
    factor_de_umplere(v,MAX_SIZE, 0.8);
    hash_init(v,MAX_SIZE);
    factor_de_umplere(v,MAX_SIZE, 0.85);
    hash_init(v,MAX_SIZE);
    factor_de_umplere(v,MAX_SIZE, 0.9);
    hash_init(v,MAX_SIZE);
    factor_de_umplere(v,MAX_SIZE, 0.95);
    hash_init(v,MAX_SIZE);
    factor_de_umplere(v,MAX_SIZE, 0.99);
    printf("\n-----------------------------------------------------------------");
}

void perf_delete()
{
    entry v[MAX_SIZE];
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("| efort maxim gasite \t|  efort mediu gasite \t|  efort maxim negasite \t|  efort mediu negasite\t|\n");
    printf("|    stergere   \t|      stergere \t|       stergere         \t|           stergere  \t|");
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    factor_de_umplere_delete(v,MAX_SIZE,0.99);
    printf("---------------------------------------------------------------------------------------------------------\n");
}

int main()
{
    demo_search();
    demo_delete();
    demo_umplere();
    perf();
    perf_delete();

}
