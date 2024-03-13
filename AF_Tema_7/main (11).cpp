/* Matiș Oana-Antonia
 * Grupa 30228
 * Am implementat operațiile de management ale unui arbore de statistică de ordine: build, select si delete.
 * Am folosit un arbore binar de cautare perfect echilibrat.
 * Pentru implementarea algoritmului de build_tree am folosit metoda divide et impera.
 * Pentru operatia de OS_SELECT am folosit pseudocodul din Cormen pentru a gasi al i-lea cel mai mic element.
 * Pentru a implementa operatia de delete am folosit algoritmul de stergere de la arborii binari de cautare de la SDA.
 * Complexitatea algoritmului de OS_SELECT este O(lgn).
 * In general, complexitatea operatiei de OS_DELETE ARE COMPLEXITATEA O(h), iar pe worst are complexitatea O(n).
 * Inaltimea este de complexitate O(lg n)
 * OS_DELETE -> sterge un nod.
	cazul1 : no sons -> delete
	cazul2 : 1 son -> delete node and update links to son
	cazul3 : 2 sons -> find min in the right subtree, swap keys and delete that min

 *
 */
#include <iostream>
#include <stdio.h>
#include "Profiler.h"

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5
Profiler p("Statistici dinamice de ordine");

typedef struct binarySearchTree
{
    int data;
    struct binarySearchTree *left;
    struct binarySearchTree *right;
    int size;
}binarySearchTree;

binarySearchTree *buildTree(int left, int right,Operation op)
{

//Am folosit metoda divide et impera
    binarySearchTree *node = (binarySearchTree *)(malloc(sizeof (binarySearchTree)));
   op.count();
   if(left>right)
   return NULL;
   else
   {
      int middle=(left+right)/2;
      op.count(2);
      node->data=middle;
      node->size=1;

      op.count(2);
      node->left=buildTree(left,middle-1,op);
      node->right=buildTree(middle+1,right,op);

      op.count();
      if(node->left!=NULL)
      {
          op.count();
          node->size+=node->left->size;
      }
     op.count();
      if(node->right!=NULL)
      {
          op.count();
          node->size+=node->right->size;
      }
      return node;
   }
}

void binarySearchTree_preorder(binarySearchTree *node, int space) {
    if (node != NULL) {
       for (int i = 0; i < space; i++)
            printf("   ");
        printf("%d\n ", node->data);
        binarySearchTree_preorder(node->left, space+1);
        binarySearchTree_preorder(node->right, space+1);
    }
}

binarySearchTree *OS_SELECT(binarySearchTree *node, int i,Operation op) {
    int rank;
    op.count();
    if (node == NULL)
        return NULL;
    else if (node!=NULL)
       {op.count();
        if(node->left!=NULL)
        { //node->left->size+1 is the rank of binarySearchTree node within the subtree rooted at node.
            op.count();
            rank = node->left->size + 1;
        }
        else
        {
            rank=1;
        }
        if (i == rank)
            return node;//if(i==rank), then node is the ith smallest element, and so we return node
        else if (i < rank)
            return OS_SELECT(node->left,i, op);//i < r, then the ith smallest element resides in node’s left subtree, and so we recurse on node->left
            else return OS_SELECT(node->right, i - rank,op);//i > r, then the ith smallest element resides in node’s right subtree.
            //the ith smallest element in the subtree rooted at node is the (i-r)th smallest element in the subtree rooted at x:right
    }
}

//this function returns the node with the minimum key value found in the tree
binarySearchTree *minKeyValue(binarySearchTree *node,Operation op)
{
    binarySearchTree *newNode = node;
    //loop down to find the leftmost leaf
    op.count();
    while(newNode && newNode->left !=NULL)
    {
        op.count();
        newNode=newNode->left;
    }
    return newNode;
}

void binarySearchTree_free(binarySearchTree *node)
{
    if(node != NULL){
        binarySearchTree_free(node->left);
        binarySearchTree_free(node->right);
        free(node);
    }
}

binarySearchTree *OS_DELETE(binarySearchTree *node, int value,Operation op) {
    op.count(2);
    if (node == NULL)
        return NULL;
     else if(node!=NULL)
     { //If the value we want to delete is smaller than the root's key, then it lies in left subtree
        op.count(2);
         if (value < node->data)
        {
            node->left = OS_DELETE(node->left, value,op);
            node->size--;
            op.count();
        }
            //If the value we want to delete is greater than the root's key, then it lies in right subtree
        else if (value > node->data)
        {
            node->right = OS_DELETE(node->right, value,op);
            node->size--;
            op.count();

        }//if the value we want to delete is equal to the root's key then this is the node that will be deleted
        else
        { //nodes with one or more children
            op.count(2);
            if (node->left != NULL && node->right != NULL)
            {
                binarySearchTree *newNode = minKeyValue(node->right,op);// node with two children:
                // Get the inorder successor (smallest in the right subtree)
                node->data = newNode->data;//copy the inorder succesor's data to this new node
                node->right = OS_DELETE(node->right, newNode->data,op);//delete the inorder successor
                op.count(2);
            }
            else
            { //node with no or only one child
                op.count();
                if (node->left == NULL)
                {
                    binarySearchTree *newNode = node->left;
                    free(newNode);
                    return newNode;
                }
                    //node with no or only one child
                else if (node->right == NULL)
                {
                    binarySearchTree *newNode = node->right;
                    free(newNode);
                    return newNode;
                }
            }
        }
    }
     return node;
}

void demo() {
    Operation op= p.createOperation("op", 3);
    binarySearchTree *node = NULL;
    int size = 11;
    node = buildTree(1, size,op);
    binarySearchTree_preorder(node, 0);
    printf("\n");

    int i = 2;
    printf("OS select for the %d key is: %d", i, OS_SELECT(node, i,op)->data,op);
    printf("\n");

    int j = 3;
    printf("OS select for the %d key is: %d", j, OS_SELECT(node, j,op)->data,op);
    printf("\n");

    int k = 4;
    printf("OS select for the %d key is: %d", k, OS_SELECT(node, k,op)->data,op);
    printf("\n");

    int del1 = 8;
    printf("Elementul care va fi sters este: %d\n", del1);
    node = OS_DELETE(node, OS_SELECT(node, del1,op)->data,op);
    binarySearchTree_preorder(node, 0);

    int del2 = 6;
    printf("Elementul care va fi sters este: %d\n", del2);
    node = OS_DELETE(node, OS_SELECT(node, del2,op)->data,op);
    binarySearchTree_preorder(node, 0);

    int del3 = 5;
    printf("Elementul care va fi sters este: %d\n", del3);
    node = OS_DELETE(node, OS_SELECT(node, del3,op)->data,op);
    binarySearchTree_preorder(node, 0);

}

void perf()
{
    int size ;
    int n,arr[MAX_SIZE];
    for ( n = STEP_SIZE; n <= MAX_SIZE; n+= STEP_SIZE)
    {   int test;
        for (test = 0; test < NR_TESTS; test++) {
            //Operation op_1 = p.createOperation("Operatiii Select", n);
           // Operation op_2 = p.createOperation("Operatii Delete", n);
            Operation op_3 = p.createOperation("Operatii Build", n);
            binarySearchTree *node = NULL;
            node = buildTree(0, n-1,op_3);
            binarySearchTree *val = OS_SELECT(node,n,op_3);
            node = OS_DELETE(node, val->data, op_3);
        }
    }
    //p.divideValues("Operatii Select", NR_TESTS);
   // p.divideValues("Operatii Delete", NR_TESTS);
    p.divideValues("Operatii Build", NR_TESTS);
   // p.createGroup("operatii", "Operatii Select", "Operatii Delete","Operatii Build");
    p.showReport();

}

int main()
{
   demo();
  // perf();
    return 0;
}
