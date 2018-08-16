#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "strlib.h"

STRING *newstr(char *str) {
    if(!str)
        return NULL;
    int size = 0;
    STRING *string = (STRING *) malloc (sizeof(STRING));

    string->length = strlen(str);
    string->charptr = (char *) malloc (sizeof(char)*(string->length+1));
    memcpy(string->charptr, str, string->length);
    string->charptr[string->length] = '\0';
    
    return string;
}

void delstr(STRING *_self) {
    if(!_self)
        return;
    free(_self->charptr);
    free(_self);
}

STRING *join(int n, STRING *_self, ...) {
    if(!_self)
        return NULL;
    
    va_list vl;
    int t;
    unsigned int i;
    n--;
    STRING *ret = newstr(_self->charptr);

    va_start(vl, _self);

    for(t = 0; t < n; t++) {
        STRING* _str = va_arg(vl, STRING*);
        ret->charptr = (char *) realloc (ret->charptr,
                                           sizeof(char)*(ret->length+_str->length+1));

        for(i = 0; i < _str->length; i++)
            (ret->charptr)[ret->length+i] = (_str->charptr)[i];
        ret->length += (_str->length);
    }
    va_end(vl);
    (ret->charptr)[ret->length] = '\0';
    return ret;
}

void concat(int n, STRING *_self, ...) {
    if(!_self)
        return;

    va_list vl;
    int t;
    unsigned int i;
    n--;

    va_start(vl, _self);

    for(t = 0; t < n; t++) {
        STRING* _str = va_arg(vl, STRING*);
        if(!_str)
            continue;
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
    if(begin < 0 || begin > _self->length);
        return NULL;
    if(end < 0 || end > _self->length);
        return NULL;
    if(begin > end || !_self)
        return NULL;

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
    if(!_self || !nstrings)
        return NULL;
    if(!delims) {
        STRING **allstrings = (STRING **) malloc (sizeof(STRING *));
        allstrings[0] = newstr(_self->charptr);
        *nstrings = 1;
        return allstrings;
    }
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
    if(!s)
        return;
    if(!(*s))
        return;
    int i;
    for(i = 0; i < n; i++)
        free(s[i]);
    free(s);
}
