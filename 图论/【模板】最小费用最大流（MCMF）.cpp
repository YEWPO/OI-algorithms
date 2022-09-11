#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int N = 5010, M = 200010;
int ver[M], edge[M], cost[M], Next[M], head[N];
int d[N], incf[N], pre[N], v[N];
int n, k, tot, s, t, maxflow, ans;

void add(int x, int y, int z, int c) {
	ver[++tot] = y, edge[tot] = z, cost[tot] = c;
	Next[tot] = head[x], head[x] = tot;
	ver[++tot] = x, edge[tot] = 0, cost[tot] = -c;
	Next[tot] = head[y], head[y] = tot;
}

int num(int i, int j, int k) {
	return (i - 1) * n + j + k * n * n;
}

bool spfa() {
	queue <int> q;
	memset(d, 0x3f, sizeof(d));
	memset(v, 0, sizeof(v));
	q.push(s);
	d[s] = 0;
	v[s] = 1;
	incf[s] = 1 << 30;
	while (q.size()) {
		int x = q.front();
		v[x] = 0;
		q.pop();
		for (int i = head[x]; i; i = Next[i]) {
			if (!edge[i]) continue;
			int y = ver[i];
			if (d[y] < d[x] + cost[i]) {
				d[y] = d[x] + cost[i];
				incf[y] = min(incf[x], edge[i]);
				pre[y] = i;
				if (!v[y]) v[y] = 1, q.push(y);
			}
		}
	}
	if (d[t] == 0x3f3f3f3f) return false;
	return true;
}


void update() {
	int x = t;
	while (x != s) {
		int i = pre[x];
		edge[i] -= incf[t];
		edge[i ^ 1] += incf[t];
		x = ver[i ^ 1];
	}
	maxflow += incf[t];
	ans += d[t] * incf[t];
}

int main() {
	cin >> n >> k;
	s = 1, t = 2 * n * n;
	tot = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			int c;
			scanf("%d", &c);
			add(num(i, j, 0), num(i, j, 1), 1, c);
			add(num(i, j, 0), num(i, j, 1), k - 1, 0);
			if (j < n) add(num(i, j, 1), num(i, j + 1, 0), k, 0);
			if (i < n) add(num(i, j, 1), num(i + 1, j, 0), k, 0);
		}
	while (spfa()) update();
	cout << ans << endl;
}
