#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
#include <queue>
using namespace std;

const int mod = 10007;
int fac[mod + 3], inv[mod + 3];

void init() {
	fac[0] = 1;
	for(int i = 1; i < mod; ++i) fac[i] = (long long) fac[i - 1] * i % mod;
	inv[0] = inv[1] = 1;
	for(int i = 2; i < mod; ++i) inv[i] = (long long) (mod - mod / i) * inv[mod % i] % mod;
	for(int i = 1; i < mod; ++i) inv[i] = (long long) inv[i] * inv[i - 1] % mod;
}

int C(int a, int b) {
	if(a < b) return 0;
	if(a < mod) return (long long) fac[a] * inv[b] % mod * inv[a - b] % mod;
	return (long long) C(a / mod, b / mod) * C(a % mod, b % mod) % mod;
}

int main() {
	init();
	int n, m;
	scanf("%d %d", &n, &m);
	printf("%d\n", C(n + m, m));
	return 0;
}
