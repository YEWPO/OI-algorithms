#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3000001;

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

int d, x, y;

void exgcd(int a, int b, int &d, int &x, int &y) {
	if(!b) d = a, x = 1, y = 0;
	else exgcd(b. a % b, d, y, x), y -= x * (a / b);
}

int Inv(int a, int p) {
	int d, x, y;
	exgcd(a, p, d, x, y);
	return d == 1 ? (x + p) % p : -1;
}

int n, p, inv[MAXN];

int main() {
	read(n), read(p);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i) inv[i] = (p - p / i) * inv[p % i] % p;
	for(int i = 1; i <= n; ++i) print(inv[i]), putchar('\n');
	return 0;
}
