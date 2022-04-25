#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef long long LL;

LL m, n, p;

LL power(LL a, LL b, LL mod) {
	LL ret = 1;
	while(b) {
		if(b & 1) ret *= a, ret %= mod;
		b >>= 1;
		a = a * a % mod;
	}
	return ret;
}

LL C(LL a, LL b) {
	if(a < b) return 0;
	LL ret = 1;
	for(int i = 1; i <= b; i++)
		ret = ret * (a - b + i) % p * power(i, p - 2, p) % p;
	return ret;
}

LL Lucas(LL a,LL b) {
	if(!b) return 1;
	return (Lucas(a / p, b / p) * C(a % p, b % p)) % p;
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%lld %lld %lld", &n, &m, &p);
		printf("%lld\n", Lucas(n + m, m));
	}
	return 0;
}
