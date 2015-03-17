#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "c_helper.h"



/*
  string replace function
  @string - input string
  @sub - string to substitute
  @replace - string to replace sub with

  Returns substring
*/
char *strreplace(char *string, char *sub, char *replace){
  if(!string || !sub || !replace || strlen(sub) == 0) return NULL; // we need all inputs

  char *pos = string; // set pointer of pos to start of string
  char *findsub; // pointer to search for sub
  int counter = 0;
  // find occurance of string to substitute in string
  while(findsub = strstr(pos, sub)){
    counter++; // count number of occurances of sub in string
    pos = findsub + strlen(sub); // move pos to after found string to we can continue searching
  }

  // malloc memory for new string of length string - length sub * occurances + length repalce * occurances + 1(\0)
  char *result = (char*)malloc(strlen(string) - strlen(sub)*counter + strlen(replace)*counter + 1);
  // failed to allocate memory
  if(result == NULL){
    return NULL;
  }

  // reset memory locations
  pos = string; 
  while((findsub = strstr(pos, sub))){ // search for sub and point to start of memory location
    int len = (findsub - pos); // length = found memory location - beginning of string
    strncat(result, pos, len); // grab text up to found sub
    strncat(result, replace, strlen(replace)); //replace the found sub with replace
    pos = (findsub + strlen(sub)); // update pos to memory address after found sub so we can find the next sub in the entire string
  }

  // if we aren't at the end of the original string, we need to get what's left of original string
  if(pos != (string + strlen(string))){
    strcat(result, pos); // get the rest of the original string
  }
  
  return result; // return new string
}

/*
  function to count number of chars in a string
  @string - input string
  @neelde - char to look for

  returns number of found occurances
*/
int numChar(char * string, char needle){

  int counter = 0; // counter to return for number of occurances

  int len = strlen(string); // length of string
  int i = 0; // to iterate over string array
  for(i = 0; i < len; i++){
    if(needle == string[i]) // if needle found in string
      counter++; // increment counter
  }

  return counter; // return number of occurances
}

/*
  function to trim leading and trailing spaces in a string
  @string - input string

  Returns same string with leading and trailing spaces removed
*/
char * trim(char * string){
  char * ptr = string; //set ptr to beginning of string
  while(isspace(*ptr)){ // continually iterate while there are spaces
    ptr++; // move pointer to the right by one in the string to check next position for another space
  }

  char * ptr2; 
  ptr2 = string + strlen(string) - 1; // set ptr to end of string
  while(isspace(*ptr2)){// continually iterate while there are spaces
    ptr2--; // move pointer to the left by one in the string to check next position for another space
  }

  // calculate new string size
  int size = ptr2 - ptr + 1 + 1; // +1 for total length of string, +1 for null character
  // create new string with spaces removed
  char * newString = substr(string, ptr - string, ptr2 - string);
  // return trimmed string
  return newString;
}

/*
  Function to get substring
  @string - input string
  @start - starting substring location
  @end - ending substring location

  Returns formatted string from @start to @end
*/
char * substr(char * string, int start, int end){
  char * newString = malloc(end - start + 1 + 1); // get memory for new substring
  // failed to allocate memory
  if(newString == NULL){
    return NULL;
  }

  int counter = 0; // newString index
  while(start <= end){ // go through sub string
    newString[counter++] = string[start++]; // save sub string into new string
  }
  newString[counter] = '\0'; // put null terminator at end of new string

  return newString; // return substr
}




/*
  Function to find occurance of char in string
  @string - input string
  @needle - char to find in string
  @offset - to find nth @needle in @string
*/
int strpos(char * string, char needle, int offset) {
  int start = 0; // starting position
  int end = strlen(string); // ending position
  int count_found = 0; // to check against offset and find the nth(offset) occurance
  // iterate over entire string
  for(start = 0; start < end; start++) {
    // if needle found
    if(needle == string[start]) {
      // if offset matchces count_found
      if(offset == count_found)
        break; // we found our position, break out of for loop
      else
        count_found++; // we didn't find out position, increment count_found
    }
  }
  return start; // return found position of @needle in @string 
}


/*
  Function to print struct that was used in an explode()
  Used mainly for debugging purposes 

  @exploded_ptr - pointer to exploded struct variable

  Prints each entry on a new line

  Returns void
*/
void print_exploded(struct exploded * exploded_ptr) {
  // iterate over struct until we get to last node
  while(exploded_ptr->next != 0) {
    // print what is in each node
    printf("Found string: %s --\n", trim(exploded_ptr->string));
    // set node to next node
    exploded_ptr = exploded_ptr->next;
  }
}


/*
  Function to split a string by a string
  This is identical to PHP function explode()
  @string - input string
  @delimeter - string to split by

  Returns exploded struct
*/
struct exploded * explode(char * string, char * delimeter){
  char * ptr = string;
  char * oldptr = string;

  // length of string
  int string_length = strlen(string);

  // first node of exploded string
  struct exploded *exploded_ptr = malloc(sizeof(struct exploded));

  // a traverse pointer to traverse the exploded_ptr struct
  struct exploded *exploded_t = exploded_ptr;
  exploded_t->next = 0; // null the next pointer

  // iterate over string baesd on delimeter
  while(ptr = strstr(oldptr, delimeter)){
    // calculate start and end points int hte string to save into struct
    int start = oldptr - string;
    int end = ptr - string - 1;

    // save string, add new node, return pointer to new node
    exploded_t = exploded_add_node(exploded_t, substr(string, start, end));
    // move the pointer of the string past what was found
    ptr = ptr + strlen(delimeter);
    oldptr = ptr;
  }
  
  // copy what's remaining of string to a new node || or if no delimeter exists, this will set the struct to the entire string
  if(oldptr < (string + string_length)){ // theres still string remaining
    // calculate points in string that was trailing to save into struct
    int start = oldptr - string;
    int end = string_length - 1;

    // save string, add new node, return pointer to new node
    exploded_t = exploded_add_node(exploded_t, substr(string, start, end));
  }
  // return exploded string
  return exploded_ptr;
}


/*
  Helper function for explode() to add new nodes based on each delimeter found in explode()

  @exploded_ptr - pointer to exploded struct
  @string - string to insert into struct

  Returns exploded struct
*/
struct exploded * exploded_add_node(struct exploded * exploded_ptr, char * string){
  // save string into node
  exploded_ptr->string = string;
  // allocate memory for next pointer in the struct
  exploded_ptr->next = malloc(sizeof(struct exploded)); 
  // set struct pointer to next node
  exploded_ptr = exploded_ptr->next;
  // set next next node to null
  exploded_ptr->next = 0;
  // return inserted node
  return exploded_ptr;
}

/*
  Free memory from explode() function
  @head - Head node in exploded struct

  Returns void
*/
void freeExploded(struct exploded * head){
  // temporary struct for freeing memory
  struct exploded * tmp;
  // iterate over struct to free memory for each node
  while(head != NULL){
    //set tmp to head
    tmp = head;
    // head to next node
    head = head->next;
    // free tmp (original head)
    free(tmp);
  }
}

/*
  Function to convert a character to an integer
  @string - string to format to integer

  Returns integer
*/
int CharToInt(char * string) {
  // convert string into int
  int value = atoi(string);
  // return calculated int
  return value;
}
