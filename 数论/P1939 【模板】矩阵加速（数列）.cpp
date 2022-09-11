#include <bits/stdc++.h>
#pragma GCC optimize(3)
#define mod 1000000007
using namespace std;

typedef unsigned long long ULL;

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

struct Square {
	ULL num[5][5];
	Square() {memset(num, 0, sizeof(num));}
	inline Square operator * (const Square &x) const {
		Square ret;
		for(int i = 1; i <= 4; ++i)
			for(int j = 1; j <= 4; ++j)
				for(int k = 1; k <= 4; ++k)
					ret.num[i][j] += num[i][k] * x.num[k][j], ret.num[i][j] %= mod;
		return ret;
	}
} Origin, Basic;

inline Square power(Square x, int y) {
	Square ret = Origin;
	while(y) {
		if(y & 1) ret = ret * x;
		x = x * x;		
		y >>= 1;
	}
	return ret;
}

int main() {
	int T, n;
	read(T);
	Origin.num[1][1] = 1;
	Origin.num[1][3] = 1;
	Origin.num[2][1] = 1;
	Origin.num[3][2] = 1;
	Origin.num[4][3] = 1;
	Basic.num[1][1] = 2;
	Basic.num[2][1] = 1;
	Basic.num[3][1] = 1;
	Basic.num[4][1] = 1;
	while(T--) {
		read(n);
		Square ans = Basic * power(Origin, n - 2);
		print(ans.num[2][1]), putchar('\n');
	}
	return 0;
}
