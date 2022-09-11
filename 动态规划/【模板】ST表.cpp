#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MaxN = 100001;
const int LogN = 21;

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

int log[MaxN], f[MaxN][LogN], z[MaxN][LogN], a[MaxN], n, m;

int main() {
	read(n), read(m);
	log[0] = -1;
	for(int i = 1; i <= n; ++i)	read(a[i]), log[i] = log[i >> 1] + 1, f[i][0] = z[i][0] = a[i];
	for(int j = 1; j <= LogN; ++j)
		for(int i = 1; i + (1 << j) - 1 <= n; ++i) {
			f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
			z[i][j] = min(z[i][j - 1], z[i + (1 << (j - 1))][j - 1]);
		}
	for(int i = 1, l, r, s; i <= m; ++i) {
		read(l), read(r), s = log[r - l + 1];
		prnti(max(f[l][s], f[r - (1 << s) + 1][s])), putchar(' ');
		print(min(z[l][s], z[r - (1 << s) + 1][s])), putchar('\n');
	}
	return 0;
}
