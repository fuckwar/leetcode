/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

 

Example 1:

Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.

Example 2:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.

Example 3:

Input: nums = [0]
Output: 0

 

Constraints:

    1 <= nums.length <= 100
    0 <= nums[i] <= 1000


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define max(a, b) ((a)>(b)?(a):(b))


int rob(int* nums, int numsSize){
    if(numsSize == 1) return nums[0];
    if(numsSize == 2) return max(nums[0], nums[1]);
    
    int pa=0, pb=0, tmp;
    for(int i=0; i<numsSize-1; i++){
        tmp = pb;
        pb = max(pb, pa+nums[i]);
        pa = tmp; 
    }
    int s1 = max(pa, pb);
    pb = 0;
    pa = 0;
    for(int i=1; i<numsSize; i++){
        tmp = pb;
        pb = max(pb, pa+nums[i]);
        pa = tmp; 
    }
    int s2 = max(pa, pb);
    return max(s1, s2);
}

int main(){
    int nums[] = {200,234,182,111,87,194,221,217,71,162,140,51,81,80,232,193,223,103,139,103};
    int robSum = rob(nums, sizeof(nums)/sizeof(nums[0]));
    printf("robSum=%d\n", robSum);
}
