#ifndef _STRLIB_H_
#define _STRLIB_H_

typedef struct {
    char *charptr;
    int length;
} STRING;

STRING *new(char *);
void delete(STRING *);
void concat(STRING *, STRING *);
STRING *substring(STRING *, int, int);
STRING **split(STRING *, int *, char *);
void delsplit(STRING **, int);

#endif
