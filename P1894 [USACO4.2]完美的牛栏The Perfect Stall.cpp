#include <bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;

const int MAXN = 201;

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

int n, m, match[MAXN], ans;
vector <int> a[MAXN];
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
	read(n), read(m);
	for(int i = 1, s; i <= n; ++i) {
		read(s);
		for(int j = 1, x; j <= s; ++j) {
			read(x);
			a[i].push_back(x);
		}
	}
	for(int i = 1; i <= n; ++i) {
		memset(vis, 0, sizeof(vis));
		if(dfs(i)) ans++;
	}
	print(ans), putchar('\n');
	return 0;
}
