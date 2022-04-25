#include <bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;

const int MAXN = 1001;

template <typename T> inline void read(T &x) {
	char c = getchar();
	bool f = false;
	for(x = 0; !isdigit(c); c = getchar()) (c == '-') && (f = true);
	for(; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	if(f) x = -x;
}

template <typename T> inline void print(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, m, e, match[MAXN], ans;
vector <int> a[MAXN];
bool vis[MAXN];

bool dfs(int x) {
	for(int i = 0, y; i < a[x].size(); ++i) {
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
	read(n), read(m), read(e);
	for(int i = 1, u, v; i <= e; ++i) {
		read(u), read(v);
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
