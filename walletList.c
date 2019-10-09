#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "walletList.h"


walletListNode * createWalletNode(void){					//initialise node with 0's
	walletListNode * node=malloc(sizeof(walletListNode));
	if(!node){
		printf("Something related to memory allocation went wrong.\n");
		exit(-1);
	}
	node->walletID= "\0";
	node->balance= 0;
	node->added= 0;
	node->reduced= 0;
	node->bcnode=NULL;
	node->next=NULL;
	return node;
}

walletListNode * addWalletNode( char * walletID, int balance){
	walletListNode * temp=createWalletNode();
	temp->walletID=malloc(sizeof(char)*(strlen(walletID)+1));
	strncpy(temp->walletID, walletID, strlen(walletID)+1);
	temp->balance= balance;
	return temp;
}


walletListNode * searchWalletList(walletListNode * head, char * walletID, walletListNode * temp){
	temp=head;										//parse list until walletlistnode with walletID as walletID
	while(temp!=NULL){
		if(!strcmp(temp->walletID,walletID)){
			return temp;
		} 
		temp=temp->next;
	}
	return NULL;

}


void printWalletList(walletListNode * head){
	walletListNode * temp=head;	
	while(temp!=NULL){
		printf("Line was: [%s_", temp->walletID);
		printBitcoinList(temp->bcnode);

		printf("]\n\n");
		temp=temp->next;
	}
}

int decrementBitcoin(walletListNode * temp, int amount){
	int counter=0;
    while(temp->bcnode!=NULL){
    	if((temp->bcnode->tree->amount) >= amount){		//if remnant of temp->bcnode suffices, simply reduce amount in bitcoin
	    	temp->bcnode->tree->amount -= amount;
	    	return counter;
	    }
	    else if((temp->bcnode->tree->amount) < amount){	//if it doesn't, make amount of this bitcoin=0 and move on to next for remaining amount
	    	amount -= (temp->bcnode->tree->amount);
	    	temp->bcnode->tree->amount=0;
	    	temp->bcnode=temp->bcnode->next;
	    	counter++;
	    }   
    }
	printf("Not enough balance of user %s for amount %d. Transaction failed(%d).\n", temp->walletID, amount,temp->bcnode->tree->amount );
	return 0;
}



void deleteWalletList(walletListNode * head){				//delete whole list and everything it contains
	walletListNode * current=malloc(sizeof(walletListNode));
	walletListNode * next=malloc(sizeof(walletListNode));
	current=head;
	while (current != NULL){
		next = current->next;
		deleteBitcoinList(current->bcnode);
		free(current);
		current = next;
	}
	head=NULL;
}


void walletStatus(walletListNode * walletstat, char * inp, walletListNode * tempwall){
	char * tempinp=malloc(sizeof(char)*(strlen(inp)+1));
	strncpy(tempinp, inp, strlen(inp)+1);
	tempinp=createInput(tempinp);					//find walletListNode * with walletID and print balance
	tempwall=searchWalletList(walletstat, tempinp, tempwall);
	printf("Current balance of user %s is: %d\n", tempwall->walletID, tempwall->balance);
}

void userInputCall(int bitcoinValue,int senderEntries,int receiverEntries, int day, int month, int year, int hour, int minute, char * tID, bucketChain * shashTable, bucketChain * rhashTable, walletListNode * walletstat){
	printf("Please enter command: \n");
	char * input=malloc(sizeof(char)*300);		//input limit 300 chars		
	char delimiter[]=" \n";
	char * token;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int i=0;
	int flag=0;
	scanf ("%[^\n]%*c", input);
	char * inp=malloc(sizeof(char)*(strlen(input)+1));
	strncpy(inp, input, strlen(input)+1);
	if(input!=NULL){
		token=strtok(input, delimiter);
		if (token!=NULL){					//choose function
			if(!strcmp(token, "/requestTransaction")) flag=1;
			else if(!strcmp(token, "/requestTransactions")) flag=2;
			else if(!strcmp(token, "/findEarnings")) flag=3;
			else if(!strcmp(token, "/findPayments")) flag=4;
			else if(!strcmp(token, "/walletStatus")) flag=5;
			else if(!strcmp(token, "/bitCoinStatus")) flag=6;
			else if(!strcmp(token, "/tracecoin")) flag=7;			
			else if(!strcmp(token, "/exit")) flag=8;
		}
	}
	walletListNode * tempwall=malloc(sizeof(walletListNode));			
	if(!tempwall){
		printf("Something related to memory allocation went wrong.\n");
		exit(-1);
    }
	if(flag==0){
		printf("Wrong input. Please try again.\n");
		exit(-1);
	}
	else if (flag==1)
	{
		token=strtok(NULL, delimiter);
		tempwall=searchWalletList(walletstat, token, tempwall);
		if(tempwall==NULL){
			printf("Error in file: user either does not have enough balance available for transaction or does not exist.\n");
			exit(-1);
		}
		char * tempinp=malloc(sizeof(char)*(strlen(inp)+1));
		strncpy(tempinp, inp, strlen(inp)+1);					//whole input for the time being
		tempinp=createInput(tempinp);							//cut first token
		tempinp=createInput(tempinp);							//cut senderID
		transaction * tran=requestTransaction(tempinp, tID, day, month, year, hour, minute, shashTable, rhashTable, senderEntries, receiverEntries, tempwall );			
		if (tran==NULL) printf("Request for transaction: not granted.\n");
		
		return;
	}
	else if (flag==2){		//not tested
		char * token1=strtok(NULL, delimiter);
		if(strtok(NULL, delimiter)==NULL){
			FILE * file= fopen(token1, "r");
			while ((read = getline(&line, &len, file)) != -1){		//same way as impied by second part
				char * tempinp=malloc(sizeof(char)*(strlen(inp)+1));
				strncpy(tempinp, inp, strlen(inp)+1);
				char * tok;
				while((tok=strtok_r(tempinp, ";", &tempinp))!=NULL){		//for every line limited by ;
					char * tr=malloc(sizeof(char)*(strlen(tok)+1));
					strncpy(tr, tok, strlen(tok)+1);
				    tr=strtok_r(tok, " ", &tok);
					tempwall=searchWalletList(walletstat, tr, tempwall);
					if(tempwall==NULL){
						printf("Error in file: user either does not have enough balance available for transaction or does not exist.\n");
						exit(-1);
					}
					transaction * tran=NULL;
					tran=requestTransaction(tok, tID, day, month, year, hour, minute, shashTable, rhashTable, senderEntries, receiverEntries, tempwall );			
					if (tran==NULL) printf("Request for transaction: not granted.\n");	
				}

			}
			fclose(file);
			
			return;
		}
		inp=createInput(inp);		//throw out function name
		char * tempinp=malloc(sizeof(char)*(strlen(inp)+1));
		strncpy(tempinp, inp, strlen(inp)+1);
		char * tok;
		while((tok=strtok_r(tempinp, ";", &tempinp))!=NULL){		//for every line limited by ;
			char * tr=malloc(sizeof(char)*(strlen(tok)+1));
			strncpy(tr, tok, strlen(tok)+1);
		    tr=strtok_r(tok, " ", &tok);						//and for every token separated by spaces
			tempwall=searchWalletList(walletstat, tr, tempwall);	//find node
			if(tempwall==NULL){
				printf("Error in file: user either does not have enough balance available for transaction or does not exist.\n");
				exit(-1);
			}
			transaction * tran=NULL;
			tran=requestTransaction(tok, tID, day, month, year, hour, minute, shashTable, rhashTable, senderEntries, receiverEntries, tempwall );			
			if (tran==NULL) printf("Request for transaction: not granted.\n");	
		}

		return;
	}
	else if (flag==3)
	{
		token=strtok(NULL, delimiter);		//print earnings
		tempwall=searchWalletList(walletstat, token, tempwall);
		printf("Earnings of user %s: $ %d\n",tempwall->walletID, tempwall->added );			
		return;			
	}
	else if (flag==4)
	{
		token=strtok(NULL, delimiter);
		tempwall=searchWalletList(walletstat, token, tempwall);		//print payments
		printf("Spendings of user %s: $%d\n",tempwall->walletID, tempwall->reduced );			
		return;
	}
	else if (flag==5)
	{
		walletStatus(walletstat, inp, tempwall);
		return;
	}
	else if (flag==6)
	{
		token=strtok(NULL, delimiter);
		bitCoinStatus(walletstat, token, bitcoinValue);
		return;
	}
	else if (flag==7)
	{
		token=strtok(NULL, delimiter);
		traceCoin(walletstat, token);
		return;
	}
	else if (flag==8)
	{
		free(tempwall);						//free pointers, delete hash tables, delete lists, delete trees
		free(input);
		deleteWalletList(walletstat);
		deleteHashTable(shashTable);
		deleteHashTable(rhashTable);
		if (line) free(line);
		printf("Bye bye. We hope to see you again soon!\n");
		exit(0);
	}
}