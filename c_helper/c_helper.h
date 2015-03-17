#ifndef C_HELPER_H_INCLUDED
#define C_HELPER_H_INCLUDED

// struct for when exploding strings into sub strings
struct exploded {
  char * string; // pointer to string
  struct exploded *next;
};


/*
  string replace function
  @string - input string
  @sub - string to substitute
  @replace - string to replace sub with

  Returns substring
*/
char * strreplace(char * string, char * sub, char * replace);

/*
  function to count number of chars in a string
  @string - input string
  @neelde - char to look for

  returns number of found occurances
*/
int numChar(char * string, char needle);


/*
  function to trim leading and trailing spaces in a string
  @string - input string

  Returns same string with leading and trailing spaces removed
*/
char * trim(char * string);

/*
  Function to get substring
  @string - input string
  @start - starting substring location
  @end - ending substring location

  Returns formatted string from @start to @end
*/
char * substr(char * string, int start, int end);


/*
  Function to find occurance of char in string
  @string - input string
  @needle - char to find in string
  @offset - to find nth @needle in @string
*/
int strpos(char * string, char needle, int offset);


/*
  Function to print struct that was used in an explode()
  Used mainly for debugging purposes 

  @exploded_ptr - pointer to exploded struct variable

  Prints each entry on a new line

  Returns void
*/
void print_exploded(struct exploded * exploded_ptr); 

/*
  Function to split a string by a string
  This is identical to PHP function explode()
  @string - input string
  @delimeter - string to split by

  Returns exploded struct
*/
struct exploded * explode(char * string, char * delimeter); 

/*
  Helper function for explode() to add new nodes based on each delimeter found in explode()

  @exploded_ptr - pointer to exploded struct
  @string - string to insert into struct

  Returns exploded struct
*/
struct exploded * exploded_add_node(struct exploded * exploded_ptr, char * string); 

/*
  Free memory from explode() function
  @head - Head node in exploded struct

  Returns void
*/
void freeExploded(struct exploded * head);

/*
  Function to convert a character to an integer
  @string - string to format to integer

  Returns integer
*/
int CharToInt(char * string);

#endif
