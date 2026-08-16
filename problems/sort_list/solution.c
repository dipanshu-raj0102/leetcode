/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* sortList(struct ListNode* head) {
    struct ListNode* findMiddle(struct ListNode* head)
    {
    if (!head) return NULL;
    struct ListNode* slow = head;
    struct ListNode* fast = head -> next;
    while(fast != NULL && fast-> next != NULL)
    {
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    return slow;
    }

    struct ListNode* mergeSortedIterative(struct ListNode* L1, struct ListNode* L2) {
    struct ListNode dummy;
    struct ListNode *tail = &dummy;
    dummy.next = NULL;

    while (L1 && L2) {
        if (L1->val <= L2->val) {
            tail->next = L1;
            L1 = L1->next;
        } else {
            tail->next = L2;
            L2 = L2->next;
        }
        tail = tail->next;
    }
    tail->next = L1 ? L1 : L2;
    return dummy.next;
    }

    struct ListNode* mergeSort(struct ListNode *head)
    {
    if(!head || !head -> next) return head;
    struct ListNode *mid = findMiddle(head);
    struct ListNode *right = mid -> next;
    mid -> next = NULL;

    struct ListNode *left_sorted = mergeSort(head);
    struct ListNode *right_sorted = mergeSort(right);

    return mergeSortedIterative(left_sorted, right_sorted);
    }
    head = mergeSort(head);
    return head;
    
}