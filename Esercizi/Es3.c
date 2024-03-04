#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int upo_mem_cmp(const void *p1, const void *p2, size_t n);

int main(){
    int a=2, b=20;
    printf("Risultato %d, %d: %d\n", a, b, upo_mem_cmp(&a, &b, sizeof(a)));

    int c=10, d=10;
    printf("Risultato %d, %d: %d\n", c, d, upo_mem_cmp(&c, &d, sizeof(c)));

    char *s="axcv", *f="abc";
    printf("Risultato %s, %s: %d\n", s, f, upo_mem_cmp(s, f, sizeof(s)*3));
    printf("Memcmp: %d\n", memcmp(s, f, 3));

    return 0;
}

int upo_mem_cmp(const void *p1, const void *p2, size_t n){
    assert(p1!=NULL);
    assert(p2!=NULL);

    const unsigned char *pc=p1;
    const unsigned char *pd=p2;
    int res=0;
    size_t i;
    for(i=0; i<n && res!=1; i++){
        if(pc[i]!=pd[i]) res=1;
    }
    if(res){
        return pc[i-1]-pd[i-1];
    }else return 0;
}