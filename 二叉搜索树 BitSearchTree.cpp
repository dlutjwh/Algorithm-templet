using Elem_Type = int;
struct BitSearchTree {
	BitSearchTree *left = nullptr, *right = nullptr, *parent = nullptr;
	Elem_Type data;
}*Root;
void Inorder_Walk(BitSearchTree *t) {   //从小到大输出二叉树的值（中序遍历）
	if (t != nullptr) {
		Inorder_Walk(t->left);
		printf("%d", t->data);
		Inorder_Walk(t -> right);
	}
}
BitSearchTree *Find_node(BitSearchTree *t, Elem_Type x) {    //搜索值为x的节点（也可用while循环）
	if (t == nullptr) {
		//cout<<"not find"<<endl;
		return t;
	}
	if (t->data == x)
		return t;
	if (x > t->data)
		return Find_node(t->right,x);
	return Find_node(t->left, x);
}
BitSearchTree *Maxmum(BitSearchTree *t,Elem_Type &a) {    //查找最大值节点
	while (t->right != nullptr) {
		a = t->data;
		t = t->right;
		
	}
	
	return t;
}
BitSearchTree *Minimum(BitSearchTree *t, Elem_Type &a) {  //查找最小值节点
	while (t->left != nullptr) {
		a = t->data;
		t = t->left;
	}
	return t;
}
BitSearchTree *Succcessor(BitSearchTree *t, Elem_Type &a) {  //查找节点t的后继
	if (t->right != nullptr)
		return Minimum(t->right, a);
	BitSearchTree *p = t->parent;
	while (p != nullptr&&p->right == t) {
		a = p->data;
		t = p;
		p = p->parent;
	}
	return p;
}
BitSearchTree *Precursor(BitSearchTree *t, Elem_Type &a) {  //查找节点t的前驱
	if (t->left != nullptr)
		return Maxmum(t->left, a);
	BitSearchTree *p = t->parent;
	while (p != nullptr&&p->left == t) {
		t = p;
		a = p->data;
		p = p->parent;
	}
	return p;
}
BitSearchTree *InsertNode(BitSearchTree *t, Elem_Type a) {   //插入一个值a，t一般为root
	BitSearchTree *x =new BitSearchTree(), *z=nullptr;
	x->data = a;
	while (t != nullptr) {
		z = t;
		if (a > t->data)
			t = t->right;
		else t = t->left;
	}
	x->parent = z;
	if (z == nullptr) {
		Root = x;
		return Root;
	}
	else if (z->data > a)
		z->left = x;
	else z->right = x;
	return x;
}
void Transplant(BitSearchTree *u, BitSearchTree *v) {  //v为根的子树代替u为根的子树，未更新v的孩子
	if (u->parent == nullptr)
		Root = v;
	else if (u->parent->left == u)
		u->parent->left = v;
	else u->parent->right = v;
	if (v != nullptr)
		v->parent = u->parent;
}
void DeleteNode(BitSearchTree *t,int &a) {  //删除节点t
	if (t != nullptr)
		a = t->data;
	if (t->left == nullptr)
		Transplant(t, t->right);
	else if (t->right == nullptr)
		Transplant(t, t->left);
	else if (t->right->left == nullptr) {
		Transplant(t, t->right);
		t->left->parent = t->right;
		t->right->left = t->left;	
	}
	else {
		int b=0;
		BitSearchTree *p = Succcessor(t, b);
		Transplant(p, p->right);
		Transplant(t, p);
		p->left = t->left;
		p->left->parent = p;
		p->right = t->right;
		p->right->parent = p;
	}
	delete t;
}
