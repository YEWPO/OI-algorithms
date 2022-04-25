#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

const int MAXL = 1000001;

int i, j, nxt[MAXL];
char s[MAXL], s2[MAXL];

inline void pre(char *s) {
	int len = strlen(s);
	for(i = 1, j = 0; i < len; ++i) {
		while(j && s[i] != s[j]) j = nxt[j];
		nxt[i + 1] = s[i] == s[j] ? ++j : 0;
	}
}

int main() {
	scanf("%s %s", s, s2);
	pre(s2);
	int n = strlen(s), m = strlen(s2);
	j = 0;
	for(i = 0; i < n; ++i) {
		while(j && s2[j] != s[i]) j = nxt[j];
		if(s2[j] == s[i]) ++j;
		if(j == m) {
			printf("%d\n", i - j + 2);
			j = nxt[j];
		}
	}
	return 0;
}
