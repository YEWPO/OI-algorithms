#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 200001;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &a) {
	T ch = getchar(), f = 1;
	for(a = 0; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for(; isdigit(ch); ch = getchar()) a = (a << 3) + (a << 1) + ch - '0';
	a *= f;
}

template <typename T> inline void print(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

queue <int> q;
int n, m, head[MAXN], cnt = 1, maxflow, d[MAXN], s, t;
bool vis[MAXN];
struct Edge {
	int nxt, to, cost;
	Edge() {}
	Edge(int _nxt, int _to, int _cost) : nxt(_nxt), to(_to), cost(_cost) {}
} e[MAXN << 1];

inline void add(int u, int v, int w) {
	e[++cnt] = Edge(head[u], v, w), head[u] = cnt;
	e[++cnt] = Edge(head[v], u, 0), head[v] = cnt;
}

inline bool bfs() {
	memset(d, 0, sizeof(d));
	q.push(s), d[s] = 1;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = head[u]; i; i = e[i].nxt) {
			if(e[i].cost && !d[e[i].to]) {
				q.push(e[i].to);
				d[e[i].to] = d[u] + 1;
				if(e[i].to == t) return true;
			}
		}
	}
	return false;
}

int dinic(int x, int flow) {
	if(x == t) return flow;
	int rest = flow, k;
	for(int i = head[x]; i; i = e[i].nxt) {
		if(e[i].cost && d[e[i].to] == d[x] + 1) {
			k = dinic(e[i].to, min(rest, e[i].cost));
			if(!k) d[e[i].to] = 0;
			e[i].cost -= k;
			e[i ^ 1].cost += k;
			rest -= k;
		}
	}
	return flow - rest;
}

int main() {
	read(n), read(m), read(s), read(t);
	for(int i = 1, x, y, z; i <= m; ++i) read(x), read(y), read(z), add(x, y, z);
	int flow = 0;
	while(bfs()) while(flow = dinic(s, INF)) maxflow += flow;
	print(maxflow), putchar('\n');
	return 0;
}
