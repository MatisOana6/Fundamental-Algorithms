/*
Matis Oana-Antonia
Grupa 30228

    Am implementat transformarea din vector parinte in arbore multicai si transformarea din arbore multicai in
arbore binar. Am folosit afisarea pretty print pentru reprezentarea parinte, reprezentarea arbore multicai si
reprezentarea binara. Pentru reprezentarea binara am folosit functia preorder.
    Complexitatea pentru transformarea din parinte in arbore multicai este O(n^2).
    Complexitatea pentru transformarea din arbore multicai in arbore binar este O(n).

*/
#include <iostream>
#include <stdio.h>

typedef struct binaryTree
{
    int data;
    struct binaryTree *child;
    struct binaryTree *sibling;
}binaryTree;

binaryTree *binaryTree_new(int data)
{
    binaryTree *tree =(binaryTree*) calloc(1, sizeof (binaryTree));
    tree->data= data;
    tree->child = NULL;
    tree->sibling = NULL;
    return tree;
}

void binaryTree_free(binaryTree *tree)
{
    if(tree != NULL){
        binaryTree_free(tree->child);
        binaryTree_free(tree->sibling);
        free(tree);
    }
}

void prettyPrintParent(int *array, int n, int parent, int numberOfSpaces) // Reprezentare vector parinti
    {
        int q = 0;
        for (int i = 0; i < n; i++)
        {
            if (array[i] == parent)
            {
                if (q != i + 1 && q != 0)
                {
                    numberOfSpaces--;
                }
                for (int j = 0; j < numberOfSpaces; j++)
                {
                    printf("    ");
                }
                numberOfSpaces++;
                q = i + 1;
                printf("%d\n", q);
                prettyPrintParent(array, n, q, numberOfSpaces);
            }
        }
    }

typedef struct multiWayTree
{  int data;
   int childCount;
   struct multiWayTree **children;
}multiWayTree;

multiWayTree *multiWayTree_new(int data)
{
    multiWayTree *mtree =(multiWayTree*) calloc(1, sizeof (multiWayTree));
    mtree->children = (multiWayTree**) calloc(10, sizeof (multiWayTree*));
    mtree->data= data;
    mtree->childCount = 0;
    return mtree;
}

multiWayTree *Transformare1(int *array, int size, int radacina)
{
    multiWayTree *root= multiWayTree_new(radacina);
    for(int i=0; i<size; i++)
    {
        if(array[i]==radacina) {
            root->children[root->childCount] = Transformare1(array, size, i + 1);
            root->childCount++;
        }
    }
    return root;
}

void prettyPrintR2(multiWayTree *mtree, int space)
{
  if(mtree==NULL)
{
    return;
}
  else
  {   for(int i=0; i<space; i++)
      printf("   ");
      printf("%d\n", mtree->data);
  for(int j=0;j<mtree->childCount; j++)
     {
      prettyPrintR2(mtree->children[j], space+1);
     }
  }
}

binaryTree *Transformare2(multiWayTree *tree)
{
    if(tree!=NULL) {
        binaryTree *nodebt = binaryTree_new(tree->data);
        nodebt->child = Transformare2(tree->children[0]);
        for(int i=1; i<tree->childCount;i++)
        {
            binaryTree *nodsuplimentar = nodebt->child;
            while(nodsuplimentar->sibling!=NULL)
            {
                nodsuplimentar=nodsuplimentar->sibling;
            }
            nodsuplimentar->sibling= Transformare2(tree->children[i]);
        }
        return nodebt;
    }
    else
        return NULL;

}

void binaryTree_preorder(binaryTree *tree, int space)
{
    if(tree != NULL) {
        for(int i=0; i<space; i++)
            printf("   ");
        printf("%d\n", tree->data);
        binaryTree_preorder(tree->child, space+1);
        binaryTree_preorder(tree->sibling, space);
    }
}

void demo()
{
    int v[]={2, 7, 5, 2, 7, 7, -1, 5, 2};
    int n=sizeof(v)/sizeof(int);
    prettyPrintParent(v,n,-1,0);
    printf("\n");

    multiWayTree *root = Transformare1(v,n,7);
    prettyPrintR2(root, 0); // 0 = Numar de Spatii
    printf("\n");

    binaryTree *root2 = Transformare2(root);
    binaryTree_preorder(root2, 0); // 0 = Numar de Spatii
    printf("\n");

}

int main() {
    demo();
    return 0;
}
