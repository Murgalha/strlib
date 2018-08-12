#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strlib.h"

STRING *new(char *str) {
    int size = 0;
    STRING *string = (STRING *) malloc (sizeof(STRING));

    string->length = strlen(str);
    string->charptr = (char *) malloc (sizeof(char)*(string->length+1));
    memcpy(string->charptr, str, string->length+1);
    
    return string;
}

void delete(STRING *_self) {
    free(_self->charptr);
    free(_self);
}

void concat(STRING *_self, STRING *_str) {
    _self->charptr = (char *) realloc (_self->charptr,
                                       sizeof(char)*(_self->length+_str->length+1));

    unsigned int i, k = 0;
    for(i = 0; i < _str->length; i++, k++)
        (_self->charptr)[_self->length+k] = (_str->charptr)[i];
    (_self->charptr)[_self->length+_str->length] = '\0';
    _self->length = (_self->length)+(_str->length);
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
    STRING *strdelims = new(delims);
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
                    STRING *tmp = new(aux);
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
        STRING *tmp = new(aux);
        allstrings[(*nstrings)++] = tmp;
        free(aux);
    }
    delete(strdelims);
    return allstrings;
}

void delsplit(STRING **s, int n) {
    int i;
    for(i = 0; i < n; i++)
        free(s[i]);
    free(s);
}
