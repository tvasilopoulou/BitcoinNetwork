#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

bitcoinListNode * createBitcoinNode(void);
bitcoinListNode * addBitcoinNode(bitcoinListNode * , int, char *, int);
/*bitcoinListNode * sortList(bitcoinListNode *, int);
void printTopK(bitcoinListNode *, int, int);*/
void printBitcoinList(bitcoinListNode *);
int decrementBitcoin(walletListNode * , int );
bitcoinListNode * searchBitcoin(walletListNode * , int );
void deleteBitcoinList(bitcoinListNode *);
char * concat(char * , char * );
char * checkDuplicates(char * , char * );
void traceCoin(walletListNode * , char * );
void bitCoinStatus(walletListNode * , char *, int );

