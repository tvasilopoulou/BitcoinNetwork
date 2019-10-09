#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


int hash(char *key, int size){		//modified hash function: https://gist.github.com/tonious/1377667
	int hashval;
	int i = 0;
	while(i < strlen( key ) ) {
		hashval = hashval << 8;
		hashval += key[ i ];
		i++;
	}
	return hashval % size;
}

void createBucketChain( bucketChain * chain ){		//initialise hash table
	chain->bucketHead=NULL;
	chain->size=0;
}

/*bucket * bucketChainInsert(bucketChain * , transaction * );*/
bucket * bucketChainInsert(bucketChain * chain, transaction * tran){		//insert as bucket
	bucket * buck=malloc(sizeof(bucket));
	buck->tran=tran;
	if (chain->bucketHead==NULL)
	{
		chain->bucketHead=buck;
		buck->next=NULL;
		(chain->size)++;
		return buck;
	}
	bucket * temp= chain->bucketHead;
	while(temp->next!=NULL) temp=temp->next;
	buck->next=temp->next;
	temp->next=buck;
	(chain->size)++;
	return buck;
}


void insert(bucketChain * chain, transaction * tran, int size, char * key){		//size=hashtablesize, key=walletID
	int index=hash(key, size);
	bucket * buck=bucketChainInsert(&chain[index], tran);		//insert in hash table
}

void deleteHashTable(bucketChain * head){
	bucket * current=malloc(sizeof(bucket));
	bucket * next=malloc(sizeof(bucket));
	current=head->bucketHead;
	while (current != NULL){
		next = current->next;
		free(current->tran);
		free(current);
		current = next;
	}
	free(head);
}
