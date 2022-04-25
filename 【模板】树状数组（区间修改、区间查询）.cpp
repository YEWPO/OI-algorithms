#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <functional>
#pragma GCC optimize(3)
#include <queue>
#define lowbit(x) x & -x
#define int long long
using namespace std;

const int MAXN = 1000001;

template <typename T> inline void read(T &x) {
	char c = getchar();
	bool f = false;
	for(x = 0; !isdigit(c); c = getchar()) {
		if(c == '-') {
			f = true;
		}
	}
	for(; isdigit(c); c = getchar()) {
		x = (x << 3) + (x << 1) + c - '0';
	}
	if(f) {
		x = -x;
	}
}

template <typename T> inline void print(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

long long c[MAXN], ci[MAXN];
int n, m, r;
long long a[MAXN], sum[MAXN];

void Modify(long long *Array, int x, long long val) {
	for(; x <= n; x += lowbit(x)) Array[x] += val;
}

long long Query(long long *Array, int x) {
	long long ret = 0;
	for(; x; x -= lowbit(x)) ret += Array[x];
	return ret;
}

signed main() {
	read(n), read(m);
	for(int i = 1; i <= n; ++i) read(a[i]), sum[i] = sum[i - 1] + a[i];
	for(int i = 1, opt, x, L, R; i <= m; ++i) {
		read(opt), read(L), read(R);
		if(opt == 1) {
			read(x);
			Modify(c, L, x), Modify(c, R + 1, -x);
			Modify(ci, L, x * L), Modify(ci, R + 1, -x * (R + 1));
		}
		else {
			long long suml =  L * Query(c, L - 1) - Query(ci, L - 1);
			long long sumr = (R + 1) * Query(c, R) - Query(ci, R);
			print(sum[R] - sum[L - 1] + sumr - suml), putchar('\n');
		}
	} 
	return 0;
}

