class ListNode {
	public:
		int val;
		ListNode* next;

		ListNode(int x) : val(x), next(NULL) {};
		ListNode() : val(0), next(NULL) {};
}

class LinkedListUtils {
	public:
		static bool hasCycle(ListNode* head) {
			if (head == NULL || head->next == NULL) {
				return false;
			}

			ListNode *slowPtr = head, *fastPtr = head;

			do {
				slowPtr = slowPtr->next;
				if (fastPtr->next == NULL) {
					return false;
				} else {
					fastPtr = (fastPtr->next)->next;
				}
			} while (fastPtr != NULL && slowPtr != NULL && slowPtr != fastPtr);

			return (fastPtr != NULL && slowPtr != NULL);
		}

		static ListNode* getCycleStart(ListNode* head) {
			if (head == NULL || head->next == NULL) {
				return NULL;
			}

			ListNode *slowPtr = head, *fastPtr = head;

			do {
				slowPtr = slowPtr->next;
				if (fastPtr->next == NULL) {
					return false;
				} else {
					fastPtr = (fastPtr->next)->next;
				}
			} while (fastPtr != NULL && slowPtr != NULL && slowPtr != fastPtr);

			if (slowPtr != fastPtr) {
				return NULL;
			}

			slowPtr = head;

			while (slowPtr != fastPtr) {
				slowPtr = slowPtr->next;
				fastPtr = fastPtr->next;
			}
			return slowPtr;
		}

		static ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *l1, *l2;
        if (list1 == NULL) {
            return list2;
        } else if (list2 == NULL) {
            return list1;
        }
        
        if (list1->val < list2->val) {
            l1 = list1;
            l2 = list2;
        } else {
            l1 = list2;
            l2 = list1;
        }
        
        ListNode *res = l1, *prev = l1;
        l1 = l1->next;
        
        while (l1 != NULL) {
            if (l1->val < l2->val) {
                l1 = l1->next;
            } else {
                prev->next = l2;
                l2 = l1;
                l1 = (prev->next)->next;
            }
            prev = prev->next;
        }
        prev->next = l2;
        return res;
    }
}