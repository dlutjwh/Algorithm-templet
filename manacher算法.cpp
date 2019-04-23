//manacher算法用于求字符串的最长回文子串，复杂度为线性的
  
  string init(const string &s) {
		string s1;
		s1 += '$';  //加入特殊字符防止越界
		for (int i = 0;i < s.size();i++) {
			s1 += '#';
			s1 += s[i];
		}
		s1 += '#';
		s1 += '&';
		return s1;
	}
	int manachar(string s, int *Len) {
		int len = s.size() * 2 + 1;
		//Len[i]表示以第i个字符为中心的回文串半径
		int *Len = new int[len + 1];
		int ans = 0;
		int mx = 0, pos = 0;   //mx 为查到的子回文串的右边界最大值，pos为对应的中心位置
		for (int i = 1;i <= len;i++) {
			if (mx > i)
				Len[i] = min(mx - i, Len[2 * pos - i]);     //核心代码
			else Len[i] = 1;
			while (s[i - Len[i]] == s[i + Len[i]])
				Len[i]++;
			if (Len[i] + i > mx) {
				pos = i;
				mx = Len[i] + i;
			}
			ans = max(ans, Len[i]);
		}
		return ans-1;
	}
