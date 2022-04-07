#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define StackLimit 85
#define NilValue -1


typedef int ListElementType;

typedef enum {
    FALSE, TRUE
} boolean;

typedef struct ListNode *ListPointer;

typedef struct ListNode
{
 ListElementType Data;
 ListPointer Next;
} ListNode;

void CreateList(ListPointer *List);
boolean EmptyList(ListPointer List);
void LinkedInsert(ListPointer *List, ListElementType Item, ListPointer PredPtr);
void LinkedTraverse(ListPointer List);
void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
void LinkedDelete(ListPointer *List, ListPointer PredPtr);
void OrderedLinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found);
void common_data_finder(ListPointer List1, ListPointer List2, ListPointer *List3);

int main()
{
    ListPointer AList, BList, Common_Data_List, PredPtr1=NULL, PredPtr2=NULL;
    int pl1, pl2, i;
    ListElementType Item;

    CreateList(&AList);
    CreateList(&BList);
    printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS 1: ");
    scanf("%d", &pl1);
    for(i=0;i<pl1;i++)
    {
        printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS 1: ");
        scanf("%d", &Item);
        LinkedInsert(&AList,Item,PredPtr1);
    }

    printf("DWSE TON PLH8OS TWN STOIXEIWN THS LISTAS 2: ");
    scanf("%d", &pl2);
    for(i=0;i<pl2;i++)
    {
        printf("DWSE TON ARI8MO GIA EISAGWGH STH ARXH THS LISTAS 2: ");
        scanf("%d", &Item);
        LinkedInsert(&BList,Item,PredPtr2);
    }
    printf("1h lista\n");
    LinkedTraverse(AList);
    printf("\n2h lista\n");
    LinkedTraverse(BList);
    common_data_finder(AList,BList,&Common_Data_List);
    printf("\nTeliki lista\n");
    LinkedTraverse(Common_Data_List);



    return 0;
}
void common_data_finder(ListPointer List1, ListPointer List2, ListPointer *List3)
{
    ListPointer curPtr1, curPtr2, predPtr=NULL;
    boolean found;

    CreateList(List3);
    curPtr1=List1;

    while(curPtr1!=NULL)
    {
        curPtr2=List2;
        found=FALSE;
        while(curPtr2!=NULL && found!=TRUE)
        {
            if(curPtr1->Data==curPtr2->Data)
            {
                LinearSearch(*List3,curPtr1->Data,&predPtr,&found);
                predPtr=NULL;
                if(found==FALSE)
                    LinkedInsert(&(*List3),curPtr1->Data,predPtr);
            }


            curPtr2=curPtr2->Next;
        }
        curPtr1=curPtr1->Next;
    }
}
void CreateList(ListPointer *List)
{
	*List = NULL;
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

void LinkedDelete(ListPointer *List, ListPointer PredPtr)
{
    ListPointer TempPtr;

    if (EmptyList(*List))
   	    printf("EMPTY LIST\n");
   else
   {
   	    if (PredPtr==NULL)
        {
      	      TempPtr = *List;
              *List = TempPtr->Next;
        }
        else
        {
      	     TempPtr = PredPtr->Next;
             PredPtr->Next = TempPtr->Next;
        }
        free(TempPtr);
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
      	     printf("%d ", CurrPtr->Data);
             CurrPtr = CurrPtr->Next;
        }
   }
}

void LinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found)
{
   ListPointer CurrPtr;
   boolean stop;

   CurrPtr = List;
   *PredPtr = NULL;
   stop= FALSE;
   while (!stop && CurrPtr!=NULL )
    {
         if (CurrPtr->Data==Item )
         	stop = TRUE;
         else
         {
         	*PredPtr = CurrPtr;
            CurrPtr = CurrPtr->Next;
         }
	}
	*Found=stop;
}

void OrderedLinearSearch(ListPointer List, ListElementType Item, ListPointer *PredPtr, boolean *Found)
{
   ListPointer CurrPtr;
   boolean DoneSearching;

   CurrPtr = List;
   *PredPtr = NULL;
   DoneSearching = FALSE;
   *Found = FALSE;
   while (!DoneSearching && CurrPtr!=NULL )
    {
         if (CurrPtr->Data>=Item )
         {
         	DoneSearching = TRUE;
         	*Found = (CurrPtr->Data==Item);
         }
         else
         {
         	*PredPtr = CurrPtr;
            CurrPtr = CurrPtr->Next;
         }
	}
}
boolean EmptyList(ListPointer List)
{
	return (List==NULL);
}
