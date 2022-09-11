#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL n, m, p;

LL qpow(LL a, LL b) {
	LL ret = 1;
	while(b) {
		if(b & 1) ret = ret * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ret;
}

LL C(LL a, LL b) {
	if(a < b) return 0;
	LL ret = 1;
	for(int i = 1; i <= b; ++i) 
		ret = ret * (a - b + i) % p * qpow(i, p - 2) % p;
	return ret;
}

LL Lucas(LL a, LL b){
	if(!b) return 1;
	return (Lucas(a / p, b / p) * C(a % p, b % p)) % p;
}

int main() {
	int T;
	cin >> T;
	while(T--) {
		cin >> n >> m >> p;
		cout << Lucas(n + m, m) << endl;
	}
}
