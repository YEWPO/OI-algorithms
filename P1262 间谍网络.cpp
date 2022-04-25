#include <bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;

const int MAXN = 3001;
const int MAXM = 8001;

template <typename T> inline void read(T &x) {
	T c = getchar(), f = 1;
	for(x = 0; !isdigit(c); c = getchar()) (c == '-') && (f = -1);
	for(; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - '0';
	x *= f;
}

template <typename T> inline void print(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, p, w[MAXN], cnt, head[MAXN];
bool buy[MAXN], flag;
struct Edge {
	int nxt, to;
	Edge() {}
	Edge(int _nxt, int _to) : nxt(_nxt), to(_to) {}
} e[MAXM], e_scc[MAXM];

inline void add(int u, int v) {
	e[++cnt] = Edge(head[u], v), head[u] = cnt;
}

int dfn[MAXN], low[MAXN], belong[MAXN], stk[MAXN], top, SCC, tot;
bool ins[MAXN];

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
			ins[t] = 0;
			belong[t] = SCC;
		}
	}
}

int head_scc[MAXN], cnt_scc, spy[MAXN], spy_cnt, W[MAXN], rd[MAXN];

inline void add_scc(int u, int v) {
	e_scc[++cnt_scc] = Edge(head_scc[u], v), head_scc[u] = cnt_scc;
}

int r;

bool notbuy[MAXN];

int main() {
	memset(W, 0x3f, sizeof(W));
	read(n), read(p);
	for(int i = 1, x; i <= p; ++i) {
		read(x);
		spy[++spy_cnt] = x;
		read(w[x]);
	}
	read(r);
	for(int i = 1, x, y; i <= r; ++i) {
		read(x), read(y);
		add(x, y);
	}
	for(int i = 1; i <= n; ++i) if(!dfn[i]) Tarjan(i);
	for(int i = 1; i <= spy_cnt; ++i) W[belong[spy[i]]] = min(W[belong[spy[i]]], w[spy[i]]), buy[belong[spy[i]]] = 1;
	for(int u = 1; u <= n; ++u) {
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if(belong[v] != belong[u]) rd[belong[v]]++;
		}
	}
	int ans = 0, tongji = 0;
	for(int i = 1; i <= SCC; ++i) {
		if(!rd[i] && buy[i]) tongji++, ans += W[i];
		if(!rd[i] && !buy[i]) {
			puts("NO");
			notbuy[i] = 1;
			flag = 1;
			break;
		}
	}
	for(int i = 1; i <= n; ++i) {
		if(notbuy[belong[i]]) {
			print(i), putchar('\n');
			break;
		}
	}	
	if(!flag) {
		puts("YES");
		print(ans), putchar('\n');
	}
	return 0;
}
