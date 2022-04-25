#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

template <typename T> inline void in(T &a) {
    T num = 0, f = 1;
    char ch = getchar();
    while(!isdigit(ch)) {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(isdigit(ch)) num = (num << 3) + (num << 1) + ch - '0', ch = getchar();
    a = num * f;
}

template <typename T> inline void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

struct Edge {
    int nxt, to;
} e[2000020];
int n, m, s, head[2000020], cnt, pre[2000002][18], dep[2000002];
inline void add(int u, int v) {
    e[++cnt].to = v;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}

void dfs(int u, int fa) {
    for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if(v == fa) continue;
        dep[v] = dep[u] + 1;
        pre[v][0] = u;
        dfs(v, u);
    }
}

int LCA(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    int d = dep[x] - dep[y];
    for(int i = 0; i <= 17; ++i)
        if(d & (1 << i)) x = pre[x][i];
    if(x == y) return x;
    for(int i = 17; i >= 0; --i)
        if(pre[x][i] != pre[y][i]) x = pre[x][i], y = pre[y][i];
    return pre[x][0];
}

int main() {
    in(n), in(m), in(s);
    for(int i = 1; i < n; ++i) {
        int x, y;
        in(x), in(y);
        add(x, y);
        add(y, x);
    }
    dfs(s, 0);
    for(int j = 1; j <= 17; ++j)
        for(int i = 1; i <= n; ++i)
            pre[i][j] = pre[pre[i][j - 1]][j - 1];
    while(m--) {
        int x, y;
        in(x), in(y);
        print(LCA(x, y)), puts("");
    }
    return 0;
}
