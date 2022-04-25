#include <bits/stdc++.h>
using namespace std;

template<typename T>
inline void read(T &x) {
    T s = 0, w = 1;

    char ch = cin.get();

    while (!isdigit(ch)) {
        if (ch == '-') {
            w = -w;
        }

        ch = cin.get();
    }

    while (isdigit(ch)) {
        s = (s << 1) + (s << 3) + ch - '0';
        ch = cin.get();
    }

    x = s;

    return;
}

template<typename T>
inline void write(T x) {
    if (x < 0) {
        cout.put('-');
        x = -x;
    }

    if (x > 9) {
        write(x / 10);
    }

    cout.put(x % 10 + '0');

    return;
}

const int SIZE = 1e6 + 100;
const int N = 1010;

struct Edge {
    int u, v;
    int next;
}edge[SIZE];
int head[N], tot = 1;

void addEdge(int u, int v) {
    edge[++tot].u = u;
    edge[tot].v = v;
    edge[tot].next = head[u];
    head[u] = tot;
    return;
}

int n, m;
int ansDot, ansEdge, ansDcc, ansDe;

bool cutEdge[SIZE], cutDot[N];
int dfn[N], low[N];
int cnt;

void tarjanDot(int u, int fa) {
    dfn[u] = low[u] = ++cnt;
    int child = 0;

    for (int e = head[u]; e; e = edge[e].next) {
        int v = edge[e].v;

        if (!dfn[v]) {
            child++;
            tarjanDot(v, u);
            low[u] = min(low[u], low[v]);

            if (fa != u && low[v] >= dfn[u] && !cutDot[u]) {
               ansDot++;
               cutDot[u] = true;
            }
        } else if (fa != v) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (u == fa && child > 1 && !cutDot[u]) {
        ansDot++;
        cutDot[u] = true;
    }

    return;
}

void tarjanEdge(int u, int fa) {
    dfn[u] = low[u] = ++cnt;

    for (int e = head[u]; e; e = edge[e].next) {
        int v = edge[e].v;

        if (!dfn[v]) {
            tarjanEdge(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] > dfn[u]) {
                ansEdge++;
                cutEdge[e] = true;
            }
        } else if (dfn[v] < dfn[u] && fa != v) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    return;
}

stack< pair<int, int> > sta;

void tarjanDcc(int u, int fa) {
    dfn[u] = low[u] = ++cnt;

    for (int e = head[u]; e; e = edge[e].next) {
        int v = edge[e].v;

        if (!dfn[v]) {
            sta.push(make_pair(u, v));
            tarjanDcc(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] >= dfn[u]) {
                ansDcc++;
                int sum = 0;

                while (true) {
                    sum++;

                    int tmp = sta.top().first;
                    sta.pop();

                    if (tmp == u) {
                        break;
                    }
                }

                ansDe = max(sum, ansDe);
            }
        } else if (dfn[v] < dfn[u] && fa != v) {
            low[u] = min(low[u], dfn[v]);
            sta.push(make_pair(u, v));
        }
    }

    return;
}

int main() {
    read(n);
    read(m);

    for (int i = 1; i <= m; ++i) {
        int x, y;
        read(x);
        read(y);
        addEdge(x, y);
        addEdge(y, x);
    }

    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjanDot(i, i);
        }
    }

    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    cnt = 0;

    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjanEdge(i, i);
        }
    }

    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    cnt = 0;

    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjanDcc(i, 0);
        }
    }

    cout << ansDot << ' ' << ansEdge << ' ' << ansDcc << ' ' << ansDe;

    return 0;
}
