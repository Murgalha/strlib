#ifndef _STRLIB_H_
#define _STRLIB_H_

#include <string.h>

/* Create and allocate new string given a char*.
   The function copies the string into the struct 
   and set its length */
char *newstr(char *);

/* Free the given char pointer
 * Simply calls free() */
void delstr(char *);

/* Join n strings passed as arguments.
   Return result string and do NOT modify
   any given argument.
   Appends '\0' in the end as terminating byte */
char *join(int n, char *, ...);

/* Concatenate n strings passed as arguments.
   Function MODIFIES the first string argument passed.
   Appends '\0' in the end as terminating byte */
void concat(int n, char *, ...);

/* Function receives a string pointer, the begin and end 
   of desired substring respectively and returns a newly allocated string 
   containing the desired substring.
   Returns NULL if numbers are < 0 or > string length */
char *substring(char *, int, int);

/* Function receives a string and the address of an integer
   along with the delimiters used to split. It verifies each delimiter char 
   with each char of string and split strings if they match.
   The integer passed is set with number of strings resulted of the split */
char **split(char *, int *, char *);

/* Free the splitted string result.
   Function needs an integer with number of splitted resulted strings */
void delsplit(char **, int);

#endif
