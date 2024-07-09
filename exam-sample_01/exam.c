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
#include <upo/sort.h>

/**** BEGIN of EXERCISE #1 ****/
const void *upo_bst_predecessor(const upo_bst_t bst, const void *key)
{
    if (bst == NULL || key == NULL) return NULL;

    return upo_bst_predecessor_impl(bst->root, key, bst->key_cmp);
    
}

void *upo_bst_predecessor_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t key_cmp)
{
    if (node == NULL) return NULL;
    
    if (key_cmp(node->key, key) >= 0)
        return upo_bst_predecessor_impl(node->left, key, key_cmp);

    void *pred = upo_bst_predecessor_impl(node->right, key, key_cmp);
    if (pred == NULL)
        return node->key;
    else
        return pred;
}

/**** END of EXERCISE #1 ****/

/**** BEGIN of EXERCISE #2 ****/
void upo_swap(void *a, void *b, size_t sz)
{
    unsigned char *aa = a;
    unsigned char *bb = b;

    while (sz-- > 0)
    {
        unsigned char tmp = *aa;
        *aa = *bb;
        *bb = tmp;
        ++aa;
        ++bb;
    }
}

void upo_bidi_bubble_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    assert(base != NULL);

    unsigned char *pc = base;
    int swapped = 1;
    for (size_t k = 0; k < n && swapped; k++)
    {
        swapped = 0;

        for (size_t i = 0; i < n - 1; i++)
        {
            if (cmp(pc + i * size, pc + (i + 1) * size) > 0)
            {
                upo_swap(pc + i * size, pc + (i + 1) * size, size);
                swapped = 1;
            }
        }
        if (swapped)
        {
            swapped = 0;

            for (size_t i = n - 2; i > 0; i--)
            {
                if (cmp(pc + i * size, pc + (i - 1) * size) < 0)
                {
                    upo_swap(pc + i * size, pc + (i - 1) * size, size);
                    swapped = 1;
                }
            }
        }
    }
}

/**** END of EXERCISE #2 ****/
