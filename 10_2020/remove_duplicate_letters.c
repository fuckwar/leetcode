/*
Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Note: This question is the same as 1081: https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/

 

Example 1:

Input: s = "bcabc"
Output: "abc"

Example 2:

Input: s = "cbacdcbc"
Output: "acdb"


Constraints:

    1 <= s.length <= 10^4
    s consists of lowercase English letters.


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct IdxBorder {
    int min;
    int max;   
};

char * removeDuplicateLetters(char * s){
    if(!s || s[0] == '\0') return '\0';
    //build letters's index border
    struct IdxBorder *letters[26] = {NULL};
    struct IdxBorder *tmp = NULL;
    char c;
    int scan=0;
    int totalLetters = 0;
    while((c = s[scan]) != '\0'){
        printf("c=%c\n", c);
        tmp = letters[c % 'a'];
        if(!tmp){
            printf("new ib for %c\n", c);
            tmp = (struct IdxBorder *)malloc(sizeof(struct IdxBorder));
            tmp->min = -1;
            tmp->max = -1;
            letters[c % 'a'] = tmp;
            totalLetters++;
        }
        if(tmp->min == -1){
            tmp->min = scan;
        }
        tmp->max = scan;
        scan++;
    }

    printf("totalLetters=%d\n", totalLetters);
    //select in lexicographical order
    char *ret = malloc((totalLetters+1) * sizeof(char));
    int begin = 0;
    for(int i=0; i<totalLetters; i++){
        for(int j=0; j<26; j++){
            if(!letters[j]){
               continue; 
            }
            c = 'a' + j;
            tmp = letters[j];
            printf("check %c,min=%d,max=%d\n", c, tmp->min, tmp->max);
            if(tmp->min < begin){
                //rebuild min border
                for(scan=begin+1; scan<=tmp->max; scan++){
                    if(s[scan] == c){
                        printf("get %c\n", c);
                        tmp->min = scan;
                        break;
                    }
                }
            }

            int isOrder = 1;
            for(int k=0; k<26; k++){
                if(letters[k] && tmp->min > letters[k]->max){
                    isOrder = 0;
                    break;
                }        
            }
            if(isOrder){
                begin = tmp->min;
                ret[i] = c; 
                letters[j] = NULL;
                free(tmp);
                break;
            }
        } 
    }
    ret[totalLetters] = '\0';
    return ret;
}

int main(){
    char letters[] = "cbacdcbc";
    //char letters[] = "bcabc";
    char *ret = removeDuplicateLetters(letters);
    printf("ret=%s\n", ret);
}
