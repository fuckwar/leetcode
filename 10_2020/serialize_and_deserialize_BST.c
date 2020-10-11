/*
Serialization is converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You need to ensure that a binary search tree can be serialized to a string, and this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

 

Example 1:

Input: root = [2,1,3]
Output: [2,1,3]

Example 2:

Input: root = []
Output: []

 

Constraints:

    The number of nodes in the tree is in the range [0, 10^4].
    0 <= Node.val <= 10^4
    The input tree is guaranteed to be a binary search tree.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void preorder(struct TreeNode* node, int* nvals, int* size){
    if(node){
        nvals[(*size)++] = node->val;
        preorder(node->left, nvals, size);
        preorder(node->right, nvals, size);
    }
}

/** Encodes a tree to a single string. */
char* serialize(struct TreeNode* root) {
    if(!root) return '\0';

    int *nvals = (int *)malloc(10000 * 4), size=0;
    preorder(root, nvals, &size);

    char *str = (char *)malloc(size * 6);
    int strlen = 0;
    printf("size=%d\n", size);
    for(int i=0; i< size; i++){
        strlen += sprintf(str+strlen, "%d,", nvals[i]);
    }
    free(nvals);
    str[strlen] = '\0';
    return str;
}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data) {
    printf("ddddd:%s\n", data);
    if(!data) return NULL;

    struct TreeNode *root=NULL, *parent=NULL, *tmp=NULL;
    char sval[6], c;
    int i=0, j=0, val=0;
    printf("i=%d,j=%d,val=%d\n", i, j, val);
    while((c = data[i++]) != '\0'){
        printf("c=%c\n", c);
        if(c != ','){
            sval[j++] = c;
        }else{
            sval[j] = '\0';
            val = atoi(sval);
            printf("atoi=%d\n", val);
            j = 0;
            struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
            node->val = val;
            node->left = NULL;
            node->right = NULL;
            if(root == NULL){
                root = node;
                parent = node;
                printf("root\n");
                continue;
            }
            printf("parent=%d\n", parent->val);
            if(val < parent->val){
                parent->left = node; 
                parent = node;
                printf("left\n");
                continue;
            }

            tmp = root;
            while(tmp != NULL){
                if(val < tmp->val){
                    tmp = tmp->left;
                }else if(tmp->right != NULL){
                    tmp = tmp->right;
                }else{
                    tmp->right = node;
                    printf("right,parent=%d\n", tmp->val);
                    break;
                }
            } 
            parent = node;
        }
        
    }
    return root;
}

// Your functions will be called as such:
// char* data = serialize(root);
// deserialize(data);

int main(){

    char data[] = "8,4,2,1,6,7,12,13,"; 
    struct TreeNode* root = deserialize(data);
    char *pdata = serialize(root);
    printf("pdata=%s\n", pdata);
/*
    struct TreeNode root = {8}, left = {4}, right = {12};
    root.left = &left;
    root.right = &right;
    char *pdata = serialize(&root);
    printf("char=%s\n", pdata);
*/
    free(pdata);

}
