#include <bits/stdc++.h>
using namespace std;

const long long MAXN = 1000001;
const int mod = 1e9 + 7;

template <typename T> inline void read(T &x) {
	char c = getchar();
	bool f = false;
	for(x = 0; !isdigit(c); c = getchar()) {
		if(c == '-') {
			f = true;
		}
	}
	for(; isdigit(c); c = getchar()) {
		x = (x << 3) + (x << 1) + c - '0';
	}
	if(f) {
		x = -x;
	}
}

template <typename T> inline void print(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, p, m;

struct Square {
	long long num[501][501];
	Square() {memset(num, 0, sizeof(num));}
	friend inline Square operator * (const Square &a, const Square &b) {
		Square ret;
		for(register int i = 1; i <= n; ++i)
			for(register int j = 1; j <= m; ++j)
				for(register int k = 1; k <= p; ++k)
					ret.num[i][j] += a.num[i][k] * b.num[k][j] % mod, ret.num[i][j] = (ret.num[i][j] + mod) % mod;
		return ret;
	} 
};

int main() {
	read(n), read(p), read(m);
	Square A, B, ans;
	for(register int i = 1; i <= n; ++i)
		for(register int j = 1; j <= p; ++j)
			read(A.num[i][j]);
	for(register int i = 1; i <= p; ++i)
		for(register int j = 1; j <= m; ++j)
			read(B.num[i][j]);
	ans = A * B;
	for(register int i = 1; i <= n; ++i) {
		for(register int j = 1; j <= m; ++j)
			print(ans.num[i][j]), putchar(' ');
		putchar('\n');
	}
	return 0;
}
