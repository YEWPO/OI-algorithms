#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <functional>
#include <map>
using namespace std;

typedef long long LL;

LL a, b, p, d;

LL power(LL a, LL b, LL p) {
	LL ret = 1;
	while(b) {
		if(b & 1) ret = ret * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ret;
} //求 a ^ b % p

LL gcd(LL a, LL b) {
	if(!b) return a;
	return gcd(b, a % b);
} //求 gcd(a, b)

void Exgcd(LL a, LL b, LL &d, LL &x, LL &y) {
	if(!b) d = a, x = 1, y = 0;
	else Exgcd(b, a % b, d, y, x), y -= x * (a / b);
} //求 Ax + By = C 的整数解

void Solve(LL a, LL b, LL p) {
	LL x, y;
	Exgcd(a, p, d, x, y);
	if(b % d) puts("No solution");
	else printf("%lld\n", (x * (b / d) % (p / d) + (p / d)) % (p / d));
} // 求解线性同余方程 a * x + p * y = b

map <LL, LL> Map;

LL BSGS(LL A, LL B, LL C) {
	if(A == 0 && B == 0) {
		return 1;
	}
	Map.clear();
	LL m = (LL) ceil(sqrt((double) C));
	LL con = B % C, D = 1;
	Map[B % C] = 0;
	for(LL i = 1; i <= m; ++i) {
		con = con * A % C;
		Map[con] = i;
	}
	con = power(A, m, C);
	for(LL i = 1; i <= m; ++i) {
		D = D * con % C;
		if(Map[D]) {
			LL t = i * m - Map[D];
			return (t % C + C) % C;
		}
	}
	return 0;
} // 求解高次同余方程 a ^ x + p * y = b

int main() {

	return 0;
}
