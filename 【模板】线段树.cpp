#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
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

int n, m;
int rt[MAXN * 40], ls[MAXN * 40], rs[MAXN * 40], SIZE, root;
int sum[MAXN * 40], MAX[MAXN * 40], MIN[MAXN * 40];
int mult[MAXN * 40], add[MAXN * 40], len[MAXN * 40];

inline void Pushdown(int x) {
	if(mult[x] != 1 || add[x]) {
		sum[ls[x]] = sum[ls[x]] * mult[x] + add[x] * len[ls[x]];
		sum[rs[x]] = sum[rs[x]] * mult[x] + add[x] * len[rs[x]];
		mult[ls[x]] *= mult[x];
		mult[rs[x]] *= mult[x];
		add[ls[x]] += add[x];
		add[rs[x]] += add[x];
		mult[x] = 1;
		add[x] = 0;
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
		add[x] += val;
		MAX[x] += val;
		MIN[x] += val;
		return;
	}
	Pushdown(x);
	int mid = (l + r) >> 1;
	if(L <= mid) Change_Add(ls[x], l, mid, L, R, val);
	if(R > mid) Change_Add(rs[x], mid + 1, r, L, R, val);
	Pushup(x);
}

void Change_Mult(int &x, int l, int r, int L, int R, int val) {
	if(!x) x = ++SIZE;
	len[x] = r - l + 1, mult[x] = 1;
	if(L <= l && r <= R) {
		sum[x] *= val;
		add[x] *= val;
		mult[x] *= val;
		MAX[x] *= val;
		MIN[x] *= val;
		return;
	}
	Pushdown(x);
	int mid = (l + r) >> 1;
	if(L <= mid) Change_Mult(ls[x], l, mid, L, R, val);
	if(R > mid) Change_Mult(rs[x], mid + 1, r, L, R, val);
	Pushup(x);
}

int Query_Max(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) return MAX[x];
	int ans = -INF, mid = (l + r) >> 1;
	if(L <= mid) ans = max(ans, Query_Max(ls[x], l, mid, L, R));
	if(R > mid) ans = max(ans, Query_Max(rs[x], mid + 1, r, L, R));
	return ans;
}

int Query_Min(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) return MIN[x];
	int ans = INF, mid = (l + r) >> 1;
	if(L <= mid) ans = min(ans, Query_Min(ls[x], l, mid, L, R));
	if(R > mid) ans = min(ans, Query_Min(rs[x], mid + 1, r, L, R));
	return ans;
}

int Query_Sum(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) return sum[x];
	int ans = 0, mid = (l + r) >> 1;
	Pushdown(x);
	if(L <= mid) ans += Query_Sum(ls[x], l, mid, L, R);
	if(R > mid) ans += Query_Sum(rs[x], mid + 1, r, L, R);
	return ans;
}

int main() {
	read(n), read(m);
	for(int i = 1, x; i <= n; ++i) read(x), Change_Add(root, 1, n, i, i, x);
	for(int i = 1, opt, l, r, val; i <= m; ++i) {
		read(opt), read(l), read(r);
		if(opt == 1) print(Query_Min(root, 1, n, l, r)), putchar('\n');
		else if(opt == 2) print(Query_Max(root, 1, n, l, r)), putchar('\n');
		else if(opt == 3) print(Query_Sum(root, 1, n, l, r)), putchar('\n');
		else if(opt == 4) read(val), Change_Add(root, 1, n, l, r, val);
		else if(opt == 5) read(val), Change_Mult(root, 1, n, l, r, val);
	}
	return 0;
}
/*
5 12
1 2 3 4 5
1 2 4
2 2 4
3 2 4
4 2 4 4
1 2 4
2 2 4
3 2 4
4 2 4 -4
5 2 4 4
1 2 4
2 2 4
3 2 4
*/
