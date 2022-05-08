#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char AM[8];
    char fname[10];
    char lname[10];
}BinTreeElementType;

typedef struct BinTreeNode *BinTreePointer;
typedef struct BinTreeNode {
    BinTreeElementType Data;
    BinTreePointer LChild, RChild;
} BinTreeNode;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateBST(BinTreePointer *Root);
boolean EmptyBST(BinTreePointer Root);
void BSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr, int *nodes);
void BuildBST(BinTreePointer *Root);
void InorderTraversal(BinTreePointer Root);

int main()
{
    BinTreePointer ARoot, LocPtr;
    int num, i;
    BinTreeElementType student;
    boolean found;

    BuildBST(&ARoot);
    InorderTraversal(ARoot);
    printf("\n");
    for(i=0;i<3;i++)
    {
        printf("Give am:");
        scanf("%s",student.AM);
        getchar();
        BSTSearch(ARoot,student,&found,&LocPtr,&num);
        printf("komboi:%d ",num);
        if(found==TRUE)
            printf("AM:%s Onoma:%s Epwnymo:%s\n",ARoot->Data.AM,ARoot->Data.fname,ARoot->Data.lname);
        else
            printf(" o foithths den brethike sto DDA\n");

    }


    return 0;
}
void InorderTraversal(BinTreePointer Root)
/* Δέχεται:    Ένα δυαδικό δέντρο με το δείκτη Root να δείχνει στην ρίζα του.
   Λειτουργία: Εκτελεί ενδοδιατεταγμένη διάσχιση του δυαδικού δέντρου και
                επεξεργάζεται κάθε κόμβο ακριβώς μια φορά.
   Εμφανίζει: Το περιεχόμενο του κόμβου, και εξαρτάται από το είδος της επεξεργασίας
*/
{
    if (Root!=NULL) {
        InorderTraversal(Root->LChild);
        printf("%s %s %s",Root->Data.AM,Root->Data.fname,Root->Data.lname);
        InorderTraversal(Root->RChild);
    }
}
void BuildBST(BinTreePointer *Root)
{
    FILE *infile;
    BinTreeElementType student;
    int nscan;
    char temch;

    CreateBST(Root);
    infile=fopen("i31f5.txt ","r");
    if(infile==NULL) printf("Problem Opening File");
    else
        while(!feof(infile))
        {
            nscan=fscanf(infile,"%[^ ]%[^ ]%[^ ]%c ",student.AM, student.fname, student.lname,&temch);
            if(nscan!=4 || temch!='\n') exit(1);
            BSTInsert(Root,student);
        }
    fclose(infile);
}
void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr, int *nodes)
{
    (*LocPtr) = Root;
    (*Found) = FALSE;
    *nodes=1;
    while (!(*Found) && (*LocPtr) != NULL)
    {
        if (strcmp(KeyValue.AM,(*LocPtr)->Data.AM)<0)
        {
            (*LocPtr) = (*LocPtr)->LChild;
            *nodes++;
        }
        else if (strcmp(KeyValue.AM,(*LocPtr)->Data.AM)>0)
        {
            (*LocPtr) = (*LocPtr)->RChild;
            *nodes+=2;
        }
        else (*Found) = TRUE;
    }
}

void CreateBST(BinTreePointer *Root)
{
    *Root = NULL;
}

boolean EmptyBST(BinTreePointer Root)
{   return (Root==NULL);
}

void BSTInsert(BinTreePointer *Root, BinTreeElementType Item)
{
    BinTreePointer LocPtr, Parent;
    boolean Found;

    LocPtr = *Root;
    Parent = NULL;
    Found = FALSE;
    while (!Found && LocPtr != NULL) {
        Parent = LocPtr;
        if (strcmp(Item.AM,LocPtr->Data.AM)<0)
            LocPtr = LocPtr ->LChild;
        else if (strcmp(Item.AM,LocPtr ->Data.AM)>0)
            LocPtr = LocPtr ->RChild;
        else
            Found = TRUE;
    }
    if (Found)
        printf("TO STOIXEIO EINAI HDH STO DDA\n");
    else {
        LocPtr = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        LocPtr ->Data = Item;
        LocPtr ->LChild = NULL;
        LocPtr ->RChild = NULL;
        if (Parent == NULL)
            *Root = LocPtr;
        else if (strcpy(Item.AM, Parent ->Data.AM)<0)
            Parent ->LChild = LocPtr;
        else
            Parent ->RChild = LocPtr;
    }
}

