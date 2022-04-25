#include <bits/stdc++.h>
#define int long long
using namespace std;

template <typename T> inline void read(T &x) {
	T ch = getchar(), f = 1;
	for(x = 0; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for(; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	x *= f;
}

template <typename T> inline void print(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int N, K, dp[10][(1 << 10) + 1][82], sit[(1 << 10) + 1], cnt, num[(1 << 10) + 1], ans;

void Pre() {
	for(int i = 0; i < (1 << N); ++i) {
		if(i & (i << 1) || i & (i >> 1)) continue;
		int sum = 0;
		for(int j = 0; j < N; ++j) if(i & (1 << j)) sum++;
		sit[++cnt] = i;
		num[cnt] = sum;
	}
}

void Dp() {
	for(int i = 1; i <= cnt; ++i) dp[1][i][num[i]] = 1;
	for(int i = 2; i <= N; ++i) {
		for(int j = 1; j <= cnt; ++j) { 
			for(int k = 1; k <= cnt; ++k) { 
				if((sit[j] & sit[k]) || (sit[j] & (sit[k] << 1)) || (sit[j] & (sit[k] >> 1))) continue;
				for(int s = 0; s <= K - num[k]; ++s) dp[i][k][s + num[k]] += dp[i - 1][j][s]; 
			}
		}
	}
	for(int i = 1; i <= cnt; ++i) ans += dp[N][i][K];
}

signed main() {
	read(N), read(K);
	Pre(), Dp();
	print(ans), putchar('\n');
	return 0;
}
/*
2 2 ---- 0
2 1 ---- 4
3 2 ---- 16
*/
