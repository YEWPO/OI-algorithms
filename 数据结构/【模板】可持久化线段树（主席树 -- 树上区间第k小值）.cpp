#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100001;

inline int read() {
	char ch = getchar();
	int x = 0, f = 1;
	for(; !isdigit(ch); ch = getchar()) (ch == '-') && (f = -1);
	for(; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
	return x * f;
}

inline void print(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, m, head[MAXN], cnt, w[MAXN];
struct Edge {
	int nxt, to, len;
	Edge() {}
	Edge(int _nxt, int _to, int _len) : nxt(_nxt), to(_to), len(_len) {}
} E[MAXN << 1];

inline void add(int u, int v, int w) {
	E[++cnt] = Edge(head[u], v, w), head[u] = cnt;
	E[++cnt] = Edge(head[v], u, w), head[v] = cnt;
}

int rt[MAXN * 50];
struct Persistable_Segment_Tree {
	int v[MAXN * 50], ls[MAXN * 50], rs[MAXN * 50], SIZE;
	void init() {
		memset(v, 0, sizeof(v));
		memset(ls, 0, sizeof(ls));
		memset(rs, 0, sizeof(rs));
		SIZE = 0;
	}
	void build(int &x, int l, int r) {
		x = ++SIZE;
		if(l == r) return;
		int mid = (l + r) >> 1;
		build(ls[x], l, mid);
		build(rs[x], mid + 1, r);
	}
	void insert(int &x, int now, int l, int r, int pos) {
		x = ++SIZE;
		int mid = (l + r) >> 1;
		ls[x] = ls[now], rs[x] = rs[now], v[x] = v[now] + 1;
		if(l == r) return;
		if(pos <= mid) insert(ls[x], ls[now], l, mid, pos);
		else insert(rs[x], rs[now], mid + 1, r, pos);
	}
	int query(int x, int y, int z, int p, int l, int r, int kth) {
		if(l == r) return l;
		int mid = (l + r) >> 1;
		int S = kth - v[ls[x]] - v[ls[y]] + v[ls[z]] + v[ls[p]];
		if(S <= 0) return query(ls[x], ls[y], ls[z], ls[p], l, mid, kth);
		return query(rs[x], rs[y], rs[z], rs[p], mid + 1, r, S);
	}
} Tree;

int sz[MAXN], top[MAXN], son[MAXN], fa[MAXN], dep[MAXN], tot;

void dfs1(int u, int f) {
	sz[u] = 1;
	for(int i = head[u]; i; i = E[i].nxt) {
		int v = E[i].to;
		if(v == f) continue;
		dep[v] = dep[u] + 1;
		fa[v] = u;
		dfs1(v, u);
		sz[u] += sz[v];
		(sz[v] > sz[son[u]]) && (son[u] = v);
	}
	return;
}

void dfs2(int x) {
	top[x] = x == son[fa[x]] ? top[fa[x]] : x;
	Tree.insert(rt[x], rt[fa[x]], 1, tot, w[x]);
	if(son[x]) dfs2(son[x]);
	for(int i = head[x]; i; i = E[i].nxt) {
		int v = E[i].to;
		if(v == son[x] || v == fa[x]) continue;
		dfs2(v);
	}
	return;
}

int tmp[MAXN];

int LCA(int x, int y) {
	int fx = top[x], fy = top[y];
	while(fx != fy) {
		if(dep[fx] < dep[fy]) swap(fx, fy), swap(x, y);
		x = fa[fx], fx = top[x];
	}
	if(dep[x] > dep[y]) return y;
	return x;
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) w[i] = read(), tmp[i] = w[i];
	for(int i = 1; i < n; ++i) add(read(), read(), 0);
	sort(tmp + 1, tmp + n + 1);
	tot = (int) (unique(tmp + 1, tmp + n + 1) - tmp - 1);
	Tree.build(rt[0], 1, cnt);
	for(int i = 1; i <= n; ++i) w[i] = (int) (lower_bound(tmp + 1, tmp + tot + 1, w[i]) - tmp);
	dfs1(1, 1), dfs2(1);
	int last = 0;
	while(m--) {
		int l = read(), r = read(), k = read();
		l ^= last;
		int L = LCA(l, r);
		int p = Tree.query(rt[l], rt[r], rt[L], rt[fa[L]], 1, tot, k);
		print(tmp[p]), putchar('\n');
		last = tmp[p];
	}
	return 0;
}
