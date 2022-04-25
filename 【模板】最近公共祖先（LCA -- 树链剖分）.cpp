#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int MaxN = 500001;

template <typename T> inline void read(T &a) {
	T ch = getchar(), f = 1;
	for(a = 0; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for(; isdigit(ch); ch = getchar()) a = (a << 3) + (a << 1) + ch - '0';
	a *= f;
}

template <typename T> inline void print(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, m, s, head[MaxN], cnt;
struct Edge {
	int nxt, to;
	Edge() {}
	Edge(int _nxt, int _to) : nxt(_nxt), to(_to) {}
} e[MaxN << 1];

inline void add(int u, int v) {
	e[++cnt] = Edge(head[u], v), head[u] = cnt;
	e[++cnt] = Edge(head[v], u), head[v] = cnt;
}

int size[MaxN], son[MaxN], top[MaxN], dep[MaxN], fa[MaxN];

void dfs1(int u, int f) {
	size[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == f) continue;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs1(v, u);
		size[u] += size[v];
		(size[v] > size[son[u]]) && (son[u] = v);
	}
}

void dfs2(int u) {
	top[u] = u == son[fa[u]] ? top[fa[u]] : u;
	if(son[u]) dfs2(son[u]);
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == fa[u] || v == son[u]) continue;
		dfs2(v);
	}
}

int LCA(int x, int y) {
	int fx = top[x], fy = top[y];
	while(fx != fy) {
		if(dep[fx] < dep[fy]) swap(fx, fy), swap(x, y);
		x = fa[fx], fx = top[x];
	}
	if(dep[x] > dep[y]) return y;
	return x;
}

signed main() {
	read(n), read(m), read(s);
	for(int i = 1, x, y; i < n; ++i) read(x), read(y), add(x, y);
	dfs1(s, s), dfs2(s);
	while(m--) {
		int a, b;
		read(a), read(b);
		print(LCA(a, b)), puts("");
	}
	return 0;
}
