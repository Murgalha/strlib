#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "strlib.h"

STRING *newstr(char *str) {
    int size = 0;
    STRING *string = (STRING *) malloc (sizeof(STRING));

    string->length = strlen(str);
    string->charptr = (char *) malloc (sizeof(char)*(string->length+1));
    memcpy(string->charptr, str, string->length);
    string->charptr[string->length] = '\0';
    
    return string;
}

void delstr(STRING *_self) {
    free(_self->charptr);
    free(_self);
}

void concat(int n, STRING *_self, ...) {
    va_list vl;
    int t;
    unsigned int i;
    n--;

    va_start(vl, _self);

    for(t = 0; t < n; t++) {
        STRING* _str = va_arg(vl, STRING*);
        _self->charptr = (char *) realloc (_self->charptr,
                                           sizeof(char)*(_self->length+_str->length+1));

        for(i = 0; i < _str->length; i++)
            (_self->charptr)[_self->length+i] = (_str->charptr)[i];
        _self->length += (_str->length);
    }
    va_end(vl);
    (_self->charptr)[_self->length] = '\0';
}

STRING *substring(STRING *_self, int begin, int end) {
    STRING *sub = (STRING *) malloc (sizeof(STRING));
    int k, i = 0;
    sub->charptr = (char *) malloc (sizeof(char)*(end-begin+1));

    for(k = begin; k < end; k++, i++)
        (sub->charptr)[i] = (_self->charptr)[k];
    (sub->charptr)[i] = '\0';
    sub->length = end-begin;
    
    return sub;
}

STRING **split(STRING *_self, int *nstrings, char *delims) {
    int i, k, t;
    STRING **allstrings = NULL;
    STRING *strdelims = newstr(delims);
    char *aux = NULL;
    *nstrings = 0;
    
    for(i = 0, t = 0; i < _self->length; i++) {
        aux = (char *) realloc (aux, sizeof(char)*(t+1));
        aux[t++] = (_self->charptr)[i];

        for(k = 0; k < strdelims->length; k++) {
            if(aux[t-1] == (strdelims->charptr)[k]) {
                aux[t-1] = '\0';
                if(t > 1) {
                    allstrings = (STRING **) realloc (allstrings,
                                                      sizeof(STRING *)*((*nstrings)+1));
                    STRING *tmp = newstr(aux);
                    allstrings[(*nstrings)++] = tmp;
                }
                free(aux);
                aux = NULL;
                t = 0;
                break;
            }
        }
    }
    if(aux) {
        aux[t] = '\0';
        allstrings = (STRING **) realloc (allstrings,
                                          sizeof(STRING *)*((*nstrings)+1));
        STRING *tmp = newstr(aux);
        allstrings[(*nstrings)++] = tmp;
        free(aux);
    }
    delstr(strdelims);
    return allstrings;
}

void delsplit(STRING **s, int n) {
    int i;
    for(i = 0; i < n; i++)
        free(s[i]);
    free(s);
}

int main() {
    STRING* str1 = newstr("teste");
    STRING* str2 = newstr("oi");
    STRING* str3 = newstr("tchau");
    concat(3, str1, str2, str3);
    printf("%s\n", str1->charptr);
}
