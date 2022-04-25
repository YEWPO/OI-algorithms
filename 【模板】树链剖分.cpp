#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

const int MAXN = 200001;
const int INF = 0x3f3f3f3f;

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

int n, m, a[MAXN], head[MAXN], cnt;
struct Edge {
	int nxt, to;
	Edge() {}
	Edge(int _nxt, int _to) : nxt(_nxt), to(_to) {}
} e[MAXN << 1];

inline void add(int u, int v) {
	e[++cnt] = Edge(head[u], v), head[u] = cnt;
	e[++cnt] = Edge(head[v], u), head[v] = cnt;
}

int sz[MAXN], son[MAXN], top[MAXN], dep[MAXN], fa[MAXN], seg[MAXN], rev[MAXN], tot;

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
	return;
}

void dfs2(int u) {
	top[u] = u == son[fa[u]] ? top[fa[u]] : u;
	seg[u] = ++tot;
	rev[tot] = u;
	if(son[u]) dfs2(son[u]);
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == son[u] || v == fa[u]) continue;
		dfs2(v);
	}
	return;
}

int ls[MAXN], rs[MAXN], SIZE, root;
int sum[MAXN], MAX[MAXN], MIN[MAXN];
int mult[MAXN], tag[MAXN], len[MAXN];

inline void Pushdown(int x) {
	if(mult[x] != 1 || tag[x]) {
		sum[ls[x]] = sum[ls[x]] * mult[x] + tag[x] * len[ls[x]];
		sum[rs[x]] = sum[rs[x]] * mult[x] + tag[x] * len[rs[x]];
		mult[ls[x]] *= mult[x];
		mult[rs[x]] *= mult[x];
		tag[ls[x]] += tag[x];
		tag[rs[x]] += tag[x];
		mult[x] = 1;
		tag[x] = 0;
	}
}

inline void Pushup(int x) {
	sum[x] = sum[ls[x]] + sum[rs[x]];
	MAX[x] = max(MAX[ls[x]], MAX[rs[x]]);
	MIN[x] = min(MIN[ls[x]], MIN[rs[x]]);
}

void Change_Add(int &x, int l, int r, int L, int R, int val) {
	if(!x) x = ++SIZE;
	len[x] = r - l + 1, mult[x] = 1;
	if(L <= l && r <= R) {
		sum[x] += val * len[x];
		tag[x] += val;
		MAX[x] += val;
		MIN[x] += val;
		return;
	}
	int mid = (l + r) >> 1;
	Pushdown(x);
	if(L <= mid) Change_Add(ls[x], l, mid, L, R, val);
	if(R > mid) Change_Add(rs[x], mid + 1, r, L, R, val);
	Pushup(x);
}

void Change_Mult(int &x, int l, int r, int L, int R, int val) {
	if(!x) x = ++SIZE;
	len[x] = r - l + 1, mult[x] = 1;
	if(L <= l && r <= R) {
		sum[x] *= val;
		mult[x] *= val;
		MAX[x] *= val;
		MIN[x] *= val;
		return;
	}
	int mid = (l + r) >> 1;
	Pushdown(x);
	if(L <= mid) Change_Mult(ls[x], l, mid, L, R, val);
	if(R > mid) Change_Mult(rs[x], mid + 1, r, L, R, val);
	Pushup(x);
}

int Query_Max(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) return MAX[x];
	int mid = (l + r) >> 1, ans = -INF;
	if(L <= mid) ans = max(ans, Query_Max(ls[x], l, mid, L, R));
	if(R > mid) ans = max(ans, Query_Max(rs[x], mid + 1, r, L, R));
	return ans;
}

int Query_Min(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) return MIN[x];
	int mid = (l + r) >> 1, ans = INF;
	if(L <= mid) ans = min(ans, Query_Min(ls[x], l, mid, L, R));
	if(R > mid) ans = min(ans, Query_Min(rs[x], mid + 1, r, L, R));
	return ans;
}

int Query_Sum(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) return sum[x];
	int mid = (l + r) >> 1, ans = 0;
	Pushdown(x);
	if(L <= mid) ans += Query_Sum(ls[x], l, mid, L, R);
	if(R > mid) ans += Query_Sum(rs[x], mid + 1, r, L, R);
	return ans;
}

int Tree_Solve_Max(int x, int y) {
	int ans = -INF;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		ans = max(ans, Query_Max(root, 1, n, seg[top[x]], seg[x]));
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	return max(ans, Query_Max(root, 1, n, seg[x], seg[y]));
}

int Tree_Solve_Min(int x, int y) {
	int ans = INF;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		ans = min(ans, Query_Min(root, 1, n, seg[top[x]], seg[x]));
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	return min(ans, Query_Min(root, 1, n, seg[x], seg[y]));
}

int Tree_Solve_Sum(int x, int y) {
	int ans = 0;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		ans += Query_Sum(root, 1, n, seg[top[x]], seg[x]);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	return ans + Query_Sum(root, 1, n, seg[x], seg[y]);
}

void Tree_Change_Add(int x, int y, int val) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		Change_Add(root, 1, n, seg[top[x]], seg[x], val);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	Change_Add(root, 1, n, seg[x], seg[y], val);
}

void Tree_Change_Mult(int x, int y, int val) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		Change_Mult(root, 1, n, seg[top[x]], seg[x], val);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y]) swap(x, y);
	Change_Mult(root, 1, n, seg[x], seg[y], val);
}

int main() {
	read(n), read(m);
	for(int i = 1; i <= n; ++i) read(a[i]);
	for(int i = 1, x, y; i < n; ++i) read(x), read(y), add(x, y);
	dfs1(1, 1), dfs2(1);
	for(int i = 1; i <= n; ++i) Change_Add(root, 1, n, seg[i], seg[i], a[i]);
	for(int i = 1, opt, x, y, val; i <= m; ++i) {
		read(opt), read(x), read(y);
		if(opt == 1) print(Tree_Solve_Min(x, y)), putchar('\n');
		else if(opt == 2) print(Tree_Solve_Max(x, y)), putchar('\n');
		else if(opt == 3) print(Tree_Solve_Sum(x, y)), putchar('\n');
		else if(opt == 4) read(val), Tree_Change_Add(x, y, val);
		else if(opt == 5) read(val), Tree_Change_Mult(x, y, val);
	}
	return 0;
}
/*
7 11
1 2 3 4 5 6 7
1 2
1 3
2 4
2 5
3 6
3 7
1 1 4
2 1 4
3 1 4
4 2 4 1
1 1 4
2 1 4
3 1 4
5 1 7 5
1 1 4
2 1 4
3 1 4
*/
