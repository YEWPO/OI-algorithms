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

    x = s * w;

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

const int N = 110;
const int SIZE = 1e4 + 10;

struct Edge {
    int u, v, w;
    int nxt;
}e[SIZE];
int tot, head[N];

void addEdge(int u, int v, int w) {
    e[++tot].u = u;
    e[tot].v = v;
    e[tot].w = w;
    e[tot].nxt = head[u];
    head[u] = tot;
    return;
}

int n, m, r;
int pre[N], dc[N], beg[N], sma[N];
int cir, ans;

bool zl() {
    while (true) {
        memset(sma, 0x3f, sizeof sma);
        memset(pre, 0, sizeof dc);
        memset(dc, 0, sizeof dc);
        memset(beg, 0, sizeof beg);
        cir = 0;

        for (int i = 1; i <= m; ++i) {
            int u = e[i].u;
            int v = e[i].v;

            if (u != v && e[i].w < sma[v]) {
                sma[v] = e[i].w;
                pre[v] = u;
            }
        }

        sma[r] = 0;
        for (int i = 1; i <= n; ++i) {
            if (sma[i] == sma[0]) {
                return false;
            }

            ans += sma[i];

            int d;
            for (d = i; d != r && beg[d] != i && !dc[d]; d = pre[d]) {
                beg[d] = i;
            }

            if (d != r && !dc[d]) {
                ++cir;
                while (!dc[d]) {
                    dc[d] = cir;
                    d = pre[d];
                }
            }
        }

        if (!cir) {
            return true;
        }

        for (int i = 1; i <= n; ++i) {
            if (!dc[i]) {
                dc[i] = ++cir;
            }
        }

        for (int i = 1; i <= m; ++i) {
            int las = sma[e[i].v];
            e[i].u = dc[e[i].u];
            e[i].v = dc[e[i].v];

            if (e[i].u != e[i].v) {
                e[i].w -= las;
            }
        }

        n = cir;
        r = dc[r];
    }
}

int main() {
    read(n);
    read(m);
    read(r);

    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        read(x);
        read(y);
        read(z);
        addEdge(x, y, z);
    }

    if (zl()) {
        cout << ans;
    } else {
        cout << "-1";
    }

    return 0;
}
