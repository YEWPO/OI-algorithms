#include <bits/stdc++.h>
using namespace std;

int main() {
	int T, n, x, flag;
	cin >> T;
	while(T--) {
		cin >> n >> x;
		flag = x;
		for(int i = 2; i <= n; ++i) cin >> x, flag ^= x;
		if(!flag) puts("No");
		else puts("Yes");
	}
	return 0;
}
