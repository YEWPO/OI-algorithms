#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define int unsigned long long
#define mod 998244353LL
using namespace std;

const int MAXN = 300001;

template <typename T> inline void read(T &x) {
	T ch = getchar(), f = 1;
	for(x = 0; !isdigit(ch); ch = getchar()) (ch == '-') && (f = -1);
	for(; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
	x *= f;
}

template <typename T> inline void print(T x) {
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, m, head[MAXN], cnt;
int son[MAXN], top[MAXN], dep[MAXN], fa[MAXN], sz[MAXN], fac[MAXN][51], sum[MAXN][51], Pow[MAXN][51];
struct Edge {
	int nxt, to;
	Edge() {}
	Edge(int _nxt, int _to) : nxt(_nxt), to(_to) {}
} e[MAXN << 1];

inline void Add_Edge(int u, int v) {
	e[++cnt] = Edge(head[u], v), head[u] = cnt;
	e[++cnt] = Edge(head[v], u), head[v] = cnt;
}

int power(int x, int y) {
	int ret = 1;
	while(y) {
		if(y & 1) ret = (ret % mod * x % mod) % mod;
		x = (x % mod * x % mod) % mod;
		y >>= 1;
	}
	return (ret + mod) % mod;
}

void Pre() {
	for(int i = 1; i <= n; ++i)
		for(int k = 1; k <= 50; ++k)
			Pow[i][k] = power(i, k);
	for(int i = 1; i <= n; ++i)
		for(int k = 1; k <= 50; ++k)
			fac[i][k] = Pow[dep[i]][k], fac[i][k] = (fac[i][k] + mod) % mod;
	for(int i = 1; i <= n; ++i)	
		for(int k = 1; k <= 50; ++k)
			sum[i][k] = sum[i - 1][k] + Pow[i][k], sum[i][k] = (sum[i][k] + mod) % mod;
}

void dfs1(int u, int f) {
	sz[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == f) continue;
		dep[v] = dep[u] + 1;
		fa[v] = u;
		dfs1(v, u);
		sz[u] += sz[v];
		(sz[v] > sz[son[u]]) && (son[u] = v);
	}
}

void dfs2(int u) {
	top[u] = u == son[fa[u]] ? top[fa[u]] : u;
	if(son[u]) dfs2(son[u]);
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == son[u] || v == fa[u]) continue;
		dfs2(v);
	}
}

int LCA(int x, int y) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) return y;
	return x;
}

signed main() {
	read(n);
	for(int i = 1, x, y; i < n; ++i) read(x), read(y), Add_Edge(x, y);
	dfs1(1, 1), dfs2(1), Pre();
	read(m);
	for(int i = 1, a, b, k; i <= m; ++i) {
		read(a), read(b), read(k);
		int d = LCA(a, b), ans = 0;
		ans += sum[dep[b]][k] - sum[dep[d]][k];
		ans = (ans + mod) % mod;
		ans += sum[dep[a]][k] - sum[dep[d]][k];
		ans = (ans + mod) % mod;
		ans += fac[d][k];
		ans = (ans + mod) % mod;
		print(ans), putchar('\n');
	}
	return 0;
}
