#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <functional>
#include <queue>
using namespace std;

typedef long long LL;

const int MAXN = 200001;
const int MAXM = 500001;

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

int n, m, fa[MAXN], rank[MAXN];
LL ans;
struct Node {
	int u, v;
	LL w;
} a[MAXM];

int Find(int x) {
	return x == fa[x] ? x : fa[x] = Find(fa[x]);
} 

void Merge(int x, int y) {
	if(rank[x] < rank[y]) fa[y] = x;
	else {
		fa[x] = y;
		if(rank[x] == rank[y]) fa[x] = y;
	}
}

bool cmp(Node x, Node y) {
	return x.w < y.w;
}

int main() {
	read(n), read(m);
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int i = 1; i <= m; ++i) {
		read(a[i].u), read(a[i].v), read(a[i].w);
	}
	sort(a + 1, a + m + 1, cmp);
	for(int i = 1; i <= m; ++i) {
		int x = a[i].u, y = a[i].v;
		int t1 = Find(x), t2 = Find(y);
		if(t1 != t2) {
			ans += a[i].w;
			Merge(t1, t2);
		}
	}
	print(ans), putchar('\n');
	return 0;
}

