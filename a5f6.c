#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define HMax 9

#define VMax 30

#define EndOfList -1

typedef struct{
    char user_id[8];
    char password[6];
}ListElementType;

typedef int KeyType;

typedef struct {
	KeyType key;
	ListElementType Data;
	int Link;
} ListElm;

typedef struct  {
	int HashTable[HMax];
    int Size;
	int SubListPtr;
    int StackPtr;
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
void PrintPinakes(HashListType HList);
int foldkey(char key[]);

int main()
{
    FILE *infile;
    HashListType board;
    ListElm bd;
    int nscan,lock=-1,pred=-1;
    char temch,id[8],pas[6];

    CreateHashList(&board);
    infile=fopen("I5f6.txt","r");
    if(infile==NULL) exit(1);
    while(TRUE){
        nscan=fscanf(infile,"%s%c%s%c",bd.Data.user_id,&temch,bd.Data.password,&temch);
        if(nscan==EOF) break;
        bd.key=foldkey(bd.Data.user_id);
        AddRec(&board,bd);
    }
    PrintPinakes(board);
    do{printf("USERNAME: ");
    scanf("%s",id);
    temch=getchar();
    nscan=foldkey(id);
    printf("PASSWORD: ");
    scanf("%s",pas);
    temch=getchar();
    SearchHashList(board,nscan,&lock,&pred);
    if(lock!=-1){
        if(strcmp(board.List[nscan].Data.password,pas)==0) printf("You have logged in to the system\n");
        else printf("Access is forbidden: Wrong password\n");
    }
    else printf("Access is forbidden: Wrong user ID\n");
    printf("Continue Y/N? ");
    temch=getchar();
    }while(temch=='y');
    fclose(infile);
    return 0;
}

int HashKey(KeyType key)
{
	return key%HMax;
}

void CreateHashList(HashListType *HList)
{
	int index;

	HList->Size=0;
	HList->StackPtr=0;

    index=0;
	while (index<HMax)
	{
		HList->HashTable[index]=EndOfList;
		index=index+1;
    }
    index=0;
	while(index < VMax-1)
	{
		HList->List[index].Link=index+1;
		index=index+1;
	}
	HList->List[index].Link=EndOfList;
}

boolean FullHashList(HashListType HList)
{
	return(HList.Size==VMax);
}

void SearchSynonymList(HashListType HList,KeyType KeyArg,int *Loc,int *Pred)
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
{
	int Loc, Pred, New, HVal;

	if(!(FullHashList(*HList)))
	{
		Loc=-1;
		Pred=-1;
		InRec.key=foldkey(InRec.Data.user_id);
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

void PrintPinakes(HashListType HList)
{
    int i;
	printf("Hash table\n");
	for (i=0;i<HMax;i++)
              printf("%d)%3d\n",i,HList.HashTable[i]);
    printf("\n");
	printf("Hash List\n");
    for (i=0;i<4;i++)
	   printf("%d)%d,    %s, %s, %d\n",i,HList.List[i].key,HList.List[i].Data.user_id,HList.List[i].Data.password,HList.List[i].Link);
	printf("\n");
}

int foldkey(char key[])
{
    int i;
    char c1=key[0],c2;

    for(i=0;key[i]!='\0';i++);
    c2=key[i-1];
    i=(c1+c2)/2;
    return i;
}
