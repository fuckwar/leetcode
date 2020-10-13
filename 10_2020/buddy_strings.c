/*
Given two strings A and B of lowercase letters, return true if you can swap two letters in A so the result is equal to B, otherwise, return false.

Swapping letters is defined as taking two indices i and j (0-indexed) such that i != j and swapping the characters at A[i] and A[j]. For example, swapping at indices 0 and 2 in "abcd" results in "cbad".

 

Example 1:

Input: A = "ab", B = "ba"
Output: true
Explanation: You can swap A[0] = 'a' and A[1] = 'b' to get "ba", which is equal to B.

Example 2:

Input: A = "ab", B = "ab"
Output: false
Explanation: The only letters you can swap are A[0] = 'a' and A[1] = 'b', which results in "ba" != B.

Example 3:

Input: A = "aa", B = "aa"
Output: true
Explanation: You can swap A[0] = 'a' and A[1] = 'a' to get "aa", which is equal to B.

Example 4:

Input: A = "aaaaaaabc", B = "aaaaaaacb"
Output: true

Example 5:

Input: A = "", B = "aa"
Output: false

 

Constraints:

    0 <= A.length <= 20000
    0 <= B.length <= 20000
    A and B consist of lowercase letters.


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


bool buddyStrings(char * A, char * B){
    int alen = strlen(A), blen = strlen(B);
    if(alen != blen) return false;
    
    int diffCnt = 0, lettersCnt[26] = {0};
    char diff[2] = {'\0'};
    
    for(int i=0; i<alen; i++){
        if(A[i] != B[i]){
            if(diffCnt > 2){
                return false;
            }
            if(diffCnt == 0){
                diff[0] = A[i];
                diff[1] = B[i];
            }else if(diff[0] != B[i] || diff[1] != A[i]) {
                return false;
            }
            diffCnt++;
        }else{
            lettersCnt[A[i]-'a']++;
        }
    }
    if(diffCnt == 0){
        for(int i=0; i<26; i++){
            if(lettersCnt[i] >= 2){
                return true;
            }
        }
        return false;
    }else{
        return diffCnt == 2;
    }
}

int main(){
//    char A[] = "aa", B[] = "aa";
//    char A[] = "ab", B[] = "ab";
    char A[] = "aaaaaaabc", B[] = "aaaaaaacb";
    bool ret = buddyStrings(A, B);
    printf("ret=%d\n", ret);
}
