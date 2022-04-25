#include <bits/stdc++.h>
using namespace std;

char s1[1000001], s2[1000001], nxt[1000001];

void get_fail(char *s) {
	int len = strlen(s);
	for(int i = 1, j = 0; i < len; ++i) {
		while(j && s[i] != s[j]) j = nxt[j];
		nxt[i + 1] = s[i] == s[j] ? ++j : 0;
	}
}

int main() {
	scanf("%s %s", s1, s2);
	get_fail(s2);
	int len1 = strlen(s1), len2 = strlen(s2);
	for(int i = 0, j = 0; i < len1; ++i) {
		while(j && s1[i] != s2[j]) j = nxt[j];
		if(s1[i] == s2[j]) j++;
		if(j == len2) {
			printf("%d\n", i - j + 2);
			j = nxt[j];
		}
	}
	for(int i = 1; i <= len2; ++i) printf("%d ", nxt[i]);
	return 0;
}
