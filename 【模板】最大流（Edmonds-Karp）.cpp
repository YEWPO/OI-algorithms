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
int n, m, s, t, head[MAXN], cnt = 1, maxflow, incf[MAXN], pre[MAXN];
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
	memset(vis, 0, sizeof(vis));
	q.push(s), vis[s] = 1;
	incf[s] = INF;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int i = head[u]; i; i = e[i].nxt) {
			if(e[i].cost) {
				int v = e[i].to;
				if(vis[v]) continue;
				incf[v] = min(incf[u], e[i].cost);
				pre[v] = i;
				q.push(v), vis[v] = 1;
				if(v == t) return true;
			}
		}
	}
	return false;
}

void update() {
	int x = t;
	while(x != s) {
		int i = pre[x];
		e[i].cost -= incf[t];
		e[i ^ 1].cost += incf[t];
		x = e[i ^ 1].to;
	}
	maxflow += incf[x];
}

int main() {
	read(n), read(m);
	for(int i = 1, x, y, z; i <= m; ++i) read(x), read(y), read(z), add(x, y, z);
	s = 1, t = n;
	while(bfs()) update();
	print(maxflow), putchar('\n');
	return 0;
}
