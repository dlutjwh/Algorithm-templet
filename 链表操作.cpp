
using data_type = int;
struct ListNode {
	data_type data;
	ListNode *next;
}*head;
void addNode(ListNode **head,data_type value) {  //在链表尾部添加节点
	ListNode *p = new ListNode();
	p->next = nullptr;
	p->data = value;
	if (*head == nullptr) {
		*head = p;
	}
	else {
		ListNode *q = *head;
		while (q->next != nullptr) {
			q = q->next;
		}
		q->next = p;
	}
	return;
}
void OrderWalk(ListNode *p){     //顺序遍历链表
	while (p != nullptr) {
		cout << p->data << "-1" << endl;
		p = p->next;
	}
	cout << endl;
}
void deleteNode(ListNode **head ,data_type value) {   //删除第一个值为value的节点
	if (*head == nullptr)
		return;
	ListNode *p = *head;
	if ((*head)->data == value) {
		*head = p->next;
		delete(p);
		return;
	}
	while(p->next!=nullptr&&p->next->data != value) {
		p = p->next;
	}
	ListNode *q = p->next;
	if (q != nullptr) {
		p->next = q->next;
		delete q;
	}
}
void InorderWalk(ListNode *p) {    //逆序遍历链表
	if (p == nullptr)
		return;
	if (p->next == nullptr)
		cout << p->data<<" ";
	else InorderWalk(p->next);
}
