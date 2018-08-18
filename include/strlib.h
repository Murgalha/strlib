#ifndef _STRLIB_H_
#define _STRLIB_H_

/* Basic struct of the lib, 
   containing the pointer to the string 
   and its length */
typedef struct {
    char *charptr;
    int length;
} STRING;

/* Create and allocate new STRING given a char*.
   The function copies the string into the struct 
   and set its length */
STRING *newstr(char *);

/* Free the given STRING structure pointer */
void delstr(STRING *);

/* Join n strings passed as arguments.
   Return result string and do NOT modify
   any given argument.
   Appends '\0' in the end as terminating byte */
STRING *join(int n, STRING *, ...);

/* Concatenate n strings passed as arguments.
   Function MODIFIES the first string argument passed.
   Appends '\0' in the end as terminating byte */
void concat(int n, STRING *, ...);

/* Function receives a string pointer, the begin and end 
   of desired substring respectively and returns a newly allocated string 
   containing the desired substring.
   Returns NULL if numbers are < 0 or > string length */
STRING *substring(STRING *, int, int);

/* Function receives a string and the address of an integer
   along with the delimiters used to split. It verifies each delimiter char 
   with each char of string and split strings if they match.
   The integer passed is set with number of strings resulted of the split */
STRING **split(STRING *, int *, char *);

/* Free the splitted string result.
   Function needs an integer with number of splitted resulted strings */
void delsplit(STRING **, int);

#endif
