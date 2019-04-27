class InsertSort {
public:
	void insertionSortArray(int a[], int n) {    //数组形式
		for (int i = 1;i < n;i++) {
			for (int j = 0;j < i;j++) {
				if (a[j] >= a[i] ) {
					int cnt = a[i];
					if (i != j) {
						for (int k = i;k > j;k--)
							a[k] = a[k - 1];
					}
					a[j] = cnt;
					break;
				}
			}
		}
	}
	ListNode* insertionSortList(ListNode* head) {      //链表形式
		if (head == nullptr)
			return nullptr;
		ListNode *first = new ListNode(INT_MIN);
		
		first->next = head;
		while (head->next != nullptr) {
			
			while (head->next&&head->next->val>=head->val) 
				head = head->next;
			if (head&&head->next!=nullptr) {
				ListNode *p = first,*q =head->next->next,*m=nullptr;
				while (p->next&&p->next->val < head->next->val) {
					p = p->next;
				}
				m = p->next;
				p->next = head->next;
				p->next->next = m;
				head->next = q;
			}
		}
		return first->next;
		
	}
};
