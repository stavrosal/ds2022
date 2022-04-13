// a11f4.c
                        /*ΥΛΟΠΟΙΗΣΗ ΟΥΡΑΣ ΔΥΝΑΜΙΚΑ ΜΕ ΔΕΙΚΤΕΣ*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char QueueElementType;           /*ο τύπος των στοιχείων της συνδεδεμένης ουράς
                                         τύπου char*/
typedef struct QueueNode *QueuePointer;

typedef struct QueueNode
{
    QueuePointer Next;
    QueueElementType Data[8];
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
        return 0;
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
                printf("You have logged in to the system from another terminal. New access is forbidden.\n");
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
    char onoma[8], termch;

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
/* Λειτουργία: Δημιουργεί μια κενή συνδεδεμένη ουρά.
   Επιστρέφει: Μια κενή συνδεδεμένη ουρά
*/
{
	(*Queue).Front = NULL;
	Queue->Rear = NULL;
}

boolean EmptyQ(QueueType Queue)
/* Δέχεται:    Μια συνδεδεμένη ουρά.
   Λειτουργία: Ελέγχει αν η συνδεδεμένη ουρά είναι κενή.
   Επιστρέφει: True αν η ουρά είναι κενή, false  διαφορετικά
*/
{
	return (Queue.Front==NULL);
}

void AddQ(QueueType *Queue, QueueElementType Item[])
/* Δέχεται:    Μια συνδεδεμένη ουρά Queue και ένα  στοιχείο Item.
   Λειτουργία: Προσθέτει το στοιχείο Item στο τέλος της συνδεδεμένης ουράς Queue.
   Επιστρέφει: Την τροποποιημένη ουρά
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
/* Δέχεται:    Μια συνδεδεμένη ουρά.
   Λειτουργία: Αφαιρεί το στοιχείο Item από την  κορυφή της συνδεδεμένης ουράς,
                αν δεν είναι  κενή.
   Επιστρέφει: Το στοιχείο Item και την τροποποιημένη συνδεδεμένη ουρά.
   Έξοδος:     Μήνυμα κενής ουράς, αν η ουρά είναι  κενή
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
