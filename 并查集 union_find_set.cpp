class union_find_set {
public:
	union_find_set(int n) {
		fa = new int[n];
		rank = new int[n];
		for (int i = 0; i < n; i++)
			fa[i] = i;
	}
	~union_find_set()
	{
		delete fa,rank;
	};
	int find(int x) {
		if (fa[x] == x)
			return x;
		return fa[x] = find(fa[x]);
	}
	void unite(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y)
			return;
		if (rank[x] < rank[y])
			fa[x] = y;
		else {
			fa[y] = x;
			if (rank[x] == rank[y])
				rank[x]++;
		}
	}
	bool same(int x, int y) {
		if (find(x) == find(y))
			return 1;
		return 0;
	}
	int n;
	int *fa,*rank;
};
