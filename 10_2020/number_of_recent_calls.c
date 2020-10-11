#include <stdio.h>
#include <stdlib.h>
/*
You have a RecentCounter class which counts the number of recent requests within a certain time frame.

Implement the RecentCounter class:

    RecentCounter() Initializes the counter with zero recent requests.
    int ping(int t) Adds a new request at time t, where t represents some time in milliseconds, and returns the number of requests that has happened in the past 3000 milliseconds (including the new request). Specifically, return the number of requests that have happened in the inclusive range [t - 3000, t].

It is guaranteed that every call to ping uses a strictly larger value of t than the previous call.

 

Example 1:

Input
["RecentCounter", "ping", "ping", "ping", "ping"]
[[], [1], [100], [3001], [3002]]
Output
[null, 1, 2, 3, 3]

Explanation
RecentCounter recentCounter = new RecentCounter();
recentCounter.ping(1);     // requests = [1], range is [-2999,1], return 1
recentCounter.ping(100);   // requests = [1, 100], range is [-2900,100], return 2
recentCounter.ping(3001);  // requests = [1, 100, 3001], range is [1,3001], return 3
recentCounter.ping(3002);  // requests = [1, 100, 3001, 3002], range is [2,3002], return 3

 

Constraints:

    1 <= t <= 10^9
    Each test case will call ping with strictly increasing values of t.
    At most 104 calls will be made to ping.

*/

#define LEN 3002

typedef struct {
    int pool[LEN];
    int begin;
    int pos; 
} RecentCounter;


RecentCounter* recentCounterCreate() {
    RecentCounter* obj = (RecentCounter *) malloc(sizeof(RecentCounter));
    return obj;
}

int recentCounterPing(RecentCounter* obj, int t) {
    obj->pool[obj->pos] = t; 
    int begin=obj->begin, end=obj->pos, mid;
//    printf("=====t=%d,begin=%d,end=%d\n", t, begin, end);
    if(t - obj->pool[begin] <= 3000){
        end = begin;
    }
    while(begin != end){
        if(begin <= end)
            mid = (begin + end) / 2;
        else
            mid = (begin + end + LEN) / 2 % LEN;
       
        if(t - obj->pool[mid] > 3000){
            begin = (mid + 1) % LEN;
        }else{
            end = mid;
        }
    }
    obj->begin = begin;
    obj->pos = (obj->pos + 1) % LEN;    
    return (LEN +  obj->pos - obj->begin) % LEN;
}

void recentCounterFree(RecentCounter* obj) {
    free(obj);
    obj = NULL;        
}

/**
 * Your RecentCounter struct will be instantiated and called as such:
 * RecentCounter* obj = recentCounterCreate();
 * int param_1 = recentCounterPing(obj, t);
 
 * recentCounterFree(obj);
*/

int main(){
    RecentCounter* obj = recentCounterCreate();
    for(int i=0; i<10000; i++){
        printf("%d,", recentCounterPing(obj, i));
    }
    recentCounterFree(obj);
}
