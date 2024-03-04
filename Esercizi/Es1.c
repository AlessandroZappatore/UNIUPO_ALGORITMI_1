#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void upo_hex_fprintf(FILE *stream, const void *p, size_t n);

int main(){
    char *s="Hello, World!";
    upo_hex_fprintf(stdout, s, strlen(s));

    char cary[]="GNU is Not Unix";
    upo_hex_fprintf(stdout, cary + (sizeof(cary))/2, sizeof cary - (sizeof(cary))/2);

    unsigned char uncary[]={255, 128, 64, 32, 16};
    upo_hex_fprintf(stdout, uncary, sizeof uncary);
    return 0;
}

void upo_hex_fprintf(FILE *stream, const void *p, size_t n){
    assert(p!=NULL);

    const unsigned char *pc=p;
    for(size_t i=0; i<n; i++){
        fprintf(stream, "%X ", pc[i]);
    }
    fprintf(stream, "\n");
}