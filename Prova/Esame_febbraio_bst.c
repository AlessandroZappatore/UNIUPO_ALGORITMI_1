#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the BST
typedef struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Helper function to find the node containing key k
TreeNode* findNode(TreeNode* root, int k) {
    if (root == NULL || root->key == k)
        return root;
    if (k < root->key)
        return findNode(root->left, k);
    else
        return findNode(root->right, k);
}

// Helper function to perform in-order traversal and find the n-th smallest element
TreeNode* inOrderTraversal(TreeNode* root, int* n) {
    if (root == NULL)
        return NULL;

    // Search in left subtree
    TreeNode* left = inOrderTraversal(root->left, n);
    if (left != NULL)
        return left;

    // Visit the current node
    (*n)--;
    if (*n == 0)
        return root;

    // Search in right subtree
    return inOrderTraversal(root->right, n);
}

// Main function to find the n-th smallest key in the subtree rooted at k
int findNthSmallest(TreeNode* root, int k, int n) {
    // Find the node containing key k
    TreeNode* node = findNode(root, k);
    if (node == NULL)
        return -1; // k not found in BST

    // Perform in-order traversal to find the n-th smallest element
    TreeNode* result = inOrderTraversal(node, &n);
    if (result == NULL)
        return -1; // n-th smallest element does not exist

    return result->key;
}

// Example usage
int main() {
    // Constructing the BST shown in the image
    TreeNode node1 = {1, NULL, NULL};
    TreeNode node4 = {4, NULL, NULL};
    TreeNode node7 = {7, NULL, NULL};
    TreeNode node13 = {13, NULL, NULL};
    TreeNode node6 = {6, &node4, &node7};
    TreeNode node3 = {3, &node1, &node6};
    TreeNode node14 = {14, NULL, NULL};
    TreeNode node10 = {10, &node13, &node14};
    TreeNode node8 = {8, &node3, &node10};

    TreeNode* root = &node8;

    // Example cases
    printf("2nd smallest in subtree rooted at 6: %d\n", findNthSmallest(root, 6, 2)); // Output: 6
    printf("2nd smallest in subtree rooted at 8: %d\n", findNthSmallest(root, 8, 2)); // Output: 3
    printf("4th smallest in subtree rooted at 14: %d\n", findNthSmallest(root, 14, 4)); // Output: -1
    printf("3rd smallest in subtree rooted at 6: %d\n", findNthSmallest(root, 6, 3)); // Output: -1
    printf("3rd smallest in subtree rooted at 17: %d\n", findNthSmallest(root, 17, 3)); // Output: -1

    return 0;
}
