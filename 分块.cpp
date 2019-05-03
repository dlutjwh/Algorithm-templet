
//分块，单点修改，区间查询最大值 cdoj  卿学姐与公主
//block为块的大小，num为块的个数，l[i]表示第i个块的左边界下标，
//r[i]表示第i个块的右边界下标，belong[i]表示第i个元素所属的块
const int maxn = 100005;
int n, block, num, l[maxn], r[maxn];
long long Max[maxn], a[maxn], belong[maxn];
class FK{  //下标从1开始
public:
	void build(int m){  
		n = m;
		block = sqrt(n);
		//memset(Max, 0, sizeof(Max));
		num = (n + block - 1) / block;
		for (int i = 1;i <= num;i++) {
			l[i] = (i - 1)*block + 1;
			r[i] = l[i] + block - 1;
		}
		for (int i = 1;i <= n;i++)
			belong[i] = (i - 1) / block + 1;
		r[num] = n;
		for (int i = 1;i <= num;i++) {
			for (int j = l[i];j <= r[i];j++)
				Max[i] = max(Max[i], a[j]);
		}
	}
	void update(int x, long long z) {
		a[x] += z;
		Max[belong[x]] = max (Max[belong[x]], a[x]);
	}
	long long ask(int x, int y) {
		long long ans = 0;
		if (belong[x] == belong[y]) {
			for (int i = x;i <= y;i++)
				ans = max(ans, a[i]);
			return ans;
		}
		for (int i = x;i <= r[belong[x]];i++)
			ans = max(ans, a[i]);
		for(int i=y;i>=l[belong[y]];i--)
			ans = max(ans, a[i]);
		for (int i = belong[x] + 1;i <= belong[y] - 1;i++)
			ans = max(ans, Max[i]);
		return ans;
	}

};
