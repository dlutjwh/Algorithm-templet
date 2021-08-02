#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cstdio>
#include<deque>
#include<stack>
using namespace std;
#define ll long long

class QuickSort{
public:

  struct ListNode {
	  int val,index;  //记录在之前链表中的id
	  ListNode *next;
	  ListNode(int x) :val(x), index(-1), next(NULL) {};
	  ListNode(int x,int i) :val(x), index(i), next(NULL) {};
  };
  QuickSort(const vector<int> &nums){  //对于vector构建链表 再快排
    ListNode *cur_node = nullptr;
    for(int i=0;i<nums.size();i++){
        ListNode *new_node = new ListNode(nums[i],i);
        if(Head==nullptr)
            Head = new_node;
        else{
            cur_node->next=new_node;
        }
        cur_node = new_node;
    }
  }
  void test(){
    ListNode *cur = Head;
    cout<<"before sort: ";
    while(cur!=nullptr){
        cout<<cur->val<<"("<<(cur->index)<<") ";
        cur = cur->next;
    }
    cout<<endl;
    Head = sortList(Head);
    cur = Head;
    cout<<"after sort: ";
    while(cur!=nullptr){
        cout<<cur->val<<"("<<(cur->index)<<") ";
        cur = cur->next;
    }
    cout<<endl;
  }

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
		//cout<<start->val<<" "<<end->val<<" "<<cnt->val<<-1<<endl;
		ListNode *L_cur_node=start;  //左半边 当前最后一个节点
		while (p != end) {
			while (p != end&&p->val >= cnt->val) {
				prep = p;
				p = p->next;
			}

			if (p != end) {  //插入到左边的最后 稳定排序
				prep->next = p->next;

				L_cur_node->next = p;
				L_cur_node = L_cur_node->next;



				p = prep->next;
			}
		}
		L_cur_node->next = cnt;
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
		while (p->next != end)
			p = p->next;
		p->next = nullptr;
		delete end;
		p = start->next;
		delete start;
		Head = p;
		return p;
	}
private:

	ListNode *Head = nullptr;
};

int main(){
    QuickSort s(vector<int>{5,3,3,2,1});
    //s.Head = new QuickSort::ListNode(3);
    s.test();
    //cout<<s.Head->val<<-1<<endl;
}



