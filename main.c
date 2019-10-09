#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "walletList.h"


/*   ./bitcoin -a bitCoinBalancesFile.txt -t transactionsFile.txt -v 25 -h1 2 -h2 3 -b 3		*/

int main(int argc, char const *argv[]){
	if (argc!=13)
	{
		printf("Please try entering the Bitcoin Network again. Number of arguments was invalid.\n");
		exit(-1);
	}
    //check arguements in pairs
	if ((strcmp(argv[1],"-a") && strcmp(argv[3],"-a") && strcmp(argv[5],"-a") && strcmp(argv[7],"-a") && strcmp(argv[9],"-a") && strcmp(argv[11],"-a"))
	 || (strcmp(argv[1],"-t") && strcmp(argv[3],"-t") && strcmp(argv[5],"-t") && strcmp(argv[7],"-t") && strcmp(argv[9],"-t") && strcmp(argv[11],"-t"))
	 || (strcmp(argv[1],"-v") && strcmp(argv[3],"-v") && strcmp(argv[5],"-v") && strcmp(argv[7],"-v") && strcmp(argv[9],"-v") && strcmp(argv[11],"-v"))
	 || (strcmp(argv[1],"-h1") && strcmp(argv[3],"-h1") && strcmp(argv[5],"-h1") && strcmp(argv[7],"-h1") && strcmp(argv[9],"-h1") && strcmp(argv[11],"-h1"))
	 || (strcmp(argv[1],"-h2") && strcmp(argv[3],"-h2") && strcmp(argv[5],"-h2") && strcmp(argv[7],"-h2") && strcmp(argv[9],"-h2") && strcmp(argv[11],"-h2"))
	 || (strcmp(argv[1],"-b") && strcmp(argv[3],"-b") && strcmp(argv[5],"-b") && strcmp(argv[7],"-b") && strcmp(argv[9],"-b") && strcmp(argv[11],"-b")))
	{
		printf("Please try entering the Bitcoin Network again. Arguments given were either in the wrong order, or incorrect.\n");
		exit(-2);
	}
	char * bitcoinBalancesFile, * transactionsFile;			//variables passed on as arguements
	int bitcoinValue, senderEntries, receiverEntries, bucketSize;
/*-a*/
	//set variables assigned from input
	if (!(strcmp(argv[1],"-a"))) {bitcoinBalancesFile=malloc(sizeof(argv[2]+1));strncpy(bitcoinBalancesFile, argv[2], strlen(argv[2])+1);}
	else if (!(strcmp(argv[3],"-a"))) {bitcoinBalancesFile=malloc(sizeof(argv[4]+1));strncpy(bitcoinBalancesFile, argv[4], strlen(argv[4])+1);}
	else if (!(strcmp(argv[5],"-a"))) {bitcoinBalancesFile=malloc(sizeof(argv[6]+1));strncpy(bitcoinBalancesFile, argv[6], strlen(argv[6])+1);}
	else if (!(strcmp(argv[7],"-a"))) {bitcoinBalancesFile=malloc(sizeof(argv[8]+1));strncpy(bitcoinBalancesFile, argv[8], strlen(argv[8])+1);}	
	else if (!(strcmp(argv[9],"-a"))) {bitcoinBalancesFile=malloc(sizeof(argv[10]+1));strncpy(bitcoinBalancesFile, argv[10], strlen(argv[10])+1);}
	else if (!(strcmp(argv[11],"-a"))) {bitcoinBalancesFile=malloc(sizeof(argv[12]+1));strncpy(bitcoinBalancesFile, argv[12], strlen(argv[12])+1);}
/*-t*/
	if (!(strcmp(argv[1],"-t"))){transactionsFile=malloc(sizeof(argv[2]+1));strncpy(transactionsFile, argv[2], strlen(argv[2])+1);}
	else if (!(strcmp(argv[3],"-t"))) {transactionsFile=malloc(sizeof(argv[4]+1));strncpy(transactionsFile, argv[4], strlen(argv[4])+1);}
	else if (!(strcmp(argv[5],"-t"))) {transactionsFile=malloc(sizeof(argv[6]+1));strncpy(transactionsFile, argv[6], strlen(argv[6])+1);}
	else if (!(strcmp(argv[7],"-t"))) {transactionsFile=malloc(sizeof(argv[8]+1));strncpy(transactionsFile, argv[8], strlen(argv[8])+1);}
	else if (!(strcmp(argv[9],"-t"))) {transactionsFile=malloc(sizeof(argv[10]+1));strncpy(transactionsFile, argv[10], strlen(argv[10])+1);}
	else if (!(strcmp(argv[11],"-t"))) {transactionsFile=malloc(sizeof(argv[12]+1));strncpy(transactionsFile, argv[12], strlen(argv[12])+1);}

/*-v*/
	if (!(strcmp(argv[1],"-v"))) bitcoinValue=atoi(argv[2]);
	else if (!(strcmp(argv[3],"-v"))) bitcoinValue=atoi(argv[4]);
	else if (!(strcmp(argv[5],"-v"))) bitcoinValue=atoi(argv[6]);
	else if (!(strcmp(argv[7],"-v"))) bitcoinValue=atoi(argv[8]);
	else if (!(strcmp(argv[9],"-v"))) bitcoinValue=atoi(argv[10]);
	else if (!(strcmp(argv[11],"-v"))) bitcoinValue=atoi(argv[12]);
/*-h1*/
	if (!(strcmp(argv[1],"-h1"))) senderEntries=atoi(argv[2]);
	else if (!(strcmp(argv[3],"-h1"))) senderEntries=atoi(argv[4]);
	else if (!(strcmp(argv[5],"-h1"))) senderEntries=atoi(argv[6]);
	else if (!(strcmp(argv[7],"-h1"))) senderEntries=atoi(argv[8]);
	else if (!(strcmp(argv[9],"-h1"))) senderEntries=atoi(argv[10]);	
	else if (!(strcmp(argv[11],"-h1"))) senderEntries=atoi(argv[12]);
/*-h2*/
	if (!(strcmp(argv[1],"-h2"))) receiverEntries=atoi(argv[2]);
	else if (!(strcmp(argv[3],"-h2"))) receiverEntries=atoi(argv[4]);
	else if (!(strcmp(argv[5],"-h2"))) receiverEntries=atoi(argv[6]);
	else if (!(strcmp(argv[7],"-h2"))) receiverEntries=atoi(argv[8]);
	else if (!(strcmp(argv[9],"-h2"))) receiverEntries=atoi(argv[10]);	
	else if (!(strcmp(argv[11],"-h2"))) receiverEntries=atoi(argv[12]);
/*-b*/
	if (!(strcmp(argv[1],"-b"))) bucketSize=atoi(argv[2]);
	else if (!(strcmp(argv[3],"-b"))) bucketSize=atoi(argv[4]);
	else if (!(strcmp(argv[5],"-b"))) bucketSize=atoi(argv[6]);
	else if (!(strcmp(argv[7],"-b"))) bucketSize=atoi(argv[8]);
	else if (!(strcmp(argv[9],"-b"))) bucketSize=atoi(argv[10]);	
	else if (!(strcmp(argv[11],"-b"))) bucketSize=atoi(argv[12]);	
	/*END OF ARGUMENT CHECK*/
	/*----------------------------------------------------------------------------------------------------------------------------------*/
	FILE * file;					//variables to read file line by line
	char delimiter[]=" \n";
	char * token;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	file= fopen(bitcoinBalancesFile, "r");			//open bitcoin balances file
	if (file == NULL) exit(-1);
	printf("Opening file named %s.\n", bitcoinBalancesFile);
	walletListNode * walletstat=NULL;				//this will be head
	walletListNode * wlnode=NULL;					//this will parse list
	int flag=0;										//used to track first node and assign it to walletstat
	char * errorCheck="~";							//first char of str used to check for bitcoin duplicates
	bitcoinListNode * head=NULL;
	while ((read = getline(&line, &len, file)) != -1){		//every line= walletID bitcoinID1 bitcoinID2... bitcoiIDn
		int tokencount=0;				//bitcoin number
		token=strtok(line, delimiter);
		if (line==NULL) continue;	//if empty line, move on
		if(token!=NULL){		//once we find non empty line
			walletListNode * temp=addWalletNode(token, 0);	//balance initially marked 0 
			if (flag==0){		//if first line
				walletstat=temp;		//initialise head
				wlnode=walletstat;
				flag++;
			}
			else{
				wlnode->next=temp;		//make next non null and connect list
				wlnode=wlnode->next;
			}
			token=strtok(NULL, delimiter);		//now start reading bitcoinID's
		}
		
		while(token!=NULL){				//after reading , while line is not finished
			tokencount++;				//tokencount=#bitcoins per walletID
			bitcoinListNode * tempbit=NULL;
			tempbit=addBitcoinNode(tempbit, atoi(token), wlnode->walletID, bitcoinValue);		//add bitcoin to list of bitcoins
			errorCheck=checkDuplicates(token, errorCheck);
			if (flag==1){		//if first bitcoin
				head=tempbit;	//store head here
				wlnode->bcnode=head;
				flag++;
			}
			else{
				wlnode->bcnode->next=tempbit;		//make next non null and connect list
				wlnode->bcnode=wlnode->bcnode->next;
			}
			token=strtok(NULL, delimiter);
		}
		flag=1;				//so as to create new list for every walletnode
		if(!tokencount){
			wlnode->bcnode=NULL;
			wlnode->bcnode= addBitcoinNode(wlnode->bcnode, 0, wlnode->walletID, 0);		//wrong
		}	
		wlnode->balance= tokencount* bitcoinValue;	//acceptance: in this file, whoever has a bitcoin has the whole fraction
		if(tokencount) wlnode->bcnode=head;
	}
	fclose(file);			//close file and reinitialise for next .txt
	file=NULL;
	line=NULL;
	file= fopen(transactionsFile, "r");
	if (file == NULL) exit(-1);
	printf("Opening file named %s.\n", transactionsFile);
	bucketChain * shashTable=malloc(sizeof(bucketChain)*senderEntries);			//allocate 2 hash tables
	bucketChain * rhashTable=malloc(sizeof(bucketChain)*receiverEntries);
	for (int i = 0; i < senderEntries; i++) createBucketChain(&shashTable[i]);		//initialise them
	for (int i = 0; i < receiverEntries; i++) createBucketChain(&rhashTable[i]);
	walletListNode * temp=malloc(sizeof(walletListNode));
	if(!temp){					//temp will be used as senderWalletID
		printf("Something related to memory allocation went wrong.\n");
		exit(-1);
    }
    walletListNode * rec=malloc(sizeof(walletListNode));
	if(!rec){					//rec will be used as receiverWalletID
		printf("Something related to memory allocation went wrong.\n");
		exit(-1);
    }
    int day, month, year, hour, minute;			//keep these to store latest date and time
    char * tID="0";								//and largest transactionID
    int count=0;								//count will be used to mark how many bitcoins are used in every transaction
    while ((read = getline(&line, &len, file)) != -1){
		if(line==NULL) continue;				//if blank line, move on
		temp=NULL;
		transaction * tran=addTransaction(line);		//adds data to tran
		temp=searchWalletList(walletstat, tran->senderWalletID, temp);		//temp is a walletList Node
		rec=searchWalletList(walletstat, tran->receiverWalletID, rec);		//rec is the receiver walletListNode
		if(temp==NULL || (temp->balance) < tran->value){					//if user not found, or not enough balance left
			printf("Error in file: user %s either does not have enough balance available for transaction or does not exist.\n",tran->senderWalletID);
			exit(-1);
		}
		if(rec==NULL){			//if user not found
			printf("Error in file: user %s does not exist.\n",tran->receiverWalletID);
			exit(-1);
		}
		//decrease value from certain bitcoin
		(temp->reduced)+=(tran->value);				//to find how many dollars the user has paid
		(rec->added)+=(tran->value);				//to find how many dollars were received
		(temp->balance)-=(tran->value);				//modify balance
		(rec->balance)+=(tran->value);
		if((temp->balance)<0){			//so definitely everyone who exists in transaction file has enough balance for said transaction
			printf("Error, user does not have enough balance available for transaction.\n");
			exit(-1);
		} 
		count=-1;						//initialise it as negative, because decrement returns >=0
		count=decrementBitcoin(temp, tran->value);	//sender's bitcoins will be reduced by value, returns how many bitcoins were harmed
		day=tran->day; month=tran->month; year=tran->year;		//since file is ordered by date and time
		hour=tran->hour; minute=tran->minute;			//for /requestTransaction
		if(atoi(tran->transactionID) > atoi(tID)){		//if current transactionID is not greater or equal to previous
			tID=malloc(sizeof(char)*(strlen(tran->transactionID)+1));	//store greatest
			strncpy(tID, tran->transactionID, strlen(tran->transactionID)+1);
		}
		insert(shashTable, tran, senderEntries, tran->senderWalletID);		//insert in hashtables
		insert(rhashTable, tran, receiverEntries, tran->receiverWalletID);
		while(count>=0 && temp->bcnode!=NULL){	//count=#bitcoins affected, temp->bcnode->tree->amount  == amount
			(temp->bcnode->traninv)++; 			//increase number of transactions that involve current bitcoin
			temp->bcnode->tree=insertTree(temp->bcnode->tree, temp->walletID, temp->bcnode->tree->amount);//insert in rec as well
			bitcoinListNode * tempbitcoin=rec->bcnode;		//reach final bitcoin node of bitcoin list of receiver
			while(tempbitcoin!=NULL) tempbitcoin=tempbitcoin->next;				//add amount taken from sender
			tempbitcoin=addBitcoinNode(rec->bcnode, temp->bcnode->bitcoinID, tran->receiverWalletID, (tran->value)%bitcoinValue);
			temp->bcnode->tree=insertTree(temp->bcnode->tree, tran->receiverWalletID, tran->value);	
			temp->bcnode=temp->bcnode->next;
			count--;		
		}
	}
	line=NULL;
	fclose(file);
	free(bitcoinBalancesFile);
	free(transactionsFile);
	free(token);
/*----------------------------------------------------------------------------------------------------------------------------------*/
	while(1){
		//time to call user to request functions
		userInputCall(bitcoinValue, senderEntries, receiverEntries, day, month, year, hour, minute, tID, shashTable, rhashTable, walletstat);
	}
	return 0;
}
