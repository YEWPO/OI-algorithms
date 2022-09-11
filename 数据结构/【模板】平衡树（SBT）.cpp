#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100001;

inline int read() {
	int num = 0, f = 1;
	char ch;
	for(; !isdigit(ch); ch = getchar()) (ch == '-') && (f = -1);
	for(; isdigit(ch); ch = getchar()) num = (num << 3) + (num << 1) + ch - '0';
	return num * f;
}

inline void print(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int data[MAXN], L[MAXN], R[MAXN], s[MAXN], num = 0, n;

inline void zig(int &x) {
	int y = R[x];
	R[x] = L[y];
	L[y] = x;
	s[y] = s[x];
	s[x] = s[L[x]] + s[R[x]] + 1;
	x = y;
}

inline void zag(int &x) {
	int y = L[x];
	L[x] = R[y];
	R[y] = x;
	s[y] = s[x];
	s[x] = s[R[x]] + s[L[x]] + 1;
	x = y;
}

void maintain(int &x, bool w) {
	if(!w) {
		if(s[L[L[x]]] > s[R[x]]) zag(x);
		else if(s[R[L[x]]] > s[R[x]]) zig(L[x]), zag(x);
		else return;
	} else {
		if(s[R[R[x]]] > s[L[x]]) zig(x);
		else if(s[L[R[x]]] > s[L[x]]) zag(R[x]), zig(x);
		else return;
	}
	maintain(L[x], 0), maintain(R[x], 1), maintain(x, 0), maintain(x, 1);
}

void insert(int &x, int w) {
	if(!x) {
		x = ++num;
		data[x] = w;
		s[x] = 1;
		L[x] = R[x] = 0;
	} else {
		s[x]++;
		if(w < data[x]) insert(L[x], w);
		else insert(R[x], w);
		maintain(x, w >= data[x]);
	}
}

int remove(int &x, int w) {
	s[x]--;
	int tmp;
	if(data[x] == w || (w < data[x] && !L[x]) || (w > data[x] && !R[x])) {
		tmp = data[x];
		if(!L[x] || !R[x]) x = L[x] + R[x];
		else data[x] = remove(L[x], data[x] + 1);
		return tmp;
	} else {
		if(w < data[x]) tmp = remove(L[x], w);
		else tmp = remove(R[x], w);
		return tmp;
	}
}

int select(int &x, int w) {
	if(w == s[L[x]] + 1) return data[x];
	if(w < s[L[x]] + 1) return select(L[x], w);
	else return select(R[x], w - s[L[x]] - 1);
}

int rank(int &x, int w) {
	if(!x) return 1;
	int tmp;
	if(w <= data[x]) tmp = rank(L[x], w);
	else tmp = s[L[x]] + 1 + rank(R[x], w);
	return tmp;
}

int pre(int &x, int w) {
	if(!x) return w;
	int tmp;
	if(w <= data[x]) tmp = pre(L[x], w);
	else {
		tmp = pre(R[x], w);
		if(tmp == w) tmp = data[x];
	}
	return tmp;
}

int nxt(int &x, int w) {
	if(!x) return w;
	int tmp;
	if(w >= data[x]) tmp = nxt(R[x], w);
	else {
		tmp = nxt(L[x], w);
		if(tmp == w) tmp = data[x];
	}
	return tmp;
}

int main() {
	n = read();
	int rt = 0;
	for(int i = 1; i <= n; ++i) {
		int opt = read(), x = read();
		if(opt == 1) insert(rt, x);
		else if(opt == 2) remove(rt, x);
		else if(opt == 3) print(rank(rt, x)), putchar('\n');
		else if(opt == 4) print(select(rt, x)), putchar('\n');
		else if(opt == 5) print(pre(rt, x)), putchar('\n');
		else print(nxt(rt, x)), putchar('\n');
	}
	return 0;
}
