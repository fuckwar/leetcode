/*
All DNA is composed of a series of nucleotides abbreviated as 'A', 'C', 'G', and 'T', for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA.

Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule.

 

Example 1:

Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
Output: ["AAAAACCCCC","CCCCCAAAAA"]

Example 2:

Input: s = "AAAAAAAAAAAAA"
Output: ["AAAAAAAAAA"]

 

Constraints:

    0 <= s.length <= 105
    s[i] is 'A', 'C', 'G', or 'T'.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SEQLEN 10

struct RepeatableTree{
    int val;
    int repeat;
    struct RepeatableTree *left;
    struct RepeatableTree *right;
};

int ctoi(char c){
    switch(c){
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        default: break;
    }
    return -1;
}

char itoc(int n){
    switch(n){
        case 0: return 'A';
        case 1: return 'C';
        case 2: return 'G';
        case 3: return 'T';
        default: break;
    }
    return 'F';
}

char * itostr(int num){
    char *seq = (char *)malloc(sizeof(char) * (SEQLEN+1));
    for(int i=0; i<SEQLEN; i++){
        seq[i] = itoc( (num >> i*2) & 0b11 );
    }
    seq[SEQLEN] = '\0';
    return seq;
}

int insertNode(struct RepeatableTree* head, int val){
    struct RepeatableTree *prev, *tmp = head;
    while(tmp){
        if(val == tmp->val){
            printf("repeat num=%d\n", val);
            return ++(tmp->repeat);
        }
        prev = tmp;
        if(val < tmp->val){
            tmp = tmp->left;
        }else{
            tmp = tmp->right;
        }
    } 

    struct RepeatableTree *node = (struct RepeatableTree *)malloc(sizeof(struct RepeatableTree));
    node->val = val;
    node->repeat = 0;
    node->left = NULL;
    node->right = NULL;
    if(val < prev->val){
        prev->left = node;
    }else{
        prev->right = node;
    }
    return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** findRepeatedDnaSequences(char * s, int* returnSize){
    *returnSize = 0;
    int len = strlen(s);
    if(len <= SEQLEN){
        return NULL;
    }

    char ** repeatSeqs = (char **) malloc(sizeof(char *) * 128);

/*  //use binary search tree
    struct RepeatableTree *head = (struct RepeatableTree *) malloc(sizeof(struct RepeatableTree));
    head->left = NULL;
    head->right = NULL;

    int tmpnum = 0;
    for(int i=0; i<SEQLEN; i++){
        tmpnum |= ctoi(s[i]) << i*2;
    }
    
    head->val = tmpnum;
    head->repeat = 0;

    for(int i=SEQLEN; i<len; i++){
        tmpnum = tmpnum >> 2;
        tmpnum |= ctoi(s[i]) << (2*SEQLEN-2);
        if(insertNode(head, tmpnum) == 1){
           repeatSeqs[(*returnSize)++] = itostr(tmpnum); 
        }
    }
*/
    // use array. len = 2^20
    int *iarr = (int *) calloc(1024 * 1024, sizeof(int));
    
    int tmpnum = 0;
    for(int i=0; i<SEQLEN; i++){
        tmpnum |= ctoi(s[i]) << i*2;
    }
    iarr[tmpnum]++;
    printf("%d\n", tmpnum);

    for(int i=SEQLEN; i<len; i++){
        tmpnum = tmpnum >> 2;
        tmpnum |= ctoi(s[i]) << (2*SEQLEN-2);
        printf("%d\n", tmpnum);
        if(iarr[tmpnum]++ == 1){
            repeatSeqs[(*returnSize)++] = itostr(tmpnum); 
        }
    }
    free(iarr);
    return repeatSeqs;
}

int main(){
    char s[] = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
//    char s[] = "AAAAAAAAAAA";
    int returnSize = 0; 
    char **ret = findRepeatedDnaSequences(s, &returnSize);    
    printf("[");        
    for(int i=0; i<returnSize; i++){
        printf("%s,", ret[i]);        
    }
    printf("]\n");        
}
