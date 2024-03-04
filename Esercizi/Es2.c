#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void upo_mem_set(void* p, unsigned char c, size_t n);

int main(){

    char cary[]="Hello, World!";
    upo_mem_set(cary, '?', strlen(cary));
    printf("cary: '%s'\n", cary);

    int i=10;
    upo_mem_set(&i, 0, sizeof i);
    printf("i: %d\n", i);

    unsigned char ucary[] = {255, 128, 64, 32, 16, 8};
    upo_mem_set(ucary, 127, (sizeof(ucary))/2);
    printf("ucary: {");
    for (size_t i = 0; i < sizeof(ucary) / sizeof(ucary[0]); i++) {
        printf("%u, ", ucary[i]);
    }
    printf("}\n");

    return 0;
}

void upo_mem_set(void* p, unsigned char c, size_t n){
    assert(p!=NULL);

    unsigned char *pc=p;

    for(size_t i=0; i<n; i++){
        pc[i]=c;
    }
}
