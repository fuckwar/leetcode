#include <stdio.h>

/*
Given a linked list, rotate the list to the right by k places, where k is non-negative.

Example 1:

Input: 1->2->3->4->5->NULL, k = 2
Output: 4->5->1->2->3->NULL
Explanation:
rotate 1 steps to the right: 5->1->2->3->4->NULL
rotate 2 steps to the right: 4->5->1->2->3->NULL

Example 2:

Input: 0->1->2->NULL, k = 4
Output: 2->0->1->NULL
Explanation:
rotate 1 steps to the right: 2->0->1->NULL
rotate 2 steps to the right: 1->2->0->NULL
rotate 3 steps to the right: 0->1->2->NULL
rotate 4 steps to the right: 2->0->1->NULL
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode{
    int val;
    struct ListNode *next;
};

struct ListNode* rotateRight(struct ListNode* head, int k){
    if(head == NULL){
        return head;
    }
    struct ListNode *tail, *tmp, *next;
    int size = 0;
    /* reverse */
    next = head;
    tail = NULL;
    while(next != NULL){
        tmp = next;
        next = next->next;
        tmp->next = tail;
        tail = tmp;
        size++;
    } 
    /* rotate */
    head->next = tail;
    for(int i=0; i<k%size; i++){
        tmp = tail;
        tail = tail->next;
        head->next = tmp;
        head = tmp;
    }
    head->next = NULL;

    printf("rotate:");
    next = tail;
    while(next != NULL){
        printf("%d->", next->val);
        next = next->next;
    }
    /* reverse */
    next = tail; 
    head = NULL;
    while(next != NULL){
        tmp = next;
        next = next->next;
        tmp->next = head;
        head = tmp;
    } 
    return head;
}

int main(){
    struct ListNode one, two, three, four, five;
    one.val = 1;
    two.val = 2;
    three.val = 3;
    one.next = &two;
    two.next = &three;
    three.next = NULL;
    
    struct ListNode *head, *next;
    head = rotateRight(&one, 2000000000);
    next = head;
    printf("result:");
    while(next != NULL){
        printf("%d->", next->val);
        next = next->next;
    }
}
