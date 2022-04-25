#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

const int N = 105;

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

int n, m, w[N][N], match[N], delta;
int la[N], lb[N];
bool va[N], vb[N];

bool dfs(int x) {
	va[x] = 1;
	for(int y = 1; y <= n; ++y) {
		if(!vb[y]) {
			if(la[x] + lb[y] - w[x][y]) delta = min(delta, la[x] + lb[y] - w[x][y]);
			else {
				vb[y] = 1;
				if(!match[y] || dfs(match[y])) {
					match[y] = x;
					return true;
				}
			}
		}
	}
	return false;
}

int KM() {
	for(int i = 1; i <= n; ++i) {
		la[i] = -(1 << 30);
		lb[i] = 0;
		for(int j = 1; j <= n; ++j) la[i] = max(la[i], w[i][j]);
	}
	for(int i = 1; i <= n; ++i)
		while(true) {
			memset(va, 0, sizeof(va));
			memset(vb, 0, sizeof(vb));
			delta = 1 << 30;
			if(dfs(i)) break;
			for(int j = 1; j <= n; ++j) {
				if(va[j]) la[j] -= delta;
				if(vb[j]) lb[j] += delta;
			}
		}
	int ans = 0;
	for(int i = 1; i <= n; ++i) ans += w[match[i]][i];
	return ans;
}

int main() {
	
	return 0;
}
