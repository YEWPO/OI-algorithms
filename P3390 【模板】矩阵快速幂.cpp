#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define mod 1000000007
using namespace std;

typedef long long LL;

const int MAXN = 101;

template <typename T> inline void read(T &x) {
	T c = getchar(), f = 1;
	for(x = 0; !isdigit(c); c = getchar()) (c == '-') && (f = -1);
	for(; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	x *= f;
}

template <typename T> inline void print(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n;

struct Square {
	LL num[MAXN][MAXN];
	Square() {memset(num, 0, sizeof(num));}
	inline Square operator * (const Square &x) const {
		Square ret;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				for(int k = 1; k <= n; ++k)
					ret.num[i][j] += num[i][k] * x.num[k][j], ret.num[i][j] = (ret.num[i][j] + mod) % mod;
		return ret;
	}
};

inline Square power(Square x, LL y) {
	Square ret;
	for(int i = 1; i <= n; ++i) ret.num[i][i] = 1; //µ¥Î»¾ØÕó  
	while(y) {
		if(y & 1) ret = ret * x;
		x = x * x;
		y >>= 1;
	}
	return ret;
}

int main() {
	Square A;
	LL k;
	read(n), read(k);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			read(A.num[i][j]);
	Square ans = power(A, k);
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) print(ans.num[i][j]), putchar(' ');
		putchar('\n');
	}
	return 0;
}
