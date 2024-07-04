/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "bst_private.h"
#include <stdio.h>
#include <stdlib.h>


/**** EXERCISE #1 - BEGIN of FUNDAMENTAL OPERATIONS ****/


upo_bst_t upo_bst_create(upo_bst_comparator_t key_cmp)
{
    upo_bst_t tree = malloc(sizeof(struct upo_bst_s));
    if (tree == NULL)
    {
        perror("Unable to create a binary search tree");
        abort();
    }

    tree->root = NULL;
    tree->key_cmp = key_cmp;

    return tree;
}

upo_bst_node_t* upo_bst_node_create(void* key, void* value)
{
    upo_bst_node_t *node=(upo_bst_node_t*) malloc(sizeof(upo_bst_node_t));
    if(node!=NULL)
    {
        
        node->right=node->left=NULL;
        node->key=key;
        node->value=value;
    }
    return node;
}

void upo_bst_destroy(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear(tree, destroy_data);
        free(tree);
    }
}

void upo_bst_clear_impl(upo_bst_node_t *node, int destroy_data)
{
    if (node != NULL)
    {
        upo_bst_clear_impl(node->left, destroy_data);
        upo_bst_clear_impl(node->right, destroy_data);

        if (destroy_data)
        {
            free(node->key);
            free(node->value);
        }

        free(node);
    }
}

void upo_bst_clear(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear_impl(tree->root, destroy_data);
        tree->root = NULL;
    }
}

void* upo_bst_put(upo_bst_t tree, void *key, void *value)
{
    if(tree!=NULL)
    {
        void *old_value=NULL;
        tree->root=upo_bst_put_impl(tree->root, key, value, old_value, tree->key_cmp);
        return old_value;
    }
    return NULL;
}

upo_bst_node_t *upo_bst_put_impl(upo_bst_node_t *node, void *key, void *value, void *old_value, upo_bst_comparator_t key_cmp)
{
    old_value=NULL;
    if(node==NULL) return upo_bst_node_create(key, value);
    else if(key_cmp(key, node->key)<0) node->left=upo_bst_put_impl(node->left, key, value, old_value, key_cmp);
    else if(key_cmp(key, node->key)>0) node->right=upo_bst_put_impl(node->right, key, value, old_value, key_cmp);
    else 
    {
        old_value=node->value;
        node->value=value;
    }
    return node;
}

void upo_bst_insert(upo_bst_t tree, void *key, void *value)
{
    if(tree!=NULL)
        tree->root=upo_bst_insert_impl(tree->root, key, value, tree->key_cmp);
}

upo_bst_node_t* upo_bst_insert_impl(upo_bst_node_t* node, void *key, void *value, upo_bst_comparator_t key_cmp)
{
    if(node==NULL) return upo_bst_node_create(key, value);
    else if(key_cmp(key, node->key)<0) node->left=upo_bst_insert_impl(node->left, key, value, key_cmp);
    else if(key_cmp(key, node->key)>0) node->right=upo_bst_insert_impl(node->right, key, value, key_cmp);
    return node;
}


void* upo_bst_get(const upo_bst_t tree, const void *key)
{
    if(tree!=NULL)
    {
        upo_bst_node_t *node=upo_bst_get_impl(tree->root, key, tree->key_cmp);
        if(node!=NULL) return node->value;
        else return NULL;
    }
    return NULL;
}

upo_bst_node_t* upo_bst_get_impl(upo_bst_node_t* node,const void *key, upo_bst_comparator_t key_cmp)
{
    if(node==NULL) return NULL;
    if(key_cmp(key, node->key)<0) return upo_bst_get_impl(node->left, key, key_cmp);
    else if(key_cmp(key, node->key)>0) return upo_bst_get_impl(node->right, key, key_cmp);
    else return node;
}

int upo_bst_contains(const upo_bst_t tree, const void *key)
{
    if(tree!=NULL)
    {
        if(upo_bst_get_impl(tree->root, key, tree->key_cmp)!=NULL) return 1;
        else return 0;
    }
    return 0;
}

void upo_bst_delete(upo_bst_t tree, const void *key, int destroy_data)
{
    if(tree!=NULL)
        tree->root=upo_bst_delete_impl(tree->root, key, tree->key_cmp, destroy_data);
}

upo_bst_node_t* upo_bst_delete_impl(upo_bst_node_t* node, const void *key, upo_bst_comparator_t key_cmp, int destroy_data)
{
    if(node==NULL) return NULL;
    if(key_cmp(key, node->key)<0) node->left=upo_bst_delete_impl(node->left, key, key_cmp, destroy_data);
    else if(key_cmp(key, node->key)>0) node->right=upo_bst_delete_impl(node->right, key, key_cmp, destroy_data);
    else if(node->left!=NULL && node->right!=NULL) node=upo_bst_delete_2Cl_impl(node, key_cmp, destroy_data);
    else node=upo_bst_delete_1Cl_impl(node, destroy_data);
    return node;
}

upo_bst_node_t* upo_bst_delete_1Cl_impl(upo_bst_node_t* node, int destroy_data)
{
    upo_bst_node_t* tmp=node;
    if(node->left!=NULL) node=node->left;
    else node=node->right;
    if(destroy_data)
    {
        free(tmp->key);
        free(tmp->value);
    }
    free(tmp);
    return node;
}

upo_bst_node_t* upo_bst_delete_2Cl_impl(upo_bst_node_t* node, upo_bst_comparator_t key_cmp, int destroy_data)
{
    upo_bst_node_t* max=upo_bst_max_impl(node->left);
    if(destroy_data)
    {
        free(node->key);
        free(node->value);
    }
    node->key=max->key;
    node->value=max->value;
    node->left=upo_bst_delete_impl(node->left, max->key, key_cmp, 0);
    return node;
}

upo_bst_node_t* upo_bst_max_impl(upo_bst_node_t* node)
{
    if(node==NULL) return NULL;
    else if(node->right!=NULL) return upo_bst_max_impl(node->right);
    else return node;
}

size_t upo_bst_size(const upo_bst_t tree)
{
    if(tree!=NULL)
        return upo_bst_size_impl(tree->root);
    return 0;
}

size_t upo_bst_size_impl(upo_bst_node_t* node)
{
    if(node==NULL) return 0;
    return 1+upo_bst_size_impl(node->left)+upo_bst_size_impl(node->right);
}

size_t upo_bst_height(const upo_bst_t tree)
{
    if(tree!=NULL)
        return upo_bst_height_impl(tree->root);
    return 0;
}

size_t upo_bst_height_impl(upo_bst_node_t* node)
{
    if(node==NULL || upo_bst_is_leaf_impl(node)) return 0;
    return 1+upo_bst_max_height(upo_bst_height_impl(node->right), upo_bst_height_impl(node->left));
}

int upo_bst_is_leaf_impl(upo_bst_node_t* node)
{
    if(node->left==NULL && node->right==NULL) return 1;
    else return 0;
}

size_t upo_bst_max_height(size_t right, size_t left)
{
    if(right>=left) return right;
    else return left;
}

void upo_bst_traverse_in_order(const upo_bst_t tree, upo_bst_visitor_t visit, void *visit_context)
{
    if(tree!=NULL)
        upo_bst_traverse_in_order_impl(tree->root, visit, visit_context);
}

void upo_bst_traverse_in_order_impl(upo_bst_node_t* node, upo_bst_visitor_t visit, void *visit_context)
{
    if(node!=NULL)
    {
        upo_bst_traverse_in_order_impl(node->left, visit, visit_context);
        visit(node->key, node->value, visit_context);
        upo_bst_traverse_in_order_impl(node->right, visit, visit_context);
    }
}

int upo_bst_is_empty(const upo_bst_t tree)
{
    if(tree==NULL || tree->root==NULL) return 1;
    else return 0;
}


/**** EXERCISE #1 - END of FUNDAMENTAL OPERATIONS ****/


/**** EXERCISE #2 - BEGIN of EXTRA OPERATIONS ****/


void* upo_bst_min(const upo_bst_t tree)
{
    if(tree!=NULL)
    {
        upo_bst_node_t *node=upo_bst_min_impl(tree->root);
        if(node!=NULL) return node->key;
        else return NULL;
    }
    return NULL;
}

upo_bst_node_t* upo_bst_min_impl(upo_bst_node_t* node)
{
    if(node==NULL) return NULL;
    else if(node->left!=NULL) return upo_bst_min_impl(node->left);
    else return node;
}


void* upo_bst_max(const upo_bst_t tree)
{
    if(tree!=NULL)
    {
        upo_bst_node_t *node=upo_bst_max_impl(tree->root);
        if(node!=NULL) return node->key;
        else return NULL;
    }
    return NULL;
}

void upo_bst_delete_min(upo_bst_t tree, int destroy_data)
{
    if(tree!=NULL)
        upo_bst_delete(tree, upo_bst_min(tree), destroy_data);
}

void upo_bst_delete_max(upo_bst_t tree, int destroy_data)
{
    if(tree!=NULL)
        upo_bst_delete(tree, upo_bst_max(tree), destroy_data);
}

void* upo_bst_floor(const upo_bst_t tree, const void *key)
{
    if(tree!=NULL)
    {
        upo_bst_node_t* node=upo_bst_floor_impl(tree->root, key, tree->key_cmp);
        if(node!=NULL) return node->key;
        else return NULL;
    }
    return NULL;
}

upo_bst_node_t* upo_bst_floor_impl(upo_bst_node_t* node, const void *key, upo_bst_comparator_t key_cmp)
{
    if(node!=NULL)
    {
        if(key_cmp(key, node->key)<0) return upo_bst_floor_impl(node->left, key, key_cmp);
        else if(key_cmp(key, node->key)>0)
        {
            upo_bst_node_t* tmp=upo_bst_floor_impl(node->right, key, key_cmp);
            if(tmp!=NULL) return tmp;
            else return node;
        }
        else return node;
    }
    return NULL;
}

void* upo_bst_ceiling(const upo_bst_t tree, const void *key)
{
    if(tree!=NULL)
    {
        upo_bst_node_t* node=upo_bst_ceiling_impl(tree->root, key, tree->key_cmp);
        if(node!=NULL) return node->key;
        else return NULL;
    }
    return NULL;
}

upo_bst_node_t* upo_bst_ceiling_impl(upo_bst_node_t* node, const void *key, upo_bst_comparator_t key_cmp)
{
    if(node!=NULL)
    {
        if(key_cmp(key, node->key)>0) return upo_bst_ceiling_impl(node->right, key, key_cmp);
        else if(key_cmp(key, node->key)<0)
        {
            upo_bst_node_t* tmp=upo_bst_ceiling_impl(node->left, key, key_cmp);
            if(tmp!=NULL) return tmp;
            else return node;
        }
        else return node;
    }
    return NULL;
}

upo_bst_key_list_t upo_bst_keys_range(const upo_bst_t tree, const void *low_key, const void *high_key)
{
    if(tree!=NULL)
    {
        upo_bst_key_list_t list=NULL;
        upo_bst_keys_range_impl(tree->root, low_key, high_key, tree->key_cmp, &list);
        return list;
    }
    return NULL;
}

void upo_bst_keys_range_impl(upo_bst_node_t* node, const void *low_key, const void *high_key, upo_bst_comparator_t key_cmp, upo_bst_key_list_t *list)
{
    if(node!=NULL)
    {
        upo_bst_keys_range_impl(node->left, low_key, high_key, key_cmp, list);
        if(key_cmp(node->key, low_key)>=0 && key_cmp(node->key, high_key)<=0)
        {
            upo_bst_key_list_node_t *list_node=malloc(sizeof(upo_bst_key_list_node_t));
            if(list_node==NULL)
            {
                perror("Unable to allocate memory for a new node of the list");
                abort();
            }
            list_node->key=node->key;
            list_node->next=*list;
            *list=list_node;

            upo_bst_keys_range_impl(node->right, low_key, high_key, key_cmp, list);
        }

    }
}


upo_bst_key_list_t upo_bst_keys(const upo_bst_t tree)
{
    if(tree!=NULL)
    {
        upo_bst_key_list_t list=NULL;
        upo_bst_keys_impl(tree->root, tree->key_cmp, &list);
        return list;
    }
    return NULL;
}

void upo_bst_keys_impl(upo_bst_node_t* node, upo_bst_comparator_t key_cmp, upo_bst_key_list_t *list)
{
    if(node!=NULL)
    {
        upo_bst_keys_impl(node->left, key_cmp, list);
        upo_bst_key_list_node_t *list_node=malloc(sizeof(upo_bst_key_list_node_t));
        if(list_node==NULL)
        {
            perror("Unable to allocate memory for a new node of the list");
            abort();
        }
        list_node->key=node->key;
        list_node->next=*list;
        *list=list_node;

        upo_bst_keys_impl(node->right, key_cmp, list);
    }
}

int upo_bst_is_bst(const upo_bst_t tree, const void *min_key, const void *max_key)
{
    if(upo_bst_is_empty(tree)) return 1;
    return upo_bst_is_bst_impl(tree->root, min_key, 0, max_key, 0, tree->key_cmp);
}

int upo_bst_is_bst_impl(upo_bst_node_t* node, const void *min_key, int min_key_2, const void *max_key, int max_key_2, upo_bst_comparator_t key_cmp)
{
    if(node==NULL) return 1;

    if(key_cmp(node->key, min_key)<0 || key_cmp(node->key, max_key)>0 || (min_key_2 && key_cmp(node->key, min_key)==0) || (max_key_2 && key_cmp(node->key, max_key)==0)) return 0;
    return upo_bst_is_bst_impl(node->left, min_key, min_key_2, node->key, 1, key_cmp) && upo_bst_is_bst_impl(node->right, node->key, 1, max_key, max_key_2, key_cmp);
}


/**** EXERCISE #2 - END of EXTRA OPERATIONS ****/


upo_bst_comparator_t upo_bst_get_comparator(const upo_bst_t tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    return tree->key_cmp;
}