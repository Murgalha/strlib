#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "strlib.h"

STRING *newstr(char *str) {
    /* Check if pointer is NULL */
    if(!str)
        return NULL;
    int size = 0;
    STRING *string = (STRING *) malloc (sizeof(STRING));

    /* Set string length and copy argument into alloc'd string pointer */
    string->length = strlen(str);
    string->charptr = (char *) malloc (sizeof(char)*(string->length+1));
    memcpy(string->charptr, str, string->length);
    string->charptr[string->length] = '\0';
    
    return string;
}

void delstr(STRING *_self) {
    /* Return if pointer is null
     * Free struct otherwise */
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

    /* n gets reduced in 1 because _self is not counted on loop */
    n--;

    /* Copy STRING *_self on a new string */
    STRING *ret = newstr(_self->charptr);

    va_start(vl, _self);

    /* Number of arguments supposed to be n */
    for(t = 0; t < n; t++) {
        /* Get string for argument and extend STRING *ret size */
        STRING* _str = va_arg(vl, STRING*);
        if(!_str)
            continue;
        ret->charptr = (char *) realloc (ret->charptr,
                                           sizeof(char)*(ret->length+_str->length+1));

        /* Concatenate each char of argument on ret */
        for(i = 0; i < _str->length; i++)
            (ret->charptr)[ret->length+i] = (_str->charptr)[i];
        ret->length += (_str->length);
    }
    /* Append '\0' and end va_list */
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
    
    /* n gets reduced in 1 because _self is not counted on loop */
    n--;

    va_start(vl, _self);

    /* Number of arguments supposed to be n */
    for(t = 0; t < n; t++) {
        /* Get string for argument and extend STRING *_self size */
        STRING* _str = va_arg(vl, STRING*);
        if(!_str)
            continue;
        _self->charptr = (char *) realloc (_self->charptr,
                                           sizeof(char)*(_self->length+_str->length+1));

        /* Concatenate each char of argument on self */
        for(i = 0; i < _str->length; i++)
            (_self->charptr)[_self->length+i] = (_str->charptr)[i];
        _self->length += (_str->length);
    }
    /* Append '\0' and end va_list */
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

    /* allocate needed size */
    STRING *sub = (STRING *) malloc (sizeof(STRING));
    int k, i = 0;
    sub->charptr = (char *) malloc (sizeof(char)*(end-begin+1));
    
    /* Copy each char from substring and append '\0' */
    for(k = begin; k < end; k++, i++)
        (sub->charptr)[i] = (_self->charptr)[k];
    (sub->charptr)[i] = '\0';
    /* Set length */
    sub->length = end-begin;
    
    return sub;
}

STRING **split(STRING *_self, int *nstrings, char *delims) {
    /* Return NULL if any given pointer is NULL */
    if(!_self || !nstrings)
        return NULL;

    /* If delims is null, return given string */
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
        /* Insert char on auxiliary string */
        aux = (char *) realloc (aux, sizeof(char)*(t+1));
        aux[t++] = (_self->charptr)[i];

        /* Check if char is equal to each delimiter */
        for(k = 0; k < strdelims->length; k++) {
            if(aux[t-1] == (strdelims->charptr)[k]) {
                /* If delimiter appears, end string
                 * and insert on 'allstrings' */
                aux[t-1] = '\0';

                /* Insert on result only if aux->length > 1 */
                if(t > 1) {
                    allstrings = (STRING **) realloc (allstrings,
                                                      sizeof(STRING *)*((*nstrings)+1));
                    STRING *tmp = newstr(aux);
                    allstrings[(*nstrings)++] = tmp;
                }
                
                /* Free and repeat */
                free(aux);
                aux = NULL;
                t = 0;
                break;
            }
        }
    }
    /* Verify and insert final word */
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
    /* Check if pointers are null
     * and free them */
    if(!s)
        return;
    int i;
    for(i = 0; i < n; i++)
        free(s[i]);
    free(s);
}
