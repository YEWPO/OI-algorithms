#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

template <typename T> inline void in(T &a) {
	T ch = getchar(), f = 1;
	for(a = 0; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
	for( ; isdigit(ch); ch = getchar()) a = (a << 3) + (a << 1) + ch - '0';
	a *= f;
}

template <typename T> inline void print(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

queue <int> q;
struct Aho_Corasick_Automaton {
	int ch[2000000][26], val[2000000], nxt[2000000], cnt;
	void ins(char *s) {
		int len = strlen(s), u = 0;
		for(int i = 0; i < len; ++i) {
			int c = s[i] - 'a';
			if(!ch[u][c]) ch[u][c] = ++cnt;
			u = ch[u][c];
		}
		val[u]++;
	}
	void build() {
		for(int i = 0; i < 26; ++i) if(ch[0][i]) nxt[ch[0][i]] = 0, q.push(ch[0][i]);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int i = 0; i < 26; ++i)
				if(ch[u][i]) nxt[ch[u][i]] = ch[nxt[u]][i], q.push(ch[u][i]);
				else ch[u][i] = ch[nxt[u]][i];
		}
	}
	int query(char *s) {
		int len = strlen(s), u = 0, ans = 0;
		for(int i = 0; i < len; ++i) {
			u = ch[u][s[i] - 'a'];
			for(int t = u; t && ~val[t]; t = nxt[t]) ans += val[t], val[t] = -1;
		}
		return ans;
	}
} AC;

int n;
char s[2000000];

signed main() {
	in(n);
	for(int i = 1; i <= n; ++i) scanf("%s", s), AC.ins(s);
	AC.build();
	scanf("%s", s), print(AC.query(s)), puts("");
	return 0;
}
