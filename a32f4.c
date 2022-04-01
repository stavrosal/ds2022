#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char onoma[20];
    int gymnasio;
}ListElementType;

typedef enum {
    FALSE, TRUE
} boolean;

#define NumberOfNodes 10
#define NilValue -1

typedef int ListPointer;

typedef struct {
    ListElementType Data;
    ListPointer  Next;
} NodeType;

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr);
void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
boolean FullList(ListPointer FreePtr);
void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[]);
void ReleaseNode(NodeType Node[NumberOfNodes], ListPointer P, ListPointer *FreePtr);
void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr,char Item1[],int Item2);
void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr,char Item1[],int *Item2);
void TraverseLinked(ListPointer List, NodeType Node[]);
void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[]);

int main()
{
    FILE* infile;
    int nscan,number,number1,i;
    char temch,ono[20];
    NodeType fashA[NumberOfNodes],fashB[NumberOfNodes];
    ListPointer alist,afreeptr,apreptr=NilValue,blist,bfreeptr,bpreptr=NilValue,currptr;

    infile=fopen("students.dat","r");
    if(infile==NULL) exit(1);
    InitializeStoragePool(fashA,&afreeptr);
    InitializeStoragePool(fashB,&bfreeptr);
    CreateList(&alist);
    CreateList(&blist);
    while(TRUE){
        nscan=fscanf(infile,"%[^\n]%c%d%c",ono,&temch,&number,&temch);
        if(nscan==EOF) break;
        if(nscan!=4 || temch!='\n') exit(2);
        Insert(&alist,fashA,&afreeptr,apreptr,ono,number);
    }
    printf("Question a:\n");
    printAll(alist,afreeptr,fashA);
    printf("Lista A\n");
    TraverseLinked(alist,fashA);
    for(i=0;i<4;i++){
        while(TRUE){
            printf("Dwse thn thesh toy ma8hth poy klhrw8hke:");
            scanf("%d",&number1);
            if(number1>=0 && number1<=NumberOfNodes-1) break;
        }
        apreptr=NilValue;
        currptr=alist;
        while(currptr!=number1){
            apreptr=currptr;
            currptr=fashA[currptr].Next;
        }
        Delete(&alist,fashA,&afreeptr,apreptr,ono,&number);
        Insert(&blist,fashB,&bfreeptr,bpreptr,ono,number);
        bpreptr=blist;
        while(fashB[bpreptr].Next!=NilValue) bpreptr=fashB[bpreptr].Next;
    }
    printf("Question b:\n");
    printAll(alist,afreeptr,fashA);
    printf("Lista A\n");
    TraverseLinked(alist,fashA);
    printAll(blist,bfreeptr,fashB);
    printf("Lista B\n");
    TraverseLinked(blist,fashB);
    printf("Question c:\n");
    bpreptr=NilValue;
    currptr=blist;
    while(currptr!=1){
        bpreptr=currptr;
        currptr=fashB[currptr].Next;
    }
    Delete(&blist,fashB,&bfreeptr,bpreptr,ono,&number);
    Insert(&alist,fashA,&afreeptr,apreptr,ono,number);
    printAll(alist,afreeptr,fashA);
    printf("Lista A\n");
    TraverseLinked(alist,fashA);
    printAll(blist,bfreeptr,fashB);
    printf("Lista B\n");
    TraverseLinked(blist,fashB);
    fclose(infile);
    return 0;
}

void InitializeStoragePool(NodeType Node[], ListPointer *FreePtr)

{
   int i;

    for (i=0; i<NumberOfNodes-1;i++)
    {
        Node[i].Next=i+1;
        Node[i].Data.gymnasio=-1;
        Node[i].Data.onoma[0]=' ';
        Node[i].Data.onoma[1]='\0';
    }
    Node[NumberOfNodes-1].Next=NilValue;
    Node[NumberOfNodes-1].Data.gymnasio=-1;
    Node[NumberOfNodes-1].Data.onoma[0]=' ';
    Node[NumberOfNodes-1].Data.onoma[1]='\0';
    *FreePtr=0;
}

void CreateList(ListPointer *List)
{
  *List=NilValue;
}

boolean EmptyList(ListPointer List)
{
  return (List==NilValue);
}

boolean FullList(ListPointer FreePtr)
{
  return (FreePtr == NilValue);
}

void GetNode(ListPointer *P, ListPointer *FreePtr, NodeType Node[])
{
  *P = *FreePtr;
  if (!FullList(*FreePtr))
    *FreePtr =Node[*FreePtr].Next;
}

void ReleaseNode(NodeType Node[], ListPointer P, ListPointer *FreePtr)
{
  Node[P].Next =*FreePtr;
  Node[P].Data.gymnasio = -1;
  Node[P].Data.onoma[0] = ' ';
  Node[P].Data.onoma[1] = '\0';
  *FreePtr =P;
}

void Insert(ListPointer *List, NodeType Node[],ListPointer *FreePtr, ListPointer PredPtr,char Item1[],int Item2)
{
  ListPointer TempPtr;
  GetNode(&TempPtr,FreePtr,Node);
  if (!FullList(TempPtr)) {
    if (PredPtr==NilValue)
    {
        Node[TempPtr].Data.gymnasio =Item2;
        strcpy(Node[TempPtr].Data.onoma,Item1);
        Node[TempPtr].Next =*List;
        *List =TempPtr;
    }
    else
      {
        Node[TempPtr].Data.gymnasio =Item2;
        strcpy(Node[TempPtr].Data.onoma,Item1);
        Node[TempPtr].Next =Node[PredPtr].Next;
        Node[PredPtr].Next =TempPtr;
      }
}
  else
    printf("Full List ...\n");
}

void Delete(ListPointer *List, NodeType Node[], ListPointer *FreePtr, ListPointer PredPtr,char Item1[],int *Item2)
{
  ListPointer TempPtr ;

  if (!EmptyList(*List))
    if (PredPtr == NilValue)
    {
        TempPtr =*List;
        strcpy(Item1,Node[TempPtr].Data.onoma);
        *Item2=Node[TempPtr].Data.gymnasio;
        *List =Node[TempPtr].Next;
        ReleaseNode(Node,TempPtr,FreePtr);
    }
    else
      {
        TempPtr =Node[PredPtr].Next;
        strcpy(Item1,Node[TempPtr].Data.onoma);
        *Item2=Node[TempPtr].Data.gymnasio;
        Node[PredPtr].Next =Node[TempPtr].Next;
        ReleaseNode(Node,TempPtr,FreePtr);
      }
  else
    printf("Empty List ...\n");
}

void TraverseLinked(ListPointer List, NodeType Node[])
{
  ListPointer CurrPtr;

  if (!EmptyList(List))
  {
      CurrPtr =List;
      while (CurrPtr != NilValue)
      {
          printf("(%d:<%s,%d> ->%d) ",CurrPtr,Node[CurrPtr].Data.onoma,Node[CurrPtr].Data.gymnasio, Node[CurrPtr].Next);
          CurrPtr=Node[CurrPtr].Next;
       }
       printf("\n");
   }
  else printf("Empty List ...\n");
}

void printAll(ListPointer List, ListPointer FreePtr, NodeType Node[])
{
    int i;
    printf("1o STOIXEIO LISTAS=%d, 1H FREE POSITION=%d\n", List, FreePtr);
    printf("H STORAGE POOL EXEI TA EJHS STOIXEIA\n");
    for (i=0;i<NumberOfNodes;i++)
        printf("(%d:<%s,%d> ->%d) ",i,Node[i].Data.onoma,Node[i].Data.gymnasio, Node[i].Next);
    printf("\n");
}
