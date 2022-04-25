#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <functional>
#include <queue>
#define lowbit(x) x & -x
using namespace std;

const int MAXN = 1000001;

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

int head[MAXN], cnt;
struct Edge {
	int nxt, to;
	Edge() {}
	Edge(int _nxt, int _to) : nxt(_nxt), to(_to) {}
} e[MAXN << 1];

inline void Add_Edge(int u, int v) {
	e[++cnt] = Edge(head[u], v), head[u] = cnt;
	e[++cnt] = Edge(head[v], u), head[v] = cnt;
}

int sz[MAXN], seg[MAXN], tot;
long long c[MAXN], ci[MAXN];
int n, m, r;
long long a[MAXN];

void Modify(long long *Array, int x, long long val) {
	for(; x <= n; x += lowbit(x)) Array[x] += val;
}

long long Query(long long *Array, int x) {
	long long ret = 0;
	for(; x; x -= lowbit(x)) ret += Array[x];
	return ret;
}


void dfs1(int u, int f) {
	sz[u] = 1;
	seg[u] = ++tot;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == f) continue;
		dfs1(v, u);
		sz[u] += sz[v];
	}
}

signed main() {
	read(n), read(m), read(r);
	for(int i = 1; i <= n; ++i) read(a[i]);
	for(int i = 1, x, y; i < n; ++i) read(x), read(y), Add_Edge(x, y);
	dfs1(r, r);
	for(int i = 1; i <= n; ++i) {
		Modify(c, seg[i], a[i]);
		Modify(c, seg[i] + 1, -a[i]);
		Modify(ci, seg[i], a[i] * seg[i]);
		Modify(ci, seg[i] + 1, -a[i] * (seg[i] + 1));
	}
	for(int i = 1, opt, x, L, R; i <= m; ++i) {
		read(opt), read(x);
		long long val;
		if(opt == 1) {
			read(val);
			L = seg[x];
			R = seg[x] + sz[x] - 1;
			Modify(c, L, val), Modify(c, R + 1, -val);
			Modify(ci, L, val * L), Modify(ci, R + 1, -val * (R + 1));
		}
		else {
			L = seg[x];
			R = seg[x] + sz[x] - 1;
			long long suml = L * Query(c, L - 1) - Query(ci, L - 1);
			long long sumr = (R + 1) * Query(c, R) - Query(ci, R);
			print(sumr - suml), putchar('\n');
		}
	} 
	return 0;
}

