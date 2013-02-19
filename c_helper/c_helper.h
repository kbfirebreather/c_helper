#ifndef C_HELPER_H_INCLUDED
#define C_HELPER_H_INCLUDED


struct exploded {
  char * string; // pointer to string
	struct exploded *next;
};



char * strreplace(char * string, char * sub, char * replace);

int numChar(char * string, char needle); // search string for needle, return num occurances

char * trim(char * string); // trims leading and trailing spaces in string

char * substr(char * string, int start, int end); // get sub string from start to end

struct exploded * explode(char * string, char * delimeter); // explodes string into pieces, setting each piece to a node in struct exploded

struct exploded * exploded_add_node(struct exploded * exploded_ptr, char * string); // assists explode(), adds string to exploded_ptr and returns next node in exploded_ptr

void freeExploded(struct exploded * head);

#endif
