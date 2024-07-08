/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */


/******************************************************************************/
/*** NOME:                                                                  ***/
/*** COGNOME:                                                               ***/
/*** MATRICOLA:                                                             ***/
/******************************************************************************/


#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/bst.h>
#include <upo/hashtable.h>


/**** BEGIN of EXERCISE #1 ****/

size_t upo_bst_subtree_count_even(const upo_bst_t bst, const void *key)
{
    if(bst == NULL) return 0;
    
    size_t depth = 0;
    upo_bst_node_t* node = findNode(bst->root, key, bst->key_cmp, &depth);
    if(node == NULL) return 0;
    return upo_bst_subtree_count_even_impl(node, depth);
}

size_t upo_bst_subtree_count_even_impl(upo_bst_node_t* node, size_t depth){
    if(node!=NULL){
        int count=0;

        if((depth%2)==0) count=1;

        return count+upo_bst_subtree_count_even_impl(node->left, depth+1)+upo_bst_subtree_count_even_impl(node->right, depth+1);
    }
    return 0;
    }

upo_bst_node_t* findNode(upo_bst_node_t* node, const void* key, upo_bst_comparator_t key_cmp, size_t* depth){
    if(node == NULL) return NULL;
    int cmp = key_cmp(node->key, key);
    if(cmp == 0) return node;
    else if(cmp > 0) {
        *depth+=1;
         return findNode(node->left, key, key_cmp, depth);}
    else  {
        *depth+=1;
        return findNode(node->right, key, key_cmp, depth);}
}

/**** END of EXERCISE #1 ****/


/**** BEGIN of EXERCISE #2 ****/

void upo_ht_sepchain_odelete(upo_ht_sepchain_t ht, const void *key, int destroy_data)
{
    if(!upo_ht_sepchain_is_empty(ht)){
        size_t hash = ht->key_hash(key, ht->capacity);

        upo_ht_sepchain_list_node_t* node = ht->slots[hash].head;
        upo_ht_sepchain_list_node_t* pred = NULL;

        while(node != NULL && ht->key_cmp(key, node->key) > 0){
            pred = node;
            node = node->next;
        }

        if(node != NULL && ht->key_cmp(key, node->key) == 0){
            if(pred == NULL)
                ht->slots[hash].head = node->next;
            else    
                pred->next = node->next;

            if(destroy_data){
                free(node->key);
                free(node->value);
            }
            free(node);
            ht->size-=1;
        }
    }
}

/**** END of EXERCISE #2 ****/
