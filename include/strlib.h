#ifndef _STRLIB_H_
#define _STRLIB_H_

typedef struct {
    char *charptr;
    int length;
} STRING;

STRING *newstr(char *);
void delstr(STRING *);
STRING *join(int n, STRING *, ...);
void concat(int n, STRING *, ...);
STRING *substring(STRING *, int, int);
STRING **split(STRING *, int *, char *);
void delsplit(STRING **, int);

#endif
