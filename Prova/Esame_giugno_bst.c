#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

int sumValuesInRange(TreeNode* root, int low, int high);
size_t upo_bst_rank(TreeNode* root, int key);
void upo_bst_rank_impl(TreeNode* node, int key, size_t *result);
size_t upo_bst_predecessor(TreeNode* root, const int key);
TreeNode* upo_bst_predecessor_impl(TreeNode* node, const int key);
int upo_bst_get_value_depth(TreeNode* node, int key, int depth);
void upo_bst_keys_leq_impl(TreeNode* node, int key, int** result, int* size, int* capacity);
int* upo_bst_keys_leq(TreeNode* root, int key, int* resultSize) ;
TreeNode* findNode(TreeNode* node, const int key);
size_t upo_bst_subtree_count_leaves_depth_impl(TreeNode* node, size_t d);
size_t upo_bst_subtree_count_leaves_depth(TreeNode* root, const int key, size_t d);

// Example usage
int main() {
    // Constructing a sample BST
    TreeNode node1 = {1, 10, NULL, NULL};
    TreeNode node4 = {4, 20, NULL, NULL};
    TreeNode node7 = {7, 30, NULL, NULL};
    TreeNode node13 = {13, 40, NULL, NULL};
    TreeNode node6 = {6, 50, &node4, &node7};
    TreeNode node3 = {3, 60, &node1, &node6};
    TreeNode node14 = {14, 70, &node13, NULL};
    TreeNode node10 = {10, 80, NULL, &node14};
    TreeNode node8 = {8, 90, &node3, &node10};

    TreeNode* root = &node8;

    // Example case
    int low = 4, high = 10;
    int sum = sumValuesInRange(root, low, high);
    printf("Sum of values in range [%d, %d]: %d\n", low, high, sum); // Output should be the sum of values 20, 30, 50, 90, 80

    printf("Rango di %d = %d\n", 8, upo_bst_rank(root, 8));
    printf("Rango di %d = %d\n", 1, upo_bst_rank(root, 1));
    printf("Rango di %d = %d\n", 13, upo_bst_rank(root, 13));
    printf("Rango di %d = %d\n", 14, upo_bst_rank(root, 14));
    printf("Rango di %d = %d\n", 0, upo_bst_rank(root, 0));
    printf("Rango di %d = %d\n", 5, upo_bst_rank(root, 5));
    printf("Rango di %d = %d\n", 12, upo_bst_rank(root, 12));
    printf("Rango di %d = %d\n\n", 100, upo_bst_rank(root, 100));

    printf("Predessore di %d = %d\n", 8, upo_bst_predecessor(root, 8));
    printf("Predessore di %d = %d\n", 1, upo_bst_predecessor(root, 1));
    printf("Predessore di %d = %d\n", 13, upo_bst_predecessor(root, 13));
    printf("Predessore di %d = %d\n", 12, upo_bst_predecessor(root, 12));
    printf("Predessore di %d = %d\n", 0, upo_bst_predecessor(root, 0));
    printf("Predessore di %d = %d\n\n", 100, upo_bst_predecessor(root, 100));

    printf("Profondita' di %d = %d\n", 8, upo_bst_get_value_depth(root, 8, 0));
    printf("Profondita' di %d = %d\n", 1, upo_bst_get_value_depth(root, 1, 0));
    printf("Profondita' di %d = %d\n", 13, upo_bst_get_value_depth(root, 13, 0));
    printf("Profondita' di %d = %d\n", 12, upo_bst_get_value_depth(root, 12, 0));
    printf("Profondita' di %d = %d\n", 0, upo_bst_get_value_depth(root, 0, 0));
    printf("Profondita' di %d = %d\n\n", 100, upo_bst_get_value_depth(root, 100, 0));

    printf("Numero di foglie del sotto-albero radicato in 8 e a profondità 1: %zu\n", upo_bst_subtree_count_leaves_depth(root, 8, 1));
    printf("Numero di foglie del sotto-albero radicato in 8 e a profondità 2: %zu\n", upo_bst_subtree_count_leaves_depth(root, 8, 2));
    printf("Numero di foglie del sotto-albero radicato in 1 e a profondità 1: %zu\n", upo_bst_subtree_count_leaves_depth(root, 1, 1));
    printf("Numero di foglie del sotto-albero radicato in 1 e a profondità 2: %zu\n", upo_bst_subtree_count_leaves_depth(root, 1, 2));
    printf("Numero di foglie del sotto-albero radicato in 3 e a profondità 0: %zu\n", upo_bst_subtree_count_leaves_depth(root, 3, 0));
    printf("Numero di foglie del sotto-albero radicato in 3 e a profondità 1: %zu\n", upo_bst_subtree_count_leaves_depth(root, 3, 1));
    printf("Numero di foglie del sotto-albero radicato in 3 e a profondità 2: %zu\n", upo_bst_subtree_count_leaves_depth(root, 3, 2));
    printf("Numero di foglie del sotto-albero radicato in 1 e a profondità 0: %zu\n", upo_bst_subtree_count_leaves_depth(root, 1, 0));
    printf("Numero di foglie del sotto-albero radicato in 10 e a profondità 4: %zu\n", upo_bst_subtree_count_leaves_depth(root, 10, 4));
    printf("Numero di foglie del sotto-albero radicato in 20 e a profondità 3: %zu\n\n", upo_bst_subtree_count_leaves_depth(root, 20, 3));


    int k = 0;
    int resultSize;
    int* keys = upo_bst_keys_leq(root, k, &resultSize);

    printf("Chiavi ≤ %d: [", k);
    for (int i = 0; i < resultSize; i++) {
        printf("%d", keys[i]);
        if (i < resultSize - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    
    free(keys);
    return 0;
}

int sumValuesInRange(TreeNode* root, int low, int high) {
    if (root == NULL) {
        return 0;
    }

    int sum = 0;

    if (root->key >= low && root->key <= high) {
        sum += root->value;
    }

    if (root->key > low) {
        sum += sumValuesInRange(root->left, low, high);
    }

    if (root->key < high) {
        sum += sumValuesInRange(root->right, low, high);
    }

    return sum;
}

void upo_bst_rank_impl(TreeNode* node, int key, size_t *result) {
    if (node == NULL)
        return;

    upo_bst_rank_impl(node->left, key, result);

    if (node->key < key)
        (*result)++;

    upo_bst_rank_impl(node->right, key, result);
}

size_t upo_bst_rank(TreeNode* root, int key) {
    if (root == NULL)
        return 0;

    size_t result = 0;
    upo_bst_rank_impl(root, key, &result);
    return result;
}

size_t upo_bst_predecessor(TreeNode* root, const int key){
    if(root != NULL) {
        TreeNode* copy = root;
        TreeNode* result = upo_bst_predecessor_impl(copy, key);
        if(result == NULL) return -1;
        else return result->key;
    } 
    return -1;
}

TreeNode* upo_bst_predecessor_impl(TreeNode* node, const int key){
    if(node != NULL){
        if(node->key-key>=0) return upo_bst_predecessor_impl(node->left, key);
        TreeNode* pred = upo_bst_predecessor_impl(node->right, key);
        if(pred == NULL) return node;
        else return pred;
    }
    return NULL;
}

int upo_bst_get_value_depth(TreeNode* node, int key, int depth) {
    if (node == NULL) return -1;
    if (key == node->key) return depth;
    else if (key < node->key)
        return upo_bst_get_value_depth(node->left, key, depth + 1);
    else
        return upo_bst_get_value_depth(node->right, key, depth + 1);
}

void upo_bst_keys_leq_impl(TreeNode* node, int key, int** result, int* size, int* capacity) {
    if (node == NULL) {
        return;
    }

    // Visit left subtree
    upo_bst_keys_leq_impl(node->left, key, result, size, capacity);

    // Process current node
    if (node->key <= key) {
        if (*size >= *capacity) {
            *capacity *= 2;
            *result = realloc(*result, *capacity * sizeof(int));
        }
        (*result)[*size] = node->key;
        (*size)++;
    } else {
        return; // No need to visit the right subtree if the current key is greater than k
    }

    // Visit right subtree
    upo_bst_keys_leq_impl(node->right, key, result, size, capacity);
}

int* upo_bst_keys_leq(TreeNode* root, int key, int* resultSize) {
    int capacity = 10;
    int* result = (int*)malloc(capacity * sizeof(int));
    *resultSize = 0;
    upo_bst_keys_leq_impl(root, key, &result, resultSize, &capacity);
    return result;
}

size_t upo_bst_subtree_count_leaves_depth(TreeNode* root, const int key, size_t d) {
    if (root != NULL) {
        TreeNode* node = findNode(root, key);
        if (node != NULL)
            return upo_bst_subtree_count_leaves_depth_impl(node, d);
        else 
            return 0;
    }
    return 0;
}

size_t upo_bst_subtree_count_leaves_depth_impl(TreeNode* node, size_t d) {
    if (node == NULL) return 0;
    if (d == 0) return (node->left == NULL && node->right == NULL) ? 1 : 0;
    
    return upo_bst_subtree_count_leaves_depth_impl(node->left, d - 1) +
           upo_bst_subtree_count_leaves_depth_impl(node->right, d - 1);
}

TreeNode* findNode(TreeNode* node, const int key) {
    if (node != NULL) {
        if (node->key == key) return node;
        else if (node->key > key) return findNode(node->left, key);
        else return findNode(node->right, key);
    }
    return NULL;
}