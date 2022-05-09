#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char AM[9];
    char onoma[11];
    char lname[11];
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
    for(i=0;i<3;i++)
    {
        printf("Give am:");
        scanf("%s",student.AM);
        BSTSearch(ARoot,student,&found,&LocPtr,&num);
        if(found==TRUE)
            printf("komboi=%d AM=%s Onoma=%s Epwnymo=%s\n",num,LocPtr->Data.AM,LocPtr->Data.onoma,LocPtr->Data.lname);
        else
            printf("komboi=%d o foithths den brethike sto DDA\n",num);

    }


    return 0;
}
void InorderTraversal(BinTreePointer Root)
{
    if (Root!=NULL) {
        InorderTraversal(Root->LChild);
        printf("AM:%s Onoma:%s Epwnymo:%s\n",Root->Data.AM,Root->Data.onoma,Root->Data.lname);
        InorderTraversal(Root->RChild);
    }
}
void BuildBST(BinTreePointer *Root)
{
    FILE *infile;
    BinTreeElementType student;

    CreateBST(&(*Root));
    infile=fopen("i31f5.txt ","r");
    if(infile==NULL) printf("Problem Opening File");
    else
        while(!feof(infile))
        {

            fscanf(infile,"%s%s%s ",student.AM, student.onoma, student.lname);
            //printf("AM:%s Onoma:%s Epwnymo:%s\n",student.AM,student.onoma,student.lname);
            BSTInsert(Root,student);
        }
    fclose(infile);
}
void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr, int *nodes)
{
    boolean stop;

    *LocPtr = Root;
    stop = FALSE;
    (*nodes)=0;
    while (!stop && *LocPtr != NULL)
    {
        (*nodes)++;
        if (strcmp(KeyValue.AM,(*LocPtr)->Data.AM)<0)
            *LocPtr = (*LocPtr)->LChild;
        else
            if (strcmp(KeyValue.AM, (*LocPtr)->Data.AM)>0)
                *LocPtr = (*LocPtr)->RChild;
            else stop = TRUE;
    }
   *Found=stop;
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
        if (strcmp(Item.AM, LocPtr->Data.AM)<0)
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
        else if (strcmp(Item.AM,Parent ->Data.AM)<0)
            Parent ->LChild = LocPtr;
        else
            Parent ->RChild = LocPtr;
    }
}
