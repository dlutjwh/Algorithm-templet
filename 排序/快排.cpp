class QuickSort{
public:
  struct ListNode {
	  int val;
	  ListNode *next;
	  ListNode(int x) :val(x), next(NULL) {};
  };
	void QuickSortArray(int a[], int l0,int r0) {
		int cnt = a[l0],l=l0,r=r0;
		while (r >l) {
			while (a[r] >= cnt&&r>l)
				r--;
			if (r > l)
				a[l] = a[r];
			while (a[l] < cnt&&r>l)
				l++;
			if (r > l)
				a[r] = a[l];
		}
		a[l] = cnt;
		if (l > l0)
			QuickSortArray(a, l0, l - 1);
		if (r < r0)
			QuickSortArray(a, l + 1, r0);		
	}
	void sortListDfs(ListNode *start, ListNode *end) {
		ListNode *p = start->next->next, *prep = start->next, *cnt = start->next;
		while (p != end) {
			while (p != end&&p->val >= cnt->val) {
				prep = p;
				p = p->next;
			}
			if (p != end) {
				prep->next = p->next;
				p->next = start->next;
				start->next = p;
				p = prep->next;
			}
		}
		if (start->next != cnt&&start->next->next != cnt)
			sortListDfs(start, cnt);
		if (cnt->next != end&&cnt->next->next != end)
			sortListDfs(cnt, end);

	}
	ListNode* sortList(ListNode* head) {
		if (head == nullptr || head->next == nullptr)
			return head;
		ListNode *start = new ListNode(INT_MIN), *end = new ListNode(INT_MAX);
		start->next = head;
		ListNode *p = head;
		while (p->next != nullptr)
			p = p->next;
		p->next = end;
		sortListDfs(start, end);
		p = start;
		//while (p->next != end)
		//	p = p->next;
		//p->next = nullptr;
		delete end;
		p = start->next;
		delete start;
		return p;
	}
};
