
class BigNum {

	//注意：使用四位数存储注意前导0

public:
	int num[1000]; //每DLEN位数存储一起，低位在前，高位在后  0-len-1,其中len-1位可能不足四位
	static const int DLEN=4;
	int len;
	static const int MAXN=10000;
	BigNum() {     //构造函数
		len = 1;
		memset(num, 0, sizeof(num));
	}
	BigNum(const int);
	BigNum(const char*);
	BigNum(const BigNum &);
	BigNum &operator = (const BigNum &);
	friend istream& operator >> (istream&, BigNum&);
	friend ostream& operator << (ostream&, BigNum&);
	BigNum operator +(const BigNum &) const;   
	BigNum operator -(const BigNum &) const;
	BigNum operator *(const BigNum &) const;
	BigNum operator /(const int &) const;
	BigNum operator ^(const int &) const;
	int operator %(const int &)const;
	bool operator >(const BigNum&) const;
	bool operator >(const int& t) const { BigNum b(t); return *this > b; }
	bool operator ==(const BigNum&) const;
	bool operator <(const BigNum& B)const {return !((*this == B) || (*this > B)); }
	bool operator <=(const BigNum& B) const { return !(*this > B); }
	bool operator !=(const BigNum& B) const { return !(*this == B); }
	bool operator >=(const BigNum& B)const { return *this > B || *this == B; }
	void print();
	

};
BigNum::BigNum(const int b) {
	len = 0;
	int  d = b;
	memset(num, 0, sizeof(num));
	while (d >= MAXN) {
		num[len++] = d%MAXN;
		d /= MAXN;
	}
	num[len++] = d;
}
BigNum::BigNum(const char *s) {
	int i, l, z, cnt = 0;
	memset(num, 0, sizeof(num));
	l = strlen(s);
	for (i = l - 1;i >= 0;i -= DLEN) {
		z = 0;
		for (int k = max(i - DLEN + 1,0);k <= i;k++)
			z = z * 10 + s[k] - '0';
		num[cnt++] = z;
	}
	len = cnt;
}
BigNum::BigNum(const BigNum &Big) {
	int l = Big.len;
	len = l;
	memset(num, 0, sizeof(num));
	for (int i = 0;i < l;i++)
		num[i] = Big.num[i];
}
BigNum & BigNum::operator=(const BigNum &B) {
	int l = B.len;
	memset(num, 0, sizeof(num));
	for (int i = 0;i < l;i++)
		num[i] = B.num[i];
	len = l;
	return *this;
}
istream& operator >> (istream &in, BigNum &b) {
	 char ch[1000];
	 int i = -1;
	 in >> ch;
	 int l = strlen(ch);
	 int cnt = 0;
	 /*for (int i = 0;i < l;i++)
		 if (ch1[i] >= '0'&&ch1[i] <= '9')
			 ch[cnt++] = ch1[i];
	 ch[cnt] = '\0';
	 */
	 int L = strlen(ch);
	 int count = 0, sum = 0;
	 for (i = L-1;i >= 0;) {
		 sum = 0;
		 int t = 1;
		 for (int j = 0;j<4 && i >= 0;j++, i--, t *= 10) {
		 sum += (ch[i]-'0')*t;
			
	}
		 b.num[count] = sum;
		 count++;
		
	}
	 b.len = count++;
	 return in;
	
}

ostream& operator<<(ostream& out, BigNum& b) {
	printf("%d", b.num[b.len - 1]);
	for (int i = b.len - 2;i >= 0;i--)
		printf("%04d", b.num[i]);
	return out;
}

BigNum BigNum::operator-(const BigNum& B) const {
	bool flag = 0;
	BigNum tmp1, tmp2;
	if (*this > B) {
		tmp1 = *this;
		tmp2 = B;
		flag = 1;
	}
	else {
		tmp1 = B;
		tmp2 = *this;
	}
	int l = tmp1.len;
	for (int i = 0;i < l;i++) {
		tmp1.num[i] -= tmp2.num[i];
		if (tmp1.num[i] < 0) {
			tmp1.num[i] += MAXN;
			tmp1.num[i+1] -= 1;
		}
	}
	for (int i = l - 1;i >= 0;i--) {
		if (tmp1.num[i] != 0) {
			tmp1.len = i + 1;
			break;
		}
	}
	if (!flag)
		tmp1.num[tmp1.len - 1] *= -1;
	return tmp1;
}
BigNum BigNum::operator*(const BigNum &B)const {
	BigNum mul;
	int i, j;
	for (i = 0;i < len;i++) {
		int up = 0;
		for (j = 0;j < B.len;j++) {
			int tmp = num[i] * B.num[j]+mul.num[i+j]+up;
			if (tmp >= MAXN) {
				int tmp1 = tmp - tmp / MAXN*MAXN;
				up = tmp / MAXN;
				mul.num[i + j] = tmp1;
			}
			else {
				up = 0;
				mul.num[i + j] = tmp;
			}
		}
		if (up!=0)
			mul.num[i + j] = up;
	}
	mul.len = i + j;
	while (mul.num[mul.len-1]==0&&mul.len>1) {
		mul.len--;
	}
	return mul;
}
BigNum BigNum::operator/(const int &b)const {
	BigNum div;
	int mod = 0;
	for (int i = len - 1;i >= 0;i--) {
		div.num[i] = (mod*MAXN + num[i]) / b;
		mod = mod*MAXN + num[i] - div.num[i] * b;
	}
	div.len = len;
	while (div.num[div.len - 1] == 0 && div.len > 1)
		div.len--;
	return div;
}

BigNum BigNum::operator^(const int &n)const {
	BigNum t(1), z(*this);

	if (n == 0) return 1;
	if (n == 1) return *this;
	int m = n;
	stack<int> s;
	while (m > 0) {
		if (m % 2) {
			s.push(1);
			m -= 1;
		}
		else {
			s.push(0);
			m /= 2;
		}
	}

	while (!s.empty()) {
		if (s.top()==1) {
			t = t*z;
		}
		else t =( t*t);
		s.pop();
		
	}
	return t;
}
BigNum BigNum::operator+(const BigNum& T)const {
	BigNum t(*this);
	int big;
	big = T.len > len ? T.len : len;
	for (int i = 0;i < big;i++) {
		t.num[i] += T.num[i];
		if (t.num[i] >= MAXN) {
			t.num[i + 1]++;
			t.num[i] -= MAXN;
		}
	}
	if (t.num[big] != 0)
		t.len = big + 1;
	else t.len = big;
	return t;
}
bool BigNum::operator ==(const BigNum& B)const {
	if (len != B.len)
		return 0;
	for (int i = 0;i < len;i++) {
		if (num[i] != B.num[i])
			return 0;
	}
	return 1;
}
bool BigNum::operator >(const BigNum &B) const{
	if (len > B.len)
		return 1;
	if (len < B.len)
		return 0;
	for (int i = len - 1;i >= 0;i--) {
		if (num[i] > B.num[i])
			return 1;
		else return 0;
	}
	return 0;

}

int BigNum::operator %(const int &mod) const {
	long long d = 0,m=mod,z=MAXN;
	for (int i = len - 1;i >= 0;i--) {
		d = (d*MAXN%m + (long long)num[i]) % m;
	}
	return d;
}
void BigNum::print() {
	printf("%d", num[len - 1]);
	for (int i = len - 2;i >= 0;i--)
		printf("%04d", num[i]);
	printf("\n");
}
