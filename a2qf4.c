#include <stdio.h>
#include <stdlib.h>

typedef int ListElementType;
typedef struct ListNode *ListPointer;
typedef struct ListNode
{
	ListElementType Data;
    ListPointer Next;
} ListNode;

typedef enum {
    FALSE, TRUE
} boolean;


void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr);
void LinkedTraverse(ListPointer List);

void UniqueList(ListPointer InList, ListPointer *OutList);

int main()
{
    int n,i,arth;
    ListPointer inlist,outlist,preptr=NULL;

    CreateList(&inlist);
    CreateList(&outlist);
    printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS: ");
    scanf("%d",&n);
    if (n != 0){
        for(i=0;i<n;i++){
            printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS: ");
            scanf("%d",&arth);
            LinkedInsert(&inlist,arth,preptr);
        }
    UniqueList(inlist,&outlist);
    }
    printf("Arxiki lista\n");
    LinkedTraverse(inlist);
    printf("Teliki lista\n");
    LinkedTraverse(outlist);
    return 0;
}

void CreateList(ListPointer *List)
{
	*List = NULL;
}

boolean EmptyList(ListPointer List)
{
	return (List==NULL);
}

void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr)
{
	ListPointer TempPtr;

   TempPtr= (ListPointer)malloc(sizeof(struct ListNode));
   TempPtr->Data = Item;
	if (PredPtr==NULL) {
        TempPtr->Next = *List;
        *List = TempPtr;
    }
    else {
        TempPtr->Next = PredPtr->Next;
        PredPtr->Next = TempPtr;
    }
}

void LinkedTraverse(ListPointer List)
{
	ListPointer CurrPtr;

   if (EmptyList(List))
   	    printf("EMPTY LIST\n");
   else
   {
   	    CurrPtr = List;
         while ( CurrPtr!=NULL )
        {
             printf("%d ",(*CurrPtr).Data);
             CurrPtr = CurrPtr->Next;
        }
   }
   printf("\n");
}

void UniqueList(ListPointer InList, ListPointer *OutList)
{
    ListPointer Flist, currptr=InList,nextptr=currptr->Next,preptr=NULL, tempPtr;

    CreateList(&Flist);
    tempPtr=Flist;
    int i=0;
    while(currptr!=NULL)
    {
        if(nextptr!=NULL)
           while(currptr->Data==nextptr->Data)
           {
                 currptr=currptr->Next;
                 nextptr=nextptr->Next;
                 if(currptr==NULL || nextptr==NULL)
                    break;
           }
        if(currptr==NULL)
            break;

        LinkedInsert(&Flist,currptr->Data,preptr);
        currptr=currptr->Next;
        if(nextptr!=NULL)
          nextptr=nextptr->Next;
    }
    currptr=Flist;
    CreateList(OutList);
    while(currptr!=NULL)
    {
        LinkedInsert(&(*OutList),currptr->Data,preptr);
        currptr=currptr->Next;
    }
}
