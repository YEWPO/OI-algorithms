#include <bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;

typedef long long LL;

const int MAXN = 30010;

template <typename T> inline void read(T &x) {
	T ch = getchar(), f = 1;
	for(x = 0; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for(; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
	x *= f;
}

template <typename T> inline void print(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, q, head[MAXN], cnt;
struct Edge {
	int nxt, to;
	Edge() {}
	Edge(int _nxt, int _to) : nxt(_nxt), to(_to) {}
} e[MAXN << 1];

inline void Add_Edge(int u, int v) {
	e[++cnt] = Edge(head[u], v), head[u] = cnt;
	e[++cnt] = Edge(head[v], u), head[v] = cnt;
}

int son[MAXN], top[MAXN], dep[MAXN], fa[MAXN], seg[MAXN], sz[MAXN];

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
	seg[u] = ++seg[0];
	if(son[u]) dfs2(son[u]);
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == son[u] || v == fa[u]) continue;
		dfs2(v);
	}
}

int ls[MAXN * 40], rs[MAXN * 40], rt, SIZE;
LL MAX[MAXN * 40], sum[MAXN * 40];

void Change(int &x, int l, int r, int pos, LL val) {
	if(!x) x = ++SIZE;
	if(l == r) {
		sum[x] = val;
		MAX[x] = val;
		return;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) Change(ls[x], l, mid, pos, val);
	else Change(rs[x], mid + 1, r, pos, val);
	sum[x] = sum[ls[x]] + sum[rs[x]];
	MAX[x] = max(MAX[ls[x]], MAX[rs[x]]);
}

LL Query_Sum(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) return sum[x];
	LL ans = 0;
	int mid = (l + r) >> 1;
	if(L <= mid) ans += Query_Sum(ls[x], l, mid, L, R);
	if(R > mid) ans += Query_Sum(rs[x], mid + 1, r, L, R);
	return ans;
}

LL Query_Max(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) return MAX[x];
	LL ans = -0x7f3f3f3f3fLL;
	int mid = (l + r) >> 1;
	if(L <= mid) ans = max(ans, Query_Max(ls[x], l, mid, L, R));
	if(R > mid) ans = max(ans, Query_Max(rs[x], mid + 1, r, L, R));
	return ans;
}

LL Ask_Sum(int x, int y) {
	LL ret = 0;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		ret += Query_Sum(rt, 1, n, seg[top[x]], seg[x]);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	return ret + Query_Sum(rt, 1, n, seg[x], seg[y]);
}

LL Ask_Max(int x, int y) {
	LL ret = -0x7f3f3f3f3fLL;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		ret = max(ret, Query_Max(rt, 1, n, seg[top[x]], seg[x]));
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	return max(ret, Query_Max(rt, 1, n, seg[x], seg[y]));
}

int main() {
	read(n);
	for(int i = 1, a, b; i < n; ++i) read(a), read(b), Add_Edge(a, b);
	LL x;	
	dfs1(1, 1), dfs2(1);
	for(int i = 1; i <= n; ++i) read(x), Change(rt, 1, n, seg[i], x);
	char opt[6];
	read(q);
	for(int i = 1, u, v; i <= q; ++i) {
		scanf("%s", opt);
		read(u), read(v);
		if(opt[0] == 'C') {
			Change(rt, 1, n, seg[u], v);
		}
		else {
			if(opt[1] == 'M') {
				print(Ask_Max(u, v)), putchar('\n');
			}
			else if(opt[1] == 'S') {
				print(Ask_Sum(u, v)), putchar('\n');
			}
		}
	}
	return 0;
}
