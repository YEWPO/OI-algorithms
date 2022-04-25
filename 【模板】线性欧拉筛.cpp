#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

const int MAXN = 1000001;

int n, prime[MAXN], phi[MAXN], v[MAXN];

void euler(int N) {
	int m = 0;
	for(int i = 2; i <= N; ++i) {
		if(!v[i]) {
			prime[++m] = v[i] = i;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= m; ++j) {
			if(prime[j] > v[i] || prime[j] > N / i) break;
			v[i * prime[j]] = prime[j];
			phi[i * prime[j]] = phi[i] * ((i % prime[j]) ? (prime[j] - 1) : prime[j]);
		}
	}
	return;
}

int main() {
	scanf("%d", &n);
	euler(n);
}
