#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MaxN = 100001;
const int MaxM = 500001;

template <typename T> inline void read(T &a) {
	T ch = getchar(), f = 1;
	for(a = 0; !isdigit(ch); ch = getchar()) (ch == '-') && (f = -1);
	for(; isdigit(ch); ch = getchar()) a = (a << 3) + (a << 1) + ch - '0';
	a *= f;
}

template <typename T> inline void print(T x) {
	(x < 0) && (putchar('-'), x = -x);
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, m, head[MaxN], cnt;
struct Edge {
	int nxt, to;
	Edge() {}
	Edge(int _nxt, int _to) : nxt(_nxt), to(_to) {}
} e[MaxM];

inline void add(int u, int v) {
	e[++cnt] = Edge(head[u], v), head[u] = cnt;
}

int SCC, stk[MaxN], top, tot, dfn[MaxN], low[MaxN], belong[MaxN], in[MaxN], ans;
bool ins[MaxN];

void Tarjan(int u) {
	dfn[u] = low[u] = ++tot;
	stk[++top] = u;
	ins[u] = 1;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(ins[v]) low[u] = min(low[u], dfn[v]);
	}
	int t = -1;
	if(low[u] == dfn[u]) {
		SCC++;
		while(t != u) {
			t = stk[top--];
			belong[t] = SCC;
			ins[t] = 0;
		}
	}
}

signed main() {
	read(n), read(m);
	for(int i = 1, x, y; i <= m; ++i) read(x), read(y), add(x, y);
	for(int i = 1; i <= n; ++i) if(!dfn[i]) Tarjan(i);
	for(int u = 1; u <= n; ++u) {
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if(belong[v] != belong[u]) in[belong[v]]++;
		}
	}
	for(int i = 1; i <= SCC; ++i) if(!in[i]) ans++;
	print(ans), putchar('\n');
	return 0;
}
