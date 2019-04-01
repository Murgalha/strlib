#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "strlib.h"

char *newstr(char *str) {
    /* Check if pointer is NULL */
    if(!str)
        return NULL;
    int size = strlen(str);
    char *string = NULL;
    
    /* Copy argument into alloc'd string pointer */
    string = (char *) malloc (sizeof(char)*(size+1));
    memcpy(string, str, size);
    string[size] = '\0';
    
    return string;
}

void delstr(char *_self) {
    /* Return if pointer is null
     * Free otherwise */
    if(!_self)
        return;
    free(_self);
}

char *join(int n, char *_self, ...) {
    if(!_self)
        return NULL;
    
    va_list vl;
    int t;
    unsigned int i;

    /* n gets reduced in 1 because _self is not counted on loop */
    n--;

    /* Copy char *_self on a new string */
    char *ret = newstr(_self);
    int ret_len = strlen(ret);

    va_start(vl, _self);

    /* Number of arguments supposed to be n */
    for(t = 0; t < n; t++) {
        /* Get string for argument and extend char *ret size */
        char *_str = va_arg(vl, char *);
        if(!_str)
            continue;

        int arg_len = strlen(_str);
        ret = (char *) realloc (ret,
                sizeof(char)*(ret_len+arg_len+1));

        /* Concatenate each char of argument on ret */
        for(i = 0; i < arg_len; i++)
            ret[ret_len+i] = _str[i];
        ret_len += arg_len;
    }
    /* Append '\0' and end va_list */
    va_end(vl);
    ret[ret_len] = '\0';
    return ret;
}

void concat(int n, char *_self, ...) {
    if(!_self)
        return;

    va_list vl;
    int t;
    unsigned int i;
    int self_len = strlen(_self);

    /* n gets reduced in 1 because _self is not counted on loop */
    n--;

    va_start(vl, _self);

    /* Number of arguments supposed to be n */
    for(t = 0; t < n; t++) {
        /* Get string for argument and extend char *_self size */
        char *_str = va_arg(vl, char *);
        if(!_str)
            continue;
        int arg_len = strlen(_str);

        _self = (char *) realloc (_self,
                sizeof(char)*(self_len+arg_len+1));

        /* Concatenate each char of argument on self */
        for(i = 0; i < arg_len; i++)
            _self[self_len+i] = _str[i];
        self_len += arg_len;
    }
    /* Append '\0' and end va_list */
    va_end(vl);
    _self[self_len] = '\0';

}

char *substring(char *_self, int begin, int end) {
    if(begin < 0 || begin > strlen(_self))
        return NULL;
    if(end < 0 || end > strlen(_self))
        return NULL;
    if(begin > end || !_self)
        return NULL;

    /* allocate needed size */
    char *sub;
    int k, i = 0;
    sub = (char *) malloc (sizeof(char)*(end-begin+1));
    
    /* Copy each char from substring and append '\0' */
    for(k = begin; k < end; k++, i++)
        sub[i] = _self[k];
    sub[i] = '\0';
    
    return sub;
}

char **split(char *_self, int *nstrings, char *delims) {
    /* Return NULL if any given pointer is NULL */
    if(!_self || !nstrings)
        return NULL;

    /* If delims is null, return given string */
    if(!delims) {
        char **allstrings = (char **) malloc (sizeof(char *));
        allstrings[0] = newstr(_self);
        *nstrings = 1;
        return allstrings;
    }
    int i, k, t;
    int self_len = strlen(_self), delims_len = strlen(delims);
    char **allstrings = NULL;
    char *aux = NULL;
    *nstrings = 0;
    
    for(i = 0, t = 0; i < self_len; i++) {
        /* Insert char on auxiliary string */
        aux = (char *) realloc (aux, sizeof(char)*(t+1));
        aux[t++] = _self[i];

        /* Check if char is equal to each delimiter */
        for(k = 0; k < delims_len; k++) {
            if(aux[t-1] == delims[k]) {
                /* If delimiter appears, end string
                 * and insert on 'allstrings' */
                aux[t-1] = '\0';

                /* Insert on result only if aux->length > 1 */
                if(t > 1) {
                    allstrings = (char **) realloc (allstrings,
                            sizeof(char *)*((*nstrings)+1));
                    allstrings[(*nstrings)++] = aux;
                }
                
                /* Prepare to repeat */
                aux = NULL;
                t = 0;
                break;
            }
        }
    }
    /* Verify and insert final word */
    if(aux) {
        aux[t] = '\0';
        allstrings = (char **) realloc (allstrings,
                sizeof(char *)*((*nstrings)+1));
        allstrings[(*nstrings)++] = aux;
    }
    
    return allstrings;
}

void delsplit(char **s, int n) {
    /* Check if pointers are null
     * and free them */
    if(!s)
        return;
    int i;
    for(i = 0; i < n; i++)
        free(s[i]);
    free(s);
}
