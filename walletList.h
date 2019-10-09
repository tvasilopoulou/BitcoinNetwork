#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitcoinList.h"


walletListNode * createWalletNode(void);
walletListNode * addWalletNode(char * , int );
/*walletListNode * sortList(walletListNode *, int);
void printTopK(walletListNode *, int, int);*/
void removeChar(char *);
void printWalletList(walletListNode * );
void deleteWalletList(walletListNode *);
void walletStatus(walletListNode * , char * , walletListNode *);
void userInputCall(int ,int ,int , int , int , int , int , int , char *,bucketChain * ,bucketChain *, walletListNode * );




/*transaction * createTransaction(void);
transaction * addTransaction( char * );*/