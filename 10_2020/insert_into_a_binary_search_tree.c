#include <stdio.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* insertIntoBST(struct TreeNode* root, int val){
    struct TreeNode* node = root;
    struct TreeNode* sub;
    int isLeft = 0;
    while(1){
        isLeft = val < node->val ? 1 : 0;
        sub = isLeft ? node->left : node->right;
        if(sub == NULL){
            break;
        }
        node = sub;
    } 
    struct TreeNode in;
    in.val = val;
    in.left = NULL;
    in.right = NULL;
    
    if(isLeft){
        node->left = &in;
    }else{
        node->right = &in;
    }  
    return root; 
}

int main(){
    struct TreeNode root, child;
    root.val = 10;
    root.left = &child;
    root.right = NULL;
    child.val = 8;
    child.left = NULL;
    child.right = NULL;

    struct TreeNode* result = insertIntoBST(&root, 12);
    printf("rval %d\n", result->right->val); 
    printf("lval %d\n", result->left->val); 
}
