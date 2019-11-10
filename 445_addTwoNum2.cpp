/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 -> val == 0) return l2;
        if (l2 -> val == 0) return l1;
        std::stack<int> stack1;
        std::stack<int> stack2;
        while (l1) {
            stack1.push(l1 -> val);
            l1 = l1 -> next;
        }
        while (l2) {
            stack2.push(l2 -> val);
            l2 = l2 -> next;
        }
        int carry = 0;
        ListNode* dummy = new ListNode(0);
        while (!stack1.empty() || !stack2.empty()) {
            int num1 = 0, num2 = 0;
            if (!stack1.empty()) {
                num1 = stack1.top();
                stack1.pop();
            }
            if (!stack2.empty()) {
                num2 = stack2.top();
                stack2.pop();
            }
            int val = (num1 + num2 + carry) % 10;
            carry = (num1 + num2 + carry) / 10;
            ListNode* new_node = new ListNode(val);
            new_node->next = dummy->next;
            dummy->next = new_node;
        }
        if (carry != 0) {
            ListNode* head = new ListNode(carry);
            head -> next = dummy -> next;
            dummy -> next = head;
        }
        return dummy -> next;
    }
};
/*
Time = O(n)
Space = O(n)
*/
