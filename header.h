#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct transaction
{
	int value;
	char * transactionID;
	char * senderWalletID;
	char * receiverWalletID;
	int day, month, year;
	int hour, minute;
}transaction;


typedef struct bucket
{
	transaction * tran;
	struct bucket * next;	
}bucket;

typedef struct bucketChain
{
	bucket * bucketHead;
	int size;
}bucketChain;

typedef struct treeNode
{
	char * walletID;
	int amount;
	struct treeNode * left;
	struct treeNode * right;
}treeNode;

typedef struct bitcoinListNode{
	int bitcoinID;
	int traninv;
	treeNode * tree;
	struct bitcoinListNode * next;
}bitcoinListNode;

typedef struct walletListNode{
	char * walletID;
	int balance;
	int added;
	int reduced;
	bitcoinListNode * bcnode;
	struct walletListNode * next;
}walletListNode;



//treeNode *=tree
walletListNode * searchWalletList(walletListNode * , char *, walletListNode * );


transaction * createTransaction(void);
transaction * addTransaction( char * );
transaction * requestTransaction(char * , char * , int , int , int , int , int, bucketChain *, bucketChain *, int, int, walletListNode * );
char* itoa(int , char* );
char * createInput(char * );
char * determineSender(char *);


int hash( char *, int );
void createBucketChain( bucketChain * );
bucket * bucketChainInsert(bucketChain * , transaction * );
void insert(bucketChain *, transaction *, int, char *);
void deleteHashTable(bucketChain * );

treeNode * newTreeNode( char *, int );
//treeNode * searchTree(treeNode * , int  );
treeNode * insertTree(treeNode *  , char * , int);
void printPostorder(treeNode * , int ); 
void deleteTree(treeNode * );




