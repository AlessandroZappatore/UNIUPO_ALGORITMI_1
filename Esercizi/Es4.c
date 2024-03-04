#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int upo_all_of(const void *base, size_t n, size_t sz, int(*pred)(const void *));
int is_even(const void *v);
int is_palindrome(const void *v);

int main(){

    int iary[]={3, 2, 7};
    size_t n_iary=3, sz_iary=sizeof(int);
    printf("iary: %d\n", upo_all_of(iary, n_iary, sz_iary, is_even));

    char *sary[]={"a", "b", "a"};
    size_t n_sary=sizeof(sary)/sizeof(sary[0]), sz_sary=sizeof(sary[0]);
    printf("sary: %d\n", upo_all_of(sary, n_sary, sz_sary, is_palindrome));

    char *sary2[]={"a", "b", "c", "d", "e"};
    size_t n_sary2=sizeof(sary2)/sizeof(sary2[0]), sz_sary2=sizeof(sary2[0]);
    printf("sary2: %d\n", upo_all_of(sary2, n_sary2, sz_sary2, is_palindrome));

    return 0;
}

int upo_all_of(const void *base, size_t n, size_t sz, int(*pred)(const void *)){
    assert(base!=NULL);

    for(size_t i=0; i<n; i++){
        if(!pred((unsigned char*)base+i*sz)) return 0;
    }
    return 1;
}

int is_even(const void *v){
    assert(v);
    return *((const int*) v)%2;
}

int is_palindrome(const void *v){
    assert(v);

    const char **ps=(const char**) v;
    size_t len=strlen(*ps);

    for(size_t i=0; i<len/2; ++i){
        if((*ps)[i] != (*ps)[len-i-1]) return 0;
    }
    return 1;
}
