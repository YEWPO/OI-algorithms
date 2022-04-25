#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <functional>
#include <queue>
#define int long long
using namespace std;

const int MAXN = 8000010;
const int mod = 998244353;

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

int n, m, fa[MAXN], rank[MAXN], ans[MAXN], cnt, ANS;

int Find(int x) {
	return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

void Merge(int x, int y) {
	if(rank[x] < rank[y]) fa[y] = x;
	else {
		fa[x] = y;
		if(rank[x] == rank[y]) rank[x]++;
	}
}

bool Judge(int x, int y) {
	return x == y; 
}

int power(int x, int y, int prime) {
	int ret = 1;
	while(y) {
		if(y & 1) ret = ret * x % prime;
		x = x * x % prime;
		y >>= 1;
	}
	return ret;
}

signed main() {
	read(n), read(m);
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int i = 1, u, v; i <= m; ++i) {
		int opt;
		read(opt), read(u), read(v);
		int t1 = Find(u), t2 = Find(v);
		if(opt == 0) {
			Merge(t1, t2);
		}
		else { 
			ans[++cnt] = Judge(t1, t2);
		}
	}
	int pos = 1;
	while(ans[pos] == 0) pos++;
	for(int i = cnt; i >= pos; --i) {
		if(ans[i]) {
			ANS = (ANS % mod + power(2, i - pos, mod)) % mod;
		}
	}
	print(ANS), puts("");
	return 0;
}

