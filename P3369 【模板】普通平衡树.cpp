#include <bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;

const int MAXN = 100001;

inline void read(int &x) {
	int c = getchar(), f = 1;
	for(x = 0; !isdigit(c); c = getchar()) (c == '-') && (f = -1);
	for(; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + c - '0';
	x *= f;
}

inline void print(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

int n, data[MAXN], L[MAXN], R[MAXN], s[MAXN], rt, num;

inline void Zig(int &x) {
	int y = R[x];
	R[x] = L[y];
	L[y] = x;
	s[y] = s[x];
	s[x] = s[L[x]] + s[R[x]] + 1;
	x = y;
}

inline void Zag(int &x) {
	int y = L[x];
	L[x] = R[y];
	R[y] = x;
	s[y] = s[x];
	s[x] = s[L[x]] + s[R[x]] + 1;
	x = y;
}

void Maintain(int &x, bool w) {
	if(!w) {
		if(s[L[L[x]]] > s[R[x]]) Zag(x);
		else if(s[R[L[x]]] > s[R[x]]) Zig(L[x]), Zag(x);
		else return;
	} else {
		if(s[R[R[x]]] > s[L[x]]) Zig(x);
		else if(s[L[R[x]]] > s[L[x]]) Zag(R[x]), Zig(x);
		else return;
	}
	Maintain(L[x], 0), Maintain(R[x], 1), Maintain(x, 0), Maintain(x, 1);
}

void Insert(int &x, int w) {
	if(!x) {
		x = ++num;
		data[x] = w;
		s[x] = 1;
		L[x] = R[x] = 0;
	} else {
		s[x]++;
		if(w < data[x]) Insert(L[x], w);
		else Insert(R[x], w);
		Maintain(x, w >= data[x]);
	}
}

int Delete(int &x, int w) {
	s[x]--;
	int tmp;
	if(w == data[x] || (w < data[x] && !L[x]) || (w > data[x] && !R[x])) {
		tmp = data[x];
		if(!L[x] || !R[x]) x = L[x] + R[x];
		else data[x] = Delete(L[x], data[x] + 1);
		return tmp;
	} else {
		if(w < data[x]) tmp = Delete(L[x], w);
		else tmp = Delete(R[x], w);
		return tmp;
	}
}

int GetRankByVal(int &x, int w) {
	if(!x) return 1;
	int tmp;
	if(w <= data[x]) tmp = GetRankByVal(L[x], w);
	else tmp = s[L[x]] + 1 + GetRankByVal(R[x], w);
	return tmp;
}

int GetValByRank(int &x, int w) {
	if(w == s[L[x]] + 1) return data[x];
	else if(w < s[L[x]] + 1) return GetValByRank(L[x], w);
	else return GetValByRank(R[x], w - s[L[x]] - 1);
}

int GetPre(int &x, int w) {
	if(!x) return w;
	int tmp;
	if(w <= data[x]) tmp = GetPre(L[x], w);
	else {
		tmp = GetPre(R[x], w);
		if(tmp == w) tmp = data[x];
	}
	return tmp;
}

int GetNext(int &x, int w) {
	if(!x) return w;
	int tmp;
	if(w >= data[x]) tmp = GetNext(R[x], w);
	else {
		tmp = GetNext(L[x], w);
		if(tmp == w) tmp = data[x];
	}
	return tmp;
}

int main() {
	read(n);
	for(int i = 1, opt, x; i <= n; ++i) {
		read(opt), read(x);
		switch(opt) {
			case 1: Insert(rt, x); break;
			case 2: Delete(rt, x); break;
			case 3: print(GetRankByVal(rt, x)), putchar('\n'); break;
			case 4: print(GetValByRank(rt, x)), putchar('\n'); break;
			case 5: print(GetPre(rt, x)), putchar('\n'); break;
			case 6: print(GetNext(rt, x)), putchar('\n'); break;
		}
	}
	return 0;
}
