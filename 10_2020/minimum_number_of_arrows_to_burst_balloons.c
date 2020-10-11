/*

There are some spherical balloons spread in two-dimensional space. For each balloon, provided input is the start and end coordinates of the horizontal diameter. Since it's horizontal, y-coordinates don't matter, and hence the x-coordinates of start and end of the diameter suffice. The start is always smaller than the end.

An arrow can be shot up exactly vertically from different points along the x-axis. A balloon with xstart and xend bursts by an arrow shot at x if xstart ≤ x ≤ xend. There is no limit to the number of arrows that can be shot. An arrow once shot keeps traveling up infinitely.

Given an array points where points[i] = [xstart, xend], return the minimum number of arrows that must be shot to burst all balloons.

Example 1:

Input: points = [[10,16],[2,8],[1,6],[7,12]]
Output: 2
Explanation: One way is to shoot one arrow for example at x = 6 (bursting the balloons [2,8] and [1,6]) and another arrow at x = 11 (bursting the other two balloons).

Example 2:

Input: points = [[1,2],[3,4],[5,6],[7,8]]
Output: 4

Example 3:

Input: points = [[1,2],[2,3],[3,4],[4,5]]
Output: 2

Example 4:

Input: points = [[1,2]]
Output: 1

Example 5:

Input: points = [[2,3],[2,3]]
Output: 1

Constraints:

    0 <= points.length <= 10^4
    points.length == 2
    -2^31 <= xstart < xend <= 2^31 - 1

*/

#include <stdlib.h>
#include <stdio.h>

int cmp(const void *a, const void *b){
    int *aa = *(int **)a, *bb = *(int **)b;
    printf("a=[%d,%d],b=[%d,%d]\n", aa[0], aa[1], bb[0], bb[1]);
    if(aa[0] == bb[0])
        return aa[1] > bb[1];
    else
        return aa[0] > bb[0];

}

int findMinArrowShots(int** points, int pointsSize, int* pointsColSize){
    if(pointsSize <= 1) return pointsSize;
    printf("ffffffff\n");
    for(int i=0; i<pointsSize; i++){
        printf("[%d,%d],", points[i][0], points[i][1]);
    }
    printf("\n");
    qsort(points, pointsSize, sizeof(int *), cmp);

    for(int i=0; i<pointsSize; i++){
        printf("[%d,%d],", points[i][0], points[i][1]);
    }
    printf("\n");

    int cnt=1, end=points[0][1];
    for(int j=1; j<pointsSize; j++){
        printf("j=%d,js=%d,end=%d\n", j, points[j][0], end);
        if(end >= points[j][0]){
            end = end > points[j][1] ? points[j][1] : end;
        }else{
            end = points[j][1];
            cnt++;
        }
    }
    return cnt;
}

int main(){
    int points[4][2] = {{10, 16}, {2, 8}, {1, 6}, {7, 12} };
    int *p[4];
    p[0] = points[0];
    p[1] = points[1];
    p[2] = points[2];
    p[3] = points[3];
    int shots = findMinArrowShots(p, 4, NULL);
    printf("shots=%d\n", shots);
}
