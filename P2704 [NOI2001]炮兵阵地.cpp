#include <bits/stdc++.h>
using namespace std;

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

int n, m, No[101], Map[101][11], state[101][(1 << 10) + 1], cnt[101];
char s[11];
long long ans, dp[101][(1 << 10) + 1][1001], num[101][(1 << 10) + 1];

void scan(char *s) {
	int x = 0;
	while((s[++x] = getchar()) != '\n' && s[x] != '\377');
	return;
}

void Pre() {
	for(int k = 1; k <= n; ++k)
		for(int i = 0; i < (1 << m); ++i) {
			if(i & (i << 1) || i & (i >> 1) || i & (i << 2) || i & (i >> 2) || i & No[k]) continue;
			state[k][++cnt[k]] = i;
			int sum = 0;
			for(int j = 0; j < m; ++j) if(i & (1 << j)) sum++;
			num[k][cnt[k]] = sum;
		}
}

void Dp() {
	cnt[0] = 1;
	for(int i = 1; i <= cnt[1]; ++i) dp[1][i][1] = num[1][i], ans = max(ans, num[1][i]);
	for(int i = 2; i <= n; ++i) {
		for(int j = 1; j <= cnt[i]; ++j) {
			for(int k = 1; k <= cnt[i - 1]; ++k) {
				for(int l = 1; l <= cnt[i - 2]; ++l) {
					if(state[i][j] & state[i - 1][k] || state[i][j] & state[i - 2][l] || state[i - 1][k] & state[i - 2][l]) continue;
					dp[i][j][k] = max(dp[i - 1][k][l] + num[i][j], dp[i][j][k]);
					ans = max(ans, dp[i][j][k]);
				}
			}
		}
	}
}

int main() {
	read(n), read(m);
	for(int i = 1; i <= n; ++i) {
		scan(s);
		for(int j = 1; j <= m; ++j) 
			Map[i][j] = s[j] == 'P' ? 0 : 1;
		for(int j = m; j; --j)
			No[i] += (1 << (m - j)) * Map[i][j];
	}
	Pre(), Dp();
	print(ans), putchar('\n');
	return 0;
}
