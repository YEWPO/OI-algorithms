#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

void exgcd(LL a, LL b, LL &d, LL &x, LL &y) {
	if(!b) d = a, x = 1, y = 0;
	else exgcd(b, a % b, d, y, x), y -= x * (a / b);
}

int main() {
	LL a, b, d, x, y;
	cin >> a >> b;
	exgcd(a, b, d, x, y);
	x /= d, y /= d, a /= d, b /= d;
	while(x < 0) {
		x += b;
		y += a;
	}
	cout << x << endl;
	return 0;
}
