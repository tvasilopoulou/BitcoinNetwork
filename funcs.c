#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "header.h"

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

