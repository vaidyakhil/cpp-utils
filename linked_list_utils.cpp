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
			} while (fastPtr != NULL && slowPtr != fastPtr);

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

		static ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	        if (l1 == NULL || l2 == NULL) {
	            return l1 == NULL ? l2 : l1;
	        }
	        
	        ListNode* head = l1->val < l2->val ? l1 : l2;
	        ListNode* aux = l1 == head ? l2 : l1;
	        
	        ListNode* cur = head, *prev= NULL;
	        while (cur != NULL) {
	            if (cur->val  > aux->val) {
	                prev-> next = aux;
	                aux = cur;
	                cur = prev->next;
	            }
	            prev = cur;
	            cur = cur->next;
	        }
	        prev->next = aux;
	        
	        return head;
	    }
}