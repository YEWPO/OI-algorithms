#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

const int MAXN = 1000001;

int n, m, prime[MAXN], v[MAXN];
bool isprime[MAXN];

void primes(int N) {
	int tot = 0;
	for(int i = 1; i <= N; ++i) {
		if(!v[i]) {
			prime[++tot] = v[i] = i;
			isp[i] = true;
		}
		for(int j = 1; j <= tot; ++j) {
			if(prime[j] > v[i] || prime[j] > N / i) break;
			v[i * prime[j]] = prime[j];
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	primes(n);
	for(int i = 1, x; i <= m; ++i) {
		scanf("%d", &x);
		if(isp[x]) puts("Yes");
		else puts("No");
	}
	return 0;
}
