void cal_nx(string p,int nx[]) {  //计算nx数组，nx[i]表示匹配串前i个字符中后缀与前缀相同的最大长度
	nx[0] = -1;
	int k = -1;
	for (int i = 1;i < p.size();i++) {
		while (k > -1 && p[k + 1] != p[i])
			k = nx[k];
		if (p[k + 1] == p[i])
			k++;
		nx[i] = k;
	}
}

int KMP(string s, string p) {  //s为模板串，p为匹配串
	int *nx = new int[p.size()];
	cal_nx(p, nx);
	int k = -1;
	for (int i = 0;i < s.size();i++) {
		while (k > -1 && s[i] != p[k+1])
			k = nx[k];
		if (s[i] == p[k + 1])
			k++;
		if (k == p.size()-1) {
			delete[] nx;
			return i - p.size() + 1;   //返回第一次出现时模板串的首字符位置
		}
	}
	delete[] nx;
	return -1;
}
