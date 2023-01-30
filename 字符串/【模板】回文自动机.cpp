#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
typedef long long ll;

int n;
char s[N];

int tot(-1), pre, pam[N][30], fail[N], len[N];

ll ans, cnt[N];

inline int build(int l) {
	len[++tot] = l;
	return tot;
}

inline int getFail(int pos, int x) {
	while (s[pos - len[x] - 1] != s[pos]) {
		x = fail[x];
	}
	return x;
}

inline void insert(int pos, char ch) {
	int val = ch - 'a';
	
	int now = getFail(pos, pre);
	
	if (!pam[now][val]) {
		int newNode = build(len[now] + 2);
		fail[newNode] = pam[getFail(pos, fail[now])][val];
		pam[now][val] = newNode;
	}
	
	pre = pam[now][val];
	cnt[pre]++;
}

int main() {
	build(0);
	build(-1);
	fail[0] = 1;
	
	scanf("%s", s + 1);
	n = strlen(s + 1);
		
	for (int i = 1; i <= n; ++i) {
		insert(i, s[i]);
	}
	
	for (int i = tot; i; --i) {
		cnt[fail[i]] += cnt[i];
		ans = max(ans, cnt[i] * len[i]);
	}
	
	printf("%lld", ans);
	
	return 0;
}
