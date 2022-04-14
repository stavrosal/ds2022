// a11f4.c
                        /*ÕËÏÐÏÉÇÓÇ ÏÕÑÁÓ ÄÕÍÁÌÉÊÁ ÌÅ ÄÅÉÊÔÅÓ*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char QueueElementType;           /*ï ôýðïò ôùí óôïé÷åßùí ôçò óõíäåäåìÝíçò ïõñÜò
                                         ôýðïõ char*/
typedef struct QueueNode *QueuePointer;

typedef struct QueueNode
{
    QueuePointer Next;
    QueueElementType Data[9];
} QueueNode;

typedef struct
{
    QueuePointer Front;
    QueuePointer Rear;
} QueueType;

typedef enum {
    FALSE, TRUE
} boolean;


void CreateQ(QueueType *Queue);
boolean EmptyQ(QueueType Queue);
void AddQ(QueueType *Queue, QueueElementType Item[]);
void RemoveQ(QueueType *Queue, QueueElementType *Item);
void TraverseQ(QueueType Queue);

boolean isinFile(FILE *file, QueueElementType input[]);
boolean isinQ(QueueType Queue, QueueElementType item[]);

int main(){
    QueueType users, admins, diax;
    FILE *infile;
    char  selection;

    infile = fopen("I11F4.dat", "r");
    if (infile == NULL){
        printf("Error while opening I11F4.dat\n");
        exit(1);
    }

    CreateQ(&admins);
    CreateQ(&users);


    QueueElementType input[8];
    do{
        printf("USERNAME: ");
        scanf("%s", input);

        if (!isinFile(infile, input)){
            printf("Wrong user ID\n");
        }
        else{
            if (isinQ(users, input) || isinQ(admins, input)){
                printf("You have logged in to the system from another terminal. New access is forbidden.");
            }
            else{
                if (input[0] == 'U' && input[1] == 'S' && input[2] == 'R'){
                    AddQ(&users, input);
                }
                else{
                    AddQ(&admins, input);
                }
            }
        }


        do{
            printf("New insertion Y/N (Y=yes, N=No)");
            scanf(" %s", &selection);
        }while(selection != 'Y' && selection != 'N');
    }while (selection == 'Y');


    printf("Oura Diaxeiristwn\n");
    TraverseQ(admins);
    printf("Oura Aplwn Xrhstwn\n");
    TraverseQ(users);


    return 0;
}

boolean isinFile(FILE *file, QueueElementType input[]){
    int nscan;
    boolean found;
    char onoma[9], termch;

    file = fopen("I11F4.dat", "r");

    found = FALSE;

    while (TRUE){
        nscan = fscanf(file, "%8[^\n]%c", onoma, &termch);
        //printf("%s\n", onoma);
        if (nscan == EOF) break;
        if (strcmp(onoma, input) == 0) {
                found = TRUE;
                break;
        }
    }
    return found;
}


void CreateQ(QueueType *Queue)
/* Ëåéôïõñãßá: Äçìéïõñãåß ìéá êåíÞ óõíäåäåìÝíç ïõñÜ.
   ÅðéóôñÝöåé: Ìéá êåíÞ óõíäåäåìÝíç ïõñÜ
*/
{
	(*Queue).Front = NULL;
	Queue->Rear = NULL;
}

boolean EmptyQ(QueueType Queue)
/* ÄÝ÷åôáé:    Ìéá óõíäåäåìÝíç ïõñÜ.
   Ëåéôïõñãßá: ÅëÝã÷åé áí ç óõíäåäåìÝíç ïõñÜ åßíáé êåíÞ.
   ÅðéóôñÝöåé: True áí ç ïõñÜ åßíáé êåíÞ, false  äéáöïñåôéêÜ
*/
{
	return (Queue.Front==NULL);
}

void AddQ(QueueType *Queue, QueueElementType Item[])
/* ÄÝ÷åôáé:    Ìéá óõíäåäåìÝíç ïõñÜ Queue êáé Ýíá  óôïé÷åßï Item.
   Ëåéôïõñãßá: ÐñïóèÝôåé ôï óôïé÷åßï Item óôï ôÝëïò ôçò óõíäåäåìÝíçò ïõñÜò Queue.
   ÅðéóôñÝöåé: Ôçí ôñïðïðïéçìÝíç ïõñÜ
*/
{
	QueuePointer TempPtr;

    TempPtr= (QueuePointer)malloc(sizeof(struct QueueNode));
    strcpy(TempPtr->Data, Item);
    TempPtr->Next = NULL;
    if (Queue->Front==NULL)
        Queue->Front=TempPtr;
    else
        Queue->Rear->Next = TempPtr;
    Queue->Rear=TempPtr;
}

void RemoveQ(QueueType *Queue, QueueElementType *Item)
/* ÄÝ÷åôáé:    Ìéá óõíäåäåìÝíç ïõñÜ.
   Ëåéôïõñãßá: Áöáéñåß ôï óôïé÷åßï Item áðü ôçí  êïñõöÞ ôçò óõíäåäåìÝíçò ïõñÜò,
                áí äåí åßíáé  êåíÞ.
   ÅðéóôñÝöåé: Ôï óôïé÷åßï Item êáé ôçí ôñïðïðïéçìÝíç óõíäåäåìÝíç ïõñÜ.
   ¸îïäïò:     ÌÞíõìá êåíÞò ïõñÜò, áí ç ïõñÜ åßíáé  êåíÞ
*/
{
    QueuePointer TempPtr;

    if (EmptyQ(*Queue)) {
   	    printf("EMPTY Queue\n");
    }
   else
   {
        TempPtr = Queue->Front;
        strcpy(Item, TempPtr->Data);
        //*Item=TempPtr->Data;
        Queue->Front = Queue->Front->Next;
        free(TempPtr);
        if (Queue->Front==NULL) Queue->Rear=NULL;
    }
}

void TraverseQ(QueueType Queue)
{
	QueuePointer CurrPtr;

   if (EmptyQ(Queue))
    {
   	    printf("EMPTY Queue\n");
    }
   else
   {
   	    CurrPtr = Queue.Front;
         while ( CurrPtr!=NULL )
        {
      	     printf("%s", CurrPtr->Data);
      	     printf("\n");
             CurrPtr = CurrPtr->Next;
        }
   }
    //printf("\n");
}


boolean isinQ(QueueType Queue, QueueElementType item[]){
    QueuePointer CurrPtr;

    boolean found;
    found = FALSE;

    if (!EmptyQ(Queue)){
        CurrPtr = Queue.Front;
        while (CurrPtr != NULL){
            if (strcmp(item, CurrPtr->Data) == 0){
                found = TRUE;
                break;
            }
            CurrPtr= CurrPtr->Next;
        }
    }
    return found;

}
