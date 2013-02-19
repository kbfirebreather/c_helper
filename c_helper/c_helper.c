#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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

char * trim(char * string){
	char * ptr = string;
	while(isspace(*ptr))
	{
		ptr++;
	}

	char * ptr2;
	ptr2 = string + strlen(string) - 1;
	while(isspace(*ptr2))
	{
		ptr2--;
	}

	int size = ptr2 - ptr + 1 + 1; // +1 for total length of string, +1 for null character
	char * newString = substr(string, ptr - string, ptr2 - string);

	return newString;

}

// return sub string of string from index start to index end
char * substr(char * string, int start, int end){
	char * newString = malloc(end - start + 1 + 1); // get memory for new substring

	int counter = 0; // newString index
	while(start <= end){ // go through sub string
		newString[counter++] = string[start++]; // save sub string into new string
	}
	newString[counter] = '\0'; // put null terminator at end of new string

	return newString; // return
}


int numChar(char * string, char needle){

	int counter = 0;

	int len = strlen(string);
	int i = 0;
	for(i = 0; i < len; i++){
		if(needle == string[i])
			counter++;
	}

	return counter;
}

struct exploded * explode(char * string, char * delimeter){
	char * ptr = string;
	char * oldptr = string;

	int string_length = strlen(string);

	struct exploded *exploded_ptr = malloc(sizeof(struct exploded)); // first node

	struct exploded *exploded_t = exploded_ptr; // to traverse explode_ptr
	exploded_t->next = 0; // null the next pointer

	while(ptr = strstr(oldptr, delimeter))
	{
		int start = oldptr - string;
		int end = ptr - string - 1;

		// save string, add new node, return pointer to new node
		exploded_t = exploded_add_node(exploded_t, substr(string, start, end));

		ptr = ptr + strlen(delimeter);
		oldptr = ptr;
	}
	
	// copy what's remaining of string to a new node || or if no delimeter exists, this will set the struct to the entire string
	if(oldptr < (string + string_length)) // theres still stuff remaining
	{
		int start = oldptr - string;
		int end = string_length - 1;

		// save string, add new node, return pointer to new node
		exploded_t = exploded_add_node(exploded_t, substr(string, start, end));
	}

	return exploded_ptr;
}

// copy string ot current node->string
// create new node, update nodes pointers
// return address to new node
struct exploded * exploded_add_node(struct exploded * exploded_ptr, char * string){
	exploded_ptr->string = string;
	exploded_ptr->next = malloc(sizeof(struct exploded)); // point to new exploded struct
	exploded_ptr = exploded_ptr->next; // move to this next point
	exploded_ptr->next = 0; // set next to null

	return exploded_ptr;
}

// frees all the nodes in exploded
void freeExploded(struct exploded * head)
{
	struct exploded * tmp;
	while(head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

// returns 1 if string == true, 0 if not
int stringToBool(char * string){
	if(strcasecmp(string, "true") == 0)
		return 1;

	if(strcasecmp(string, "false") == 0)
		return 0;
	else
		return -1;
}

