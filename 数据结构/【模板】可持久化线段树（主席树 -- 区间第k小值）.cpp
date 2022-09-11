#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 200001;

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

int n, m, w[MAXN];
int rt[MAXN * 50], tmp[MAXN];

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
	int query(int x, int y, int l, int r, int kth) {
		if(l == r) return l;
		int mid = (l + r) >> 1;
		int S = v[ls[y]] - v[ls[x]];
		if(S >= kth) return query(ls[x], ls[y], l, mid, kth);
		return query(rs[x], rs[y], mid + 1, r, kth - S);
	}
} Tree;

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) w[i] = read(), tmp[i] = w[i];
	sort(tmp + 1, tmp + n + 1);
	int tot = (int) (unique(tmp + 1, tmp + n + 1) - tmp - 1);
	Tree.build(rt[0], 1, tot);
	for(int i = 1, p; i <= n; ++i) {
		p = lower_bound(tmp + 1, tmp + tot + 1, w[i]) - tmp;
		Tree.insert(rt[i], rt[i - 1], 1, tot, p);
	}
	while(m--) {
		int l = read(), r = read(), k = read();
		int p = Tree.query(rt[l - 1], rt[r], 1, tot, k);
		print(tmp[p]), putchar('\n');
	}
	return 0;
}
