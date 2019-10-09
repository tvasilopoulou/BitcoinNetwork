#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <sys/ioctl.h>
#include "bitcoinList.h"

bitcoinListNode * createBitcoinNode(void){		//initialise bitcoin node
	bitcoinListNode * node=malloc(sizeof(bitcoinListNode));
	if(!node){
		printf("Something related to memory allocation went wrong.\n");
		exit(-1);
	}
	node->bitcoinID=0;
	(node->traninv)=0;
	node->tree=NULL;
	node->next=NULL;
	return node;
}

bitcoinListNode * addBitcoinNode(bitcoinListNode * head, int bc, char * walletID, int bitcoinValue){
	bitcoinListNode * temp=head;
	if (temp==NULL){				//if first node to be added, initialise node
		temp=createBitcoinNode();
		temp->tree=insertTree(temp->tree, walletID, bitcoinValue);
		temp->bitcoinID=bc;
		return temp;
	} 
	while(temp->next!=NULL){		//if not head, move to the end of list
		temp=temp->next;
	}
	temp->next=createBitcoinNode();		//and now create new node
	temp=temp->next;
	temp->bitcoinID=bc;
	return temp;
}

bitcoinListNode * searchBitcoin(walletListNode * head, int bitcoinID){		//search for the bitcoin in every bitcoin list with the given ID
	walletListNode * temp=head;
    while(temp!=NULL){				//while still wallets to look through
    	bitcoinListNode * bit=temp->bcnode;
    	while(bit!=NULL){			//search every bitcoin
    		if (bit->bitcoinID == bitcoinID)return bit;		//until found
    		bit=bit->next;
    	}
    	temp=temp->next;
    }
    return NULL;			//else return NULL
}


void printBitcoinList(bitcoinListNode * head){
	bitcoinListNode * temp=head;
	while(temp!=NULL){
		printf("[%d]", temp->bitcoinID);
		temp=temp->next;
	}
	free(temp);
}


void deleteBitcoinList(bitcoinListNode * head){
	bitcoinListNode * current=malloc(sizeof(bitcoinListNode));
	bitcoinListNode * next=malloc(sizeof(bitcoinListNode));
	current=head;
	while (current != NULL){
		next = current->next;
		if(current->bitcoinID!=0){
			deleteTree(current->tree);
			free(current);
		}
		current = next;
	}
	head=NULL;
}

char * concat(char *s1, char *s2){			//https://stackoverflow.com/questions/8465006/how-do-i-concatenate-two-strings-in-c
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char * result = malloc(len1 + len2 + 1); 		//stick s2 in the end of s1 (like strncat but without causing a segmentation fault)
    if(!result){
		printf("Something related to memory allocation went wrong.\n");
		exit(-1);
    }
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}

char * checkDuplicates(char * str, char *  errorCheck){		//https://stackoverflow.com/questions/15098936/simple-way-to-check-if-a-string-contains-another-string-in-c
	if(strstr(errorCheck, str)!=NULL && atoi(str)!=0){		//if bitcoinID already inside string, return error
		printf("Error in file: A bitcoin can only belong to one user. Please assign bitcoin with ID %d only once before trying again.\n", atoi(str));
		exit(-1);
	}
	errorCheck=concat(errorCheck, str);	//stick new bitcoinID in the end of str
	errorCheck=concat(errorCheck, "|");	//allong with a separator to avoid multiples
	return errorCheck;
}

char * createInput(char * str){		//remove first word from input
	char *tmp = strchr(str, ' ');	//remove until first space
	if(tmp != NULL) str = tmp + 1;
	return str;
}

void traceCoin(walletListNode * walletstat, char * token){
	walletListNode * wall=walletstat;
	int bitcoinID=atoi(token);
	bitcoinListNode * bcnode=malloc(sizeof(bitcoinListNode));
	bcnode=searchBitcoin(wall, bitcoinID);						//search for bitcoin in every list
	if(bcnode==NULL){
		printf("Bitcoin with ID: %d is not registered in our system.\n",bitcoinID );
		free(bcnode);
		return;
	}
	printf("Bitcoin %d was found in our system.\n", bcnode->bitcoinID);		//if not found, let user know
	free(bcnode);
}

void bitCoinStatus(walletListNode * walletstat, char * token, int bitcoinValue){
	bitcoinListNode * tempbc=malloc(sizeof(bitcoinListNode));		//track bitcoin and print its original value and
	tempbc=searchBitcoin(walletstat, atoi(token));					//# of transactions it's been involved in 
	printf("Bitcoin with ID %d:\nInitial value: %d\nIncluded in %d transactions\n",tempbc->bitcoinID, bitcoinValue, tempbc->traninv );
	free(tempbc);
}


