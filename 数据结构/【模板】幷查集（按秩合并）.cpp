#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

const int MAXN = 100001;

int fa[MAXN], rank[MAXN];

int Get_fa(int x) {
	return x == fa[x] ? x : fa[x] = Get_fa(fa[x]);
}

inline void Merge(int x, int y) {
	int t1 = Get_fa(x), t2 = Get_fa(y);
	if(rank[t1] < rank[t2]) fa[t2] = t1;
	else {
		fa[t1] = t2;
		if(rank[t1] == rank[t2]) rank[t1]++;
	}
	return;
}

inline void Judge(int x, int y) {
	if(Get_fa(x) == Get_fa(y)) puts("Yes");
	else puts("No");
	return;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int i = 1, opt, x, y; i <= n; ++i) {
		scanf("%d %d %d", &opt, &x, &y);
		if(opt == 1) Merge(x, y);
		else Judge(x, y);
	}
	return 0;
}
