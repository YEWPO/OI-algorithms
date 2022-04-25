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

const int N = 310;

int n, m;
int edge[N][N];
set<int> dot;
int ans = 2000;
int dis[N];
int s, t;

int addSet() {
    memset(dis, 0, sizeof dis);
    s = t = 0;
    set<int> lef = dot;
    int inDot, cut;

    while (!lef.empty()) {
        cut = -1;
        for (auto it = lef.begin(); it != lef.end(); it++) {
            int u = *it;

            if (dis[u] > cut) {
                cut = dis[u];
                inDot = u;
            }
        }

        s = t;
        t = inDot;

        lef.erase(inDot);

        for (auto it = lef.begin(); it != lef.end(); it++) {
            int u = *it;

            dis[u] += edge[u][inDot];
        }
    }

    return cut;
}

void StoerWagner() {

    while (dot.size() > 1) {
        ans = min(ans, addSet());

        edge[s][t] = edge[t][s] = 0;
        dot.erase(t);

        for (auto it = dot.begin(); it != dot.end(); it++) {
            int u = *it;
            edge[s][u] += edge[t][u];
            edge[u][s] += edge[u][t];

            edge[t][u] = edge[u][t] = 0;
        }
    }

    return;
}

int main() {
    read(n);
    read(m);

    for (int i = 1; i <= n; ++i) {
        dot.insert(i);
    }

    for (int i = 1; i <= m; ++i) {
        int u, v;
        read(u);
        read(v);

        edge[u][v]++;
        edge[v][u]++;
    }

    StoerWagner();

    write(ans);

    return 0;
}
