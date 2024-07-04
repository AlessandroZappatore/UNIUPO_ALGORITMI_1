/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file sort_private.h
 *
 * \brief Private header for sorting algorithms.
 *
 * \author Your Name
 *
 * \copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 *  This file is part of UPOalglib.
 *
 *  UPOalglib is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  UPOalglib is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UPO_SORT_PRIVATE_H
#define UPO_SORT_PRIVATE_H

#include <upo/sort.h>
#include <stdlib.h>
#include <string.h>


/* TO STUDENTS:
 *
 *  This file is currently "empty".
 *  Here you can put the prototypes of auxiliary "private" functions that are
 *  internally used by "public" functions.
 *  For instance, you can declare the prototype of the function that performs
 *  the "merge" operation in the merge-sort algorithm:
 *    static void upo_merge_sort_merge(void *base, size_t lo, size_t mid, size_t hi, size_t size, upo_sort_comparator_t cmp);
 *  Also, you can declare the prototype of the function that performs the
 *  the recursion in the merge-sort algorithm:
 *    static void upo_merge_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp);
 *  Further, you can declare the prototype of the function that performs the
 *  "partition" operation in the quick-sort algorithm:
 *    static size_t upo_quick_sort_partition(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp);
 *  And so on.
 *
 */
void upo_swap(void *a, void *b, size_t size)
{
    // BEGIN of Alternative #1

    unsigned char *aa = a;
    unsigned char *bb = b;
    size_t i;

    assert( a );
    assert( b );

    if (a == b)
    {
        /* Nothing to swap */
        return;
    }

    for (i = 0; i < size; ++i)
    {
        unsigned char tmp = *aa;
        *aa = *bb;
        *bb = tmp;
        ++aa;
        ++bb;
    }
}

void upo_merge(void *base, size_t lo, size_t mid, size_t hi, size_t size,upo_sort_comparator_t cmp)
{
    unsigned char *ptr=base;
    unsigned char *aux=NULL;
    size_t i=0, j=mid+1-lo, k, n=hi-lo+1;
    aux=malloc(n*size);
    if(aux!=NULL)
    {
        memcpy(aux, ptr+lo*size, n*size);

        for (k = lo; k <= hi; ++k)
        {
            if (i > (mid-lo))
            {
            memcpy(ptr+k*size, aux+j*size, size);
            ++j;
            }
                else if (j > (hi-lo))
                {
                memcpy(ptr+k*size, aux+i*size, size);
                ++i;
                }
                    else if (cmp(aux+j*size, aux+i*size) < 0)
                    {
                    memcpy(ptr+k*size, aux+j*size, size);
                    ++j;
                    }
                        else
                        {
                        memcpy(ptr+k*size, aux+i*size, size);
                        ++i;
                        }
            }
            free(aux);
    }
}

void upo_merge_sort_rec(void *base, size_t lo, size_t hi, size_t size,upo_sort_comparator_t cmp)
{
    if(lo>=hi) return;
    size_t mid=(lo+hi)/2;
    upo_merge_sort_rec(base, lo, mid, size, cmp);
    upo_merge_sort_rec(base, mid+1, hi,size, cmp);
    upo_merge(base, lo, mid, hi, size, cmp);
}

size_t upo_quick_sort_partition(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    size_t p = lo, i = lo, j = hi + 1;
    unsigned char *ptr = base;

    while (1)
    {
        do
        {
            i += 1;
        } while (i <= hi && cmp(ptr + i * size, ptr + p * size) < 0);

        do
        {
            j -= 1;
        } while (j >= lo && cmp(ptr + j * size, ptr + p * size) > 0);

        if (i >= j)
        {
            break;
        }

        upo_swap(ptr + i * size, ptr + j * size, size);
    }

    upo_swap(ptr + p * size, ptr + j * size, size);
    return j;
}

void upo_quick_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp)
{
    if (lo >= hi) return;

    size_t j = upo_quick_sort_partition(base, lo, hi, size, cmp);
    if (j > 0)
    {
        upo_quick_sort_rec(base, lo, j - 1, size, cmp);
    }
    upo_quick_sort_rec(base, j + 1, hi, size, cmp);
}



#endif /* UPO_SORT_PRIVATE_H */
