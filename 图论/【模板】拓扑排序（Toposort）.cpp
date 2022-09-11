#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 1000001;

inline int read() {
	int num = 0, f = 1, ch;
	for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for(; isdigit(ch); ch = getchar()) num = (num << 3) + (num << 1) + ch - '0';
	return num * f;
}

inline void print(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, m, head[MAXN], cnt, deg[MAXN], ans[MAXN], len;
queue <int> q;
struct Edge {
	int nxt, to;
	Edge() {}
	Edge(int _nxt, int _to) : nxt(_nxt), to(_to) {}
} e[MAXN << 1];

inline void add(int u, int v) {
	e[++cnt] = Edge(head[u], v), head[u] = cnt;
}

inline void topo() {
	while(!q.empty()) {
		int u = q.front();
		ans[++len] = u, q.pop();
		for(int i = head[u], v; i; i = e[i].nxt) {
			deg[v = e[i].to]--;
			if(!deg[v]) q.push(v);
		}
	}
	for(int i = 1; i <= len; ++i) print(ans[i]), putchar(' ');
}

int main() {
	n = read(), m = read();
	for(int i = 1, x, y; i <= m; ++i) x = read(), y = read(), add(x, y), deg[y]++;
	for(int i = 1; i <= n; ++i) if(!deg[i]) q.push(i);
	topo();
	return 0;
}
