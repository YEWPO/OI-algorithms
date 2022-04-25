#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;

const int MaxN = 100001;
const int MaxM = 200001;
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

int n, m, s, head[MaxN], cnt, dis[MaxN];
bool vis[MaxN];
struct Edge {
	int nxt, to, cost;
	Edge() {}
	Edge(int _nxt, int _to, int _cost) : nxt(_nxt), to(_to), cost(_cost) {}
} e[MaxM << 1];
queue <int> q;

inline void add(int u, int v, int w) {
	e[++cnt] = Edge(head[u], v, w), head[u] = cnt;
}

signed main() {
	read(n), read(m), read(s);
	for(int i = 1, x, y, z; i <= m; ++i) read(x), read(y), read(z), add(x, y, z);
	for(int i = 1; i <= n; ++i) dis[i] = INF;
	dis[s] = 0, q.push(s);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for(int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if(dis[v] > dis[u] + e[i].cost) {
				dis[v] = dis[u] + e[i].cost;
				if(!vis[v]) vis[v] = 1, q.push(v);
			}
		}
	}
	for(int i = 1; i <= n; ++i) print(dis[i]), putchar(' ');
	putchar('\n');
	return 0;
}
