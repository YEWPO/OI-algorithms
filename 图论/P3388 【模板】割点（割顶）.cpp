#include <bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;

const int MAXN = 20001;
const int MAXM = 100001;

template <class T> inline void read(T &x) {
	T c = getchar(), f = 1;
	for(x = 0; !isdigit(c); c = getchar()) (c == '-') && (f = -1);
	for(; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	x *= f;
}

template <typename T> inline void print(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, m, head[MAXN], cnt, ans;
struct Edge {
	int nxt, to;
	Edge() {}
	Edge(int _nxt, int _to) : nxt(_nxt), to(_to) {}
} e[MAXM << 1];

inline void add(int u, int v) {
	e[++cnt] = Edge(head[u], v), head[u] = cnt;
	e[++cnt] = Edge(head[v], u), head[v] = cnt;
}

int dfn[MAXN], low[MAXN], tot, root;
bool cut[MAXN];

void Tarjan(int u, int f) {
	dfn[u] = low[u] = ++tot;
	int flag = 0;
	for(int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(v == f) continue;
		if(!dfn[v]) {
			Tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if(dfn[u] <= low[v]) {
				flag++;
				if(flag > 1 || u != root) cut[u] = 1;
			}
		} else low[u] = min(low[u], dfn[v]);
	}
}

int main() {
	read(n), read(m);
	for(int i = 1, x, y; i <= m; ++i) read(x), read(y), add(x, y);
	for(int i = 1; i <= n; ++i) if(!dfn[i]) {
		tot = 0;
		Tarjan(i, root = i);	
	}
	for(int i = 1; i <= n; ++i) if(cut[i]) ans++;
	print(ans), putchar('\n');
	for(int i = 1; i <= n; ++i) {
		if(cut[i]) {
			print(i), putchar(' ');
		}
	}
	putchar('\n');
	return 0;
}
