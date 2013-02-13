#include <string.h>
#include <stdlib.h>
#include "c_helper.h"

//my replace
char *strreplace(char *string, char *sub, char *replace)
{
	if(!string || !sub || !replace || strlen(sub) == 0) return NULL; // we need all inputs

	char *pos = string; // set pointer of pos to start of string
	char *findsub; // pointer to search for sub
	int counter = 0;
	while(findsub = strstr(pos, sub)){
		counter++; // count number of occurances of sub in string
		pos = findsub + strlen(sub);
	}

	char *result = (char*)malloc(strlen(string) - strlen(sub)*counter + strlen(replace)*counter + 1); // malloc memory for new string of length string - length sub * occurances + length repalce * occurances + 1(\0)
	if(result == NULL){
		return NULL;
	}

	// reset memory locations
	pos = string;	
	while((findsub = strstr(pos, sub))) // search for sub and point to start of memory location
	{ 
		int len = (findsub - pos); // length = found memory locatino - beginning of string
		strncat(result, pos, len); // grab text up to found sub
		strncat(result, replace, strlen(replace)); //replace the found sub with replace
		pos = (findsub + strlen(sub)); // update pos to memory address after found sub so we can find the next sub in the entire string
	}

	// if we aren't at the end of the original string, we need to get what's left of original string
	if(pos != (string + strlen(string)))
	{
		strcat(result, pos); // get the rest of the original string
	}
	
	return result; // return new string
}