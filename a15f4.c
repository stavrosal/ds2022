#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int arithmoskiv;
    float sinolikovar;
    char imerominia[100];
} StackElementType;

typedef struct StackNode *StackPointer;
typedef struct StackNode
{
	StackElementType Data;
    StackPointer Next;
} StackNode;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateStack(StackPointer *Stack);
boolean EmptyStack(StackPointer Stack);
void Push(StackPointer *Stack, StackElementType Item);
void Pop(StackPointer *Stack, StackElementType *Item);
void TraverseStack(StackPointer Stack);

int find_min(StackPointer *w1,StackPointer *w2,StackPointer *w3);
int find_plith(StackPointer *w);

int main()
{
    StackPointer w1,w2,w3;
    StackElementType w;
    int n,i,min=0;
    char temp;

    CreateStack(&w1);
    CreateStack(&w2);
    CreateStack(&w3);
    printf("Plithos fortiwn: ");
    scanf("%d",&n);
    if(n!=0){
        for(i=0;i<n;i++){
            min=find_min(&w1,&w2,&w3);
            printf("Arithmos kivwtiwn gia to %do fortio: ",i+1);
            scanf("%d",&w.arithmoskiv);
            printf("Synoliko baros gia to %do fortio: ",i+1);
            scanf("%f",&w.sinolikovar);
            printf("Imeromhnia liksis gia to %do fortio: ",i+1);
            scanf("%s",w.imerominia);
            scanf("%c",&temp);
            if(min==1)
                Push(&w1,w);
            else if(min==2)
                Push(&w2,w);
            else
                Push(&w3,w);
        }
    }
    printf("WAREHOUSE 1\n");
    TraverseStack(w1);
    printf("WAREHOUSE 2\n");
    TraverseStack(w2);
    printf("WAREHOUSE 3\n");
    TraverseStack(w3);
    return 0;
}

void CreateStack(StackPointer *Stack)
{
	*Stack = NULL;
}

boolean EmptyStack(StackPointer Stack)
{
	return (Stack==NULL);
}

void Push(StackPointer *Stack, StackElementType Item)
{
	StackPointer TempPtr;

    TempPtr= (StackPointer)malloc(sizeof(struct StackNode));
    TempPtr->Data = Item;
    TempPtr->Next = *Stack;
    *Stack = TempPtr;
}

void Pop(StackPointer *Stack, StackElementType *Item)
{
    StackPointer TempPtr;

    if (EmptyStack(*Stack)) {
   	    printf("EMPTY Stack\n");
    }
   else
   {
        TempPtr = *Stack;
        *Item=TempPtr->Data;
        *Stack = TempPtr->Next;
        free(TempPtr);
    }
}

void TraverseStack(StackPointer Stack)
{
	StackPointer CurrPtr;

   if (EmptyStack(Stack))
   {
   	    printf("EMPTY Stack\n");
    }
   else
   {
   	    CurrPtr = Stack;
         while ( CurrPtr!=NULL )
        {
      	     printf("%d %.2f %s\n",CurrPtr->Data.arithmoskiv,CurrPtr->Data.sinolikovar,CurrPtr->Data.imerominia);
             CurrPtr = CurrPtr->Next;
        }
   }
}

int find_plith(StackPointer *w)
{
    int athr=0;
    StackPointer currptr=*w;

    while(currptr!=NULL){
        athr=athr+(*w)->Data.arithmoskiv;
        currptr=currptr->Next;
    }
    return athr;
}

int find_min(StackPointer *w1,StackPointer *w2,StackPointer *w3)
{
    int s1,s2,s3;

    s1=find_plith(w1);
    s2=find_plith(w2);
    s3=find_plith(w3);
    if(s3<=s1 && s3<=s2)
        return 3;
    else if(s2<=s1)
        return 2;
    else
        return 1;
}
