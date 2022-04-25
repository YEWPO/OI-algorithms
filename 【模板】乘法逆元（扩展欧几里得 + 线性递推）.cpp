#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef long long LL;

void exgcd(LL a, LL b, LL &d, LL &x, LL &y) {
	if(!b) d = a, x = 1, y = 0;
	else exgcd(b, a % b, d, y, x), y -= x * (a / b);
}

LL Inv(LL a, LL p) {
	LL d, x, y;
	exgcd(a, p, d, x, y);
	return d == 1 ? (x + p) % p : -1;
}

LL inv[1000001];

int main() {
	LL n, p;
	scanf("%lld %lld", &n, &p);
	for(int i = 1; i <= n; ++i) printf("%lld\n", Inv(i, p));
	inv[1] = 1;
	for(int i = 2; i <= n; ++i) inv[i] = (p - p / i) * inv[p % i] % p;
}
