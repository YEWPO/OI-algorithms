#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 1001;

inline int read() {
	int x = 0, f = 1, ch;
	for(; !isdigit(ch); ch = getchar()) (ch == '-') && (f = -1);
	for(; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
	return x * f;
}

inline void print(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, m, e, match[MAXN], ans;
vector <int> a[1001];
bool vis[MAXN];

bool dfs(int x) {
	for(unsigned i = 0, y; i < a[x].size(); ++i) {
		if(!vis[y = a[x][i]]) {
			vis[y] = 1;
			if(!match[y] || dfs(match[y])) {
				match[y] = x;
				return true;
			}
		}
	}
	return false;
}

int main() {
	n = read(), m = read(), e = read();
	for(int i = 1, u, v; i <= e; ++i) {
		u = read(), v = read();
		if(v > m) continue;
		a[u].push_back(v);
	}
	for(int i = 1; i <= n; ++i) {
		memset(vis, 0, sizeof(vis));
		if(dfs(i)) ans++;
	}
	print(ans), putchar('\n');
	return 0;
}
