#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <functional>
#define DBG printf("problems are here!!!!!\n");

const int MAXN = 100100;
const int MAXE = 400400;
const int INF = 0x3f3f3f3f;

using std::min;
using std::max;
using std::queue;

template<class T>void read(T &x) {
	x = 0;
	int f = 0;
	int ch = getchar();
	while(ch < '0' || ch > '9') {
		f |= (ch == '-');
		ch = getchar();
	}
	while(ch >=  '0'&&ch <= '9') {
		x = x * 10+(ch^48);
		ch = getchar();
	}
	x = f?-x:x;
	return;
}

struct Edge {
	int to, nxt, flow;
	Edge() {}
	Edge(int _to, int _nxt, int _flow) : to(_to), nxt(_nxt), flow(_flow) {}
} E[MAXE];

int h[MAXN], cur[MAXN], pre[MAXN], vis[MAXN], p;
int num[MAXN], d[MAXN], source, sink;
int tot, n, m;
queue<int>q;

inline void add_edge(int x, int y, int flow) {
	E[p] = Edge(y, h[x], flow), h[x] = p++;
	E[p] = Edge(x, h[y], 0), h[y] = p++;
}

void bfs() {
	memset(vis, 0, sizeof(vis));
	d[sink] = 0, vis[sink] = 1;
	q.push(sink);
	while(!q.empty()) {
		int u = q.front();
		num[d[u]]++;
		q.pop();
		for(int i = h[u]; ~i; i = E[i].nxt) {
			int v = E[i].to;
			if(!vis[v]) {
				vis[v] = 1;
				d[v] = d[u] + 1;
				q.push(v);
			}
		}
	}
}

void augment(int flow) {
	for(int i = source; i != sink; i = E[cur[i]].to) {
		E[cur[i]].flow -= flow;
		E[cur[i] ^ 1].flow += flow;
	}
}

int isap() {
	memset(num, 0, sizeof(num));
	bfs();
	memcpy(cur, h, sizeof(h));
	int u = source, f = INF, flow = 0;
	while(d[source] < tot) {
		bool fg = 0;
		for(int i = cur[u]; ~i; i = E[i].nxt) {
			int v = E[i].to;
			if(E[i].flow > 0&& d[u] == d[v] + 1) {
				cur[u] = i;
				pre[v] = u;
				u = v;
				fg = 1;
				f = min(f, E[i].flow);
				if(u == sink) {
					flow += f;
					augment(f);
					f = INF;
					u = source;
				}
				break;
			}
		}
		if(fg) continue;
		if(--num[d[u]] == 0) break;
		int M = tot - 1;
		for(int i = h[u]; ~i; i = E[i].nxt) {
			int v = E[i].to;
			if(E[i].flow > 0&& d[v] < M) {
				M = d[v];
				cur[u] = i;
			}
		}
		num[d[u] = M + 1]++;
		if(u != source) u = pre[u];
	}
	return flow;
}

signed main() {
	memset(h, -1, sizeof(h));
	read(n), read(m);
	read(source), read(sink);
	tot = n;
	for(int i = 1, a, b, c; i <= m; i++) {
		read(a), read(b), read(c);
		add_edge(a, b, c);
	}
	printf("%d\n", isap());
	return 0;
}
