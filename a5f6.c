//filename : a5f6.c

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define HMax 9              /*     ôï ìÝãåèïò ôïõ ðßíáêá HashTable */

#define VMax 8             /*ôï ìÝãåèïò ôçò ëßóôáò, */

#define EndOfList -1        /* óçìáßá ðïõ óçìáôïäïôåß ôï ôÝëïò ôçò ëßóôáò
                                êáé ôçò êÜèå õðïëßóôáò óõíùíýìùí */

typedef struct{
    char name[9];
    char password[6];
} ListElementType;  /*ôýðïò äåäïìÝíùí ãéá ôá óôïé÷åßá ôçò ëßóôáò */

typedef int KeyType;

typedef struct {
	KeyType key;
	ListElementType Data;
	int Link;
} ListElm;

typedef struct  {
	int HashTable[HMax];   // ðßíáêáò äåéêôþí ðñïò ôéò õðïëßóôåò óõíùíýìùí
    int Size;                // ðëÞèïò åããñáöþí ôçò ëßóôáò List
	int SubListPtr;          // Däåßêôçò óå ìéá õðïëßóôá óõíùíýìùí
    int StackPtr;           // äåßêôçò ðñïò ôçí ðñþôç åëåýèåñç èÝóç ôçò ëßóôáò List
	ListElm List[VMax];
} HashListType;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateHashList(HashListType *HList);
int HashKey(KeyType key);
boolean FullHashList(HashListType HList);
void SearchSynonymList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred);
void SearchHashList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred);
void AddRec(HashListType *HList,ListElm InRec);
void DeleteRec(HashListType *HList,KeyType DelKey);

void Print_HashList(HashListType HList);
void PrintPinakes(HashListType HList, int count);

int foldKey(char name[HMax]);


int main(){
    FILE *infile;
    int Loc, Pred;
    char termch;
    HashListType HList;
    ListElm rec;

    infile = fopen("I5f6.txt", "r");
    if (infile == NULL){
        printf("Error while opening file.\n");
        return(1);
    }

    CreateHashList(&HList);

    char str[HMax], str2[HMax];
    int count=0, key;
    while (fgets(str, VMax, infile) != NULL){
        fgets(str2, VMax, infile);

        if (strlen(str) > 0 && str[strlen(str)-1] == '\n'){

            str[(strlen(str)-1)] = '\0';

            }
        if (strlen(str2) > 0 && str2[strlen(str2)-1] == '\n'){

            str2[(strlen(str2)-1)] = '\0';

            }

        key = foldKey(str);

        count++;

        rec.key = key;
        rec.Link = -1;
        strcpy(rec.Data.name, str);
        strcpy(rec.Data.password, str2);

        AddRec(&HList, rec);
    }
    PrintPinakes(HList, count);
    char tname[9], tpass[7], selection;

    do{
        printf("USERNAME: ");
        scanf("%8s", tname);
        printf("PASSWORD: ");
        scanf("%7s", tpass);

        SearchHashList(HList, foldKey(tname), &Loc, &Pred);
        if (strcmp(HList.List[Loc].Data.name, tname) != 0 || Loc == -1)
            printf("Access is forbidden: Wrong user ID\n");
        else if (strcmp(HList.List[Loc].Data.password, tpass) != 0){
            printf("Access is forbidden: Wrong password\n");
        }
        else{
            printf("You have logged in to the system\n");
        }


        do{
            printf("Continue Y/N? ");
            scanf(" %s", &selection);
        }while(toupper(selection) != 'Y' && toupper(selection) != 'N');
    }while (toupper(selection) == 'Y');

    return 0;

}

int foldKey(char name[HMax]){
    int x;
    x = (name[0] + name[(strlen(name)-1)]) / 2;
    return x;
}

int HashKey(KeyType key)
/* ÄÝ÷åôáé:    Ôçí ôéìÞ key åíüò êëåéäéïý.
   Ëåéôïõñãßá: Âñßóêåé ôçí ôéìÞ êáôáêåñìáôéóìïý HValue ãéá ôï êëåéäß Key.
   ÅðéóôñÝöåé: Ôçí ôéìÞ êáôáêåñìáôéóìïý HValue
*/
{
	/*óå ðåñßðôùóç ðïõ ôï KeyType äåí åßíáé áêÝñáéïò
	èá ðñÝðåé íá ìåôáôñÝðåôáé êáôÜëëçëá ôï êëåéäß óå áñéèìü*/
	return key%HMax;
}

void CreateHashList(HashListType *HList)
/* Ëåéôïõñãßá: Äçìéïõñãåß ìéá äïìÞ HList.
   ÅðéóôñÝöåé: Ôçí äïìÞ HList
*/
{
	int index;

	HList->Size=0;           //ÄÇÌÉÏÕÑÃÅÉ ÌÉÁ ÊÅÍÇ ËÉÓÔÁ
	HList->StackPtr=0;       //ÄÅÉÊÔÇò ÓÔÇ ÊÏÑÕÖÇ ÔÇÓ ÓÔÏÉÂÁÓ ÔÙÍ ÅËÅÕÈÅÑÙÍ ÈÅÓÅÙÍ

    /*ÁÑ×ÉÊÏÐÏÉÅÉ ÔÏÍ ÐÉÍÁÊÁ HashTable ÔÇÓ ÄÏÌÇÓ HList ÙÓÔÅ ÊÁÈÅ ÓÔÏÉ×ÅÉÏÕ ÔÏÕ
        ÍÁ Å×ÅÉ ÔÇ ÔÉÌÇ EndOfList (-1)*/
    index=0;
	while (index<HMax)
	{
		HList->HashTable[index]=EndOfList;
		index=index+1;
    }

     //Äçìéïõñãßá ôçò óôïßâáò ôùí åëåýèåñùí èÝóåùí óôç ëßóôá HList
    index=0;
	while(index < VMax-1)
	{
		HList->List[index].Link=index+1;
		index=index+1;
	}
	HList->List[index].Link=EndOfList;
}

boolean FullHashList(HashListType HList)
/* ÄÝ÷åôáé:    Ìéá äïìÞ HList.
   Ëåéôïõñãßá: ÅëÝã÷åé áí ç ëßóôá List ôçò äïìÞò HList åßíáé ãåìÜôç.
   ÅðéóôñÝöåé: TRUE áí ç ëßóôá List åßíáé ãåìÜôç, FALSE äéáöïñåôéêÜ.
*/
{
	return(HList.Size==VMax);
}

void SearchSynonymList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred)
/* ÄÝ÷åôáé:     Ìéá äïìÞ HList êáé ìéá ôéìÞ êëåéäéïý KeyArg.
    Ëåéôïõñãßá: ÁíáæçôÜ ìéá åããñáöÞ ìå êëåéäß KeyArg óôçí õðïëßóôá óõíùíýìùí.
    ÅðéóôñÝöåé: Ôç èÝóç Loc ôçò åããñáöÞò êáé ôç èÝóç Pred ôçò ðñïçãïýìåíçò
                åããñáöÞò óôçí õðïëßóôá
*/
{
	int Next;
	Next=HList.SubListPtr;
	*Loc=-1;
	*Pred=-1;
	while(Next!=EndOfList)
	{
		if (HList.List[Next].key==KeyArg)
		{
			*Loc=Next;
			Next=EndOfList;
		}
		else
		{
			*Pred=Next;
			Next=HList.List[Next].Link;
		}
	}
}
void SearchHashList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred)
/* ÄÝ÷åôáé:     Ìéá äïìÞ HList êáé ìéá ôéìÞ êëåéäéïý KeyArg.
    Ëåéôïõñãßá: ÁíáæçôÜ ìéá åããñáöÞ ìå êëåéäß KeyArg óôç äïìÞ HList.
    ÅðéóôñÝöåé: Ôç èÝóç Loc ôçò åããñáöÞò êáé ôç èÝóç Pred ôçò
                ðñïçãïýìåíçò åããñáöÞò ôçò õðïëßóôáò óôçí ïðïßá áíÞêåé.
                Áí äåí õðÜñ÷åé åããñáöÞ ìå êëåéäß KeyArg ôüôå Loc=Pred=-1
*/
{
	int HVal;
	HVal=HashKey(KeyArg);
    if (HList.HashTable[HVal]==EndOfList)
	{
		*Pred=-1;
		*Loc=-1;
	}
	else
	{
		HList.SubListPtr=HList.HashTable[HVal];
		SearchSynonymList(HList,KeyArg,Loc,Pred);
	}
}

void AddRec(HashListType *HList,ListElm InRec)
/* ÄÝ÷åôáé:    Ìéá äïìÞ HList êáé ìéá åããñáöÞ InRec.
   Ëåéôïõñãßá: ÅéóÜãåé ôçí åããñáöÞ InRec óôç ëßóôá List, áí äåí åßíáé ãåìÜôç,
                êáé åíçìåñþíåé ôç äïìÞ HList.
   ÅðéóôñÝöåé: Ôçí ôñïðïðïéçìÝíç äïìÞ HList.
   ¸îïäïò:     ÌÞíõìá ãåìÜôçò ëßóôáò, áí ç List åßíáé ãåìÜôç, äéáöïñåôéêÜ,
                áí õðÜñ÷åé Þäç åããñáöÞ ìå ôï ßäéï êëåéäß,
                åìöÜíéóç áíôßóôïé÷ïõ ìçíýìáôïò
*/
{
	int Loc, Pred, New, HVal;

   // New=0;
	if(!(FullHashList(*HList)))
	{
		Loc=-1;
		Pred=-1;
		SearchHashList(*HList,InRec.key,&Loc,&Pred);
		if(Loc==-1)
		{
			HList->Size=HList->Size +1;
			New=HList->StackPtr;
			HList->StackPtr=HList->List[New].Link;
			HList->List[New]=InRec;
			if (Pred==-1)
			{
			    HVal=HashKey(InRec.key);
                HList->HashTable[HVal]=New;
				HList->List[New].Link=EndOfList;
			}
			else
			{
                HList->List[New].Link=HList->List[Pred].Link;
				HList->List[Pred].Link=New;
			}
		}

		else
		{
			printf("YPARXEI HDH EGGRAFH ME TO IDIO KLEIDI \n");
		}
	}
	else
	{
		printf("Full list...");
	}
}
void DeleteRec(HashListType *HList,KeyType DelKey)
/* DEXETAI:    TH DOMH (HList) KAI To KLEIDI (DelKey) THS EGGRAFHS
               POY PROKEITAI NA DIAGRAFEI
   LEITOYRGIA: DIAGRAFEI, THN EGGRAFH ME KLEIDI (DelKey) APO TH
               LISTA (List), AN YPARXEI ENHMERWNEI THN DOMH HList
   EPISTREFEI: THN TROPOPOIHMENH DOMH (HList)
   EJODOS:     "DEN YPARXEI EGGRAFH ME KLEIDI" MHNYMA
*/
{
	int Loc, Pred, HVal;

	SearchHashList(*HList,DelKey,&Loc,&Pred);
	if(Loc!=-1)
	{
		if(Pred!=-1)
		{
			HList->List[Pred].Link=HList->List[Loc].Link;
		}
		else
		{
			HVal=HashKey(DelKey);
		    HList->HashTable[HVal]=HList->List[Loc].Link;
		}
		HList->List[Loc].Link=HList->StackPtr;
		HList->StackPtr=Loc;
		HList->Size=HList->Size -1;
	}
	else
	{
		printf("DEN YPARXEI  EGGRAFH ME KLEIDI %d \n",DelKey);
	}
}

void Print_HashList(HashListType HList)
{
   int i, SubIndex;

     printf("HASHLIST STRUCTURE with SYNONYM CHAINING\n");
     printf("========================================\n");

          printf("PINAKAS DEIKTWN STIS YPO-LISTES SYNWNYMWN EGGRAFWN:\n");
            for (i=0; i<HMax;i++)
              printf("%d| %d\n",i,HList.HashTable[i]);

          printf("OI YPO-LISTES TWN SYNWNYMWN EGGRAFWN:\n");
          for (i=0; i<HMax;i++)
          {
              SubIndex = HList.HashTable[i];
              while ( SubIndex != EndOfList )
              {
                   printf("[%d, %d, %d]",HList.List[SubIndex].key,HList.List[SubIndex].Data,HList.List[SubIndex].Link);
                   printf(" -> ");
                   SubIndex = HList.List[SubIndex].Link;
               } //* while *)
              printf("TELOS % dHS YPO-LISTAS\n", i);
          }

          printf("H STOIBA TWN ELEY8ERWN 8ESEWN THS LISTAS:\n");
          SubIndex = HList.StackPtr;
          while ( SubIndex != EndOfList )
          {
                printf("%d <= ",SubIndex);
                SubIndex = HList.List[SubIndex].Link;
          }
          printf("TELOS\n");

          printf("MEGE8OS THS LISTAS = %d\n", HList.Size);
          printf("========================================\n");
}


void PrintPinakes(HashListType HList, int count)
{
    int i;
	printf("Hash table\n");
	for (i=0; i<HMax;i++)
              printf("%d)%3d\n",i,HList.HashTable[i]);

	printf("\nHash List\n");
    for (i=0;i<count;i++)
	   printf("%d) %d, %9s, %9s, %4d\n", i, HList.List[i].key, HList.List[i].Data.name, HList.List[i].Data.password, HList.List[i].Link);
	printf("\n");
}

