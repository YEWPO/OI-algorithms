#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define mod 100000000
using namespace std;

typedef long long LL;

template <typename T> inline void read(T &x) {
	T ch = getchar(), f = 1;
	for(x = 0; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for(; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
	x *= f;
}

template <typename T> inline void print(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, m, Map[13][13], state[13][(1 << 12) + 1], cnt[13], No[13];
LL ans, dp[13][(1 << 12) + 1];

void Pre() {
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < (1 << m); ++j) {
			if(j & (j << 1) || j & (j >> 1) || j & No[i]) continue;
			state[i][++cnt[i]] = j;
		}
	}
}

void Dp() {
	for(int i = 1; i <= cnt[1]; ++i) dp[1][i] = 1;
	for(int i = 2; i <= n; ++i) {
		for(int j = 1; j <= cnt[i]; ++j) {
			for(int k = 1; k <= cnt[i - 1]; ++k) {
				if(state[i][j] & state[i - 1][k]) continue;
				dp[i][j] += dp[i - 1][k];
				dp[i][j] %= mod;
			}
		}
	}
	for(int i = 1; i <= cnt[n]; ++i) ans += dp[n][i], ans %= mod;
}

int main() {
	read(n), read(m);
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) read(Map[i][j]);
		for(int j = m; j; --j) No[i] += ((Map[i][j] ^ 1) * (1 << (m - j)));
	}
	Pre(), Dp();
	print(ans), putchar('\n');
	return 0;
}
