/*
Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

 

Example 1:

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.

Example 2:

Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]

Example 3:

Input: candidates = [2], target = 1
Output: []

Example 4:

Input: candidates = [1], target = 1
Output: [[1]]

Example 5:

Input: candidates = [1], target = 2
Output: [[1,1]]

Constraints:

    1 <= candidates.length <= 30
    1 <= candidates[i] <= 200
    All elements of candidates are distinct.
    1 <= target <= 500

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int cmp(const void *a, const void *b){
    return *(int *)a > *(int *)b;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes){
    qsort(candidates, candidatesSize, sizeof(int), cmp);
    int **ret = (int **)malloc(256 * sizeof(int *));
    int *columnSizes = (int *)malloc(256 * sizeof(int));
    int *comIdx = (int *)malloc((target / candidates[0] + 1) * sizeof(int));
    comIdx[0] = 0;

    int pos = 0, posCopy=-1, retIdx=0,  idx, x, y = target;
    while(pos >= 0){
        idx = comIdx[pos];
        if(pos <= posCopy){
            y += candidates[idx++];
        }
        posCopy = pos;
        if(idx >= candidatesSize){
            pos--;
            continue;
        } 
        
        x = candidates[idx];
        if(y == x){
            printf("y x %d\n", y);
            comIdx[pos] = idx;
            int *members = (int *)malloc((pos+1) * sizeof(int));
            for(int i=0; i <= pos; i++){
                members[i] = candidates[comIdx[i]];
            }
            ret[retIdx] = members;
            columnSizes[retIdx] = pos + 1;
            retIdx++;

            pos--;
        }else if(y > x){
            y -= x;
            comIdx[pos] = idx;
            comIdx[++pos] = idx;
        }else{
            pos--;
        }
    }
    *returnSize = retIdx;
    returnColumnSizes[0] = columnSizes; 
    return ret;
}

int main(){
    int candidates[] = {2, 3, 6, 7, 1};
    int target = 7;

//    int candidates[] = {2, 3, 5};
//    int target = 8;

//    int candidates[] = {2};
//    int target = 1;

//    int candidates[] = {1};
//    int target = 2;

    int **returnColumnSizes = (int **)malloc(sizeof(int *));
    int returnSize;
    int ** ret = combinationSum(candidates, sizeof(candidates)/sizeof(candidates[0]), target, &returnSize, returnColumnSizes);
    printf("returnSize=%d\n", returnSize);
    if(returnSize){
        printf("[");
        for(int i=0; i < returnSize; i++){
            printf("[");
            for(int j=0; j < returnColumnSizes[0][i]; j++){
                printf("%d,", ret[i][j]);
            }
            printf("],");
        }
        printf("]\n");
    }
}
