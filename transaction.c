#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "transaction.h"


transaction * createTransaction(void){			//initialise transactions with 0's
	transaction * node=malloc(sizeof(transaction));
	if(!node){
		printf("Something related to memory allocation went wrong.\n");
		exit(-1);
	}
	node->value=0;
	node->day=0;
	node->month=0;
	node->year=0;
	node->hour=0;
	node->minute=0;
	return node;
}


transaction * addTransaction(char * line){
	char delimiter[]=" -:";
	char * token=strtok(line, delimiter);			//pass data into transaction struct
	transaction * tran=createTransaction();

	tran->transactionID=malloc(sizeof(char)*(strlen(token)+1));
	strncpy(tran->transactionID, token, strlen(token)+1); token=strtok(NULL, delimiter);

	tran->senderWalletID=malloc(sizeof(char)*(strlen(token)+1));
	strncpy(tran->senderWalletID, token, strlen(token)+1); token=strtok(NULL, delimiter);

	tran->receiverWalletID=malloc(sizeof(char)*(strlen(token)+1));
	strncpy(tran->receiverWalletID, token, strlen(token)+1); token=strtok(NULL, delimiter);

	tran->value=atoi(token); token=strtok(NULL, delimiter);
	tran->day=atoi(token); token=strtok(NULL, delimiter);			//check for errors
	tran->month=atoi(token); token=strtok(NULL, delimiter);
	tran->year=atoi(token); token=strtok(NULL, delimiter);
	tran->hour=atoi(token); token=strtok(NULL, delimiter);
	tran->minute=atoi(token);
	return tran;
}


transaction * requestTransaction(char * line, char * transactionID, int day, int month, int year, int hour, int minute, bucketChain * shashTable, bucketChain * rhashTable, int senderEntries, int receiverEntries, walletListNode * tempwall)
{
	char delimiter[]=" -:";
	transaction * tran=createTransaction();
	char * token=strtok_r(line, delimiter, &line);
	int inttid=atoi(transactionID);			//assign new id, greater by one every time function is called
	inttid++;
	transactionID=itoa(inttid, transactionID);
	tran->transactionID=malloc(sizeof(char)*(strlen(transactionID)+1));
	strncpy(tran->transactionID, transactionID, strlen(transactionID)+1);
	tran->senderWalletID=malloc(sizeof(char)*(strlen(tempwall->walletID)+1));
	strncpy(tran->senderWalletID, tempwall->walletID, strlen(tempwall->walletID)+1);
	tran->receiverWalletID=malloc(sizeof(char)*(strlen(token)+1));
	strncpy(tran->receiverWalletID, token, strlen(token)+1); token=strtok_r(line, delimiter, &line);
	tran->value=atoi(token); token=strtok_r(line, delimiter, &line);
	if(token==NULL){				//if date and time not specified, use current
		time_t t = time(NULL);		//https://stackoverflow.com/questions/1442116/how-to-get-the-date-and-time-values-in-a-c-program
		struct tm tm = *localtime(&t);
		tran->day=tm.tm_mday; 
		tran->month=tm.tm_mon + 1;
		tran->year=tm.tm_year + 1900;
		tran->hour=tm.tm_hour;
		tran->minute=tm.tm_min;
	}
	else{
		tran->day=atoi(token); token=strtok_r(line, delimiter, &line);	//else pass data from call
		tran->month=atoi(token); token=strtok_r(line, delimiter, &line);
		tran->year=atoi(token); token=strtok_r(line, delimiter, &line);
		tran->hour=atoi(token); token=strtok_r(line, delimiter, &line);
		tran->minute=atoi(token);		
	}
	if(tempwall==NULL || (tempwall->balance) < tran->value){			//tempwall is sender
		printf("Error in file: user %s either does not have enough balance available for transaction or does not exist.\n",tran->senderWalletID);
		exit(-1);
	}
	//if transaction happens later than latest previous transaction
	if((tran->year) > year || (tran->year) == year && (tran->month) > month || (tran->year) == year && (tran->month) == month && (tran->day) > day 
		|| (tran->year) == year && (tran->month) == month && (tran->day) == day && (tran->hour) > hour 
		|| (tran->year) == year && (tran->month) == month && (tran->day) == day && (tran->hour) == hour && (tran->minute)>=minute){

		(tempwall->balance)-=(tran->value);		//reduce balance
		insert(shashTable, tran, senderEntries, tran->senderWalletID);		//insert in hash table this transaction too
		insert(rhashTable, tran, receiverEntries, tran->receiverWalletID);
		printf("Transaction request number %s: granted.\n",tran->transactionID);
		printf("Transaction details: Sender: %s \t Receiver: %s \t Amount transfered: %d \t Date: %d-%d-%d \t Time: %d:%d \n",
				tran->senderWalletID, tran->receiverWalletID, tran->value, tran->day, tran->month,tran->year, tran->hour, tran->minute );
		return tran;
	}
	return NULL;
}


char* itoa(int i, char * b){			//https://stackoverflow.com/questions/9655202/how-to-convert-integer-to-string-in-c
	char const digit[] = "0123456789";		//covert integer to string
	char* p = b;
	if(i<0){
		*p++ = '-';
		i *= -1;
	}
	int shifter = i;
	do{ //Move to where representation ends
		++p;
		shifter = shifter/10;
	}while(shifter);
	*p = '\0';
	do{ //Move back, inserting digits as u go
		*--p = digit[i%10];
		i = i/10;
	}while(i);
	return b;
}

char * determineSender(char * str){
	str=createInput(str);			//read first token that when function is called will throw out first word
	char * token=strtok(str, " ");
	return token;
}