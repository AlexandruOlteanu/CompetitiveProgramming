/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* head = NULL;
        ListNode* aux = NULL;
        while (list1 != NULL || list2 != NULL) {
            if (list2 == NULL || (list1 != NULL && list1->val < list2->val)) {
                    if (head == NULL) {
                        head = list1;
                        aux = head;
                    }
                    else {
                        aux->next = list1;
                        aux = aux->next;
                    }
                    list1 = list1->next;
            }
            else {
                if (head == NULL) {
                    head = list2;
                    aux = head;
                }
                else {
                    aux->next = list2;
                    aux = aux->next;
                }
                list2 = list2->next;
            }
        }
        return head;
    }
};