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

const int SIZE = 2e5 + 50;

int n, m;

vector<int> edge[SIZE];

int dfn[SIZE], low[SIZE];
int col[SIZE];
int cnt,colcnt;
bool ans = true;

stack<int> sta;

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    sta.push(u);

    for (int i = 0; i < edge[u].size(); ++i) {
        int v = edge[u][i];

        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (!col[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        int sum = 1;
        col[u] = ++colcnt;

        while (sta.top() != u) {
            col[sta.top()] = colcnt;
            sta.pop();
            sum++;
        }
        sta.pop();
    }

    return;
}

int main() {
    read(n);
    read(m);

    for (int i = 1; i <= m; ++i) {
        int u, wu, v, wv;

        read(u);
        read(wu);
        read(v);
        read(wv);

        edge[wu ? u : u + n].push_back(wv ? v + n : v);
        edge[wv ? v : v + n].push_back(wu ? u + n : u);
    }

    for (int i = 1; i <= n << 1; ++i) {
        edge[0].push_back(i);
    }

    tarjan(0);

    for (int i = 1; i <= n; ++i) {
        if (col[i] == col[i + n]) {
            ans = false;
            break;
        }
    }

    if (ans) {
        cout << "YES";
    } else {
        cout << "NO";
    }


    return 0;
}
