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

const int SIZE = 2e5 + 10;
const int N = 5e3 + 5;
int n, m, k;

vector< pair<int, int> > preEdge[N];

struct Edge {
    int v, w;
    int nxt;
}edge[SIZE];

int tot, head[N];

void addEdge(int u, int v, int w) {
    edge[++tot].v = v;
    edge[tot].w = w;
    edge[tot].nxt = head[u];
    head[u] = tot;

    return;
}

int dis[N];
bool vis[N];
priority_queue< pair<int, int> > q;

void dijkstra() {
    memset(dis, 0x3f, sizeof dis);

    q.push(make_pair(0, n));
    vis[n] = true;
    dis[n] = 0;

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        vis[u] = false;

        for (auto e: preEdge[u]) {
            int v = e.first;
            int w = e.second;

            if (dis[u] + w  < dis[v]) {
                dis[v] = dis[u] + w;

                if (!vis[v]) {
                    q.push(make_pair(dis[v], v));
                    vis[v] = true;
                }
            }
        }
    }

    return;
}

struct Node {
    int d;
    int g;

    bool operator<(Node x) const {
        return g + dis[d] > x.g + dis[x.d];
    }
};
priority_queue<Node> p;
int cnt[N];

void AStar() {
    p.push({1, 0});

    while (!p.empty()) {
        int u = p.top().d;
        int s = p.top().g;
        p.pop();

        cnt[u]++;

        if (cnt[n] == k) {
            write(s);
            exit(0);
        }

        if (cnt[u] <= k) {
            for (int i = head[u]; i; i = edge[i].nxt) {
                int v = edge[i].v;
                int w = edge[i].w;

                p.push({v, s + w});
            }
        }
    }

    return;
}

int main() {
    read(n);
    read(m);
    read(k);

    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        read(x);
        read(y);
        read(z);

        addEdge(x, y, z);
        preEdge[y].push_back(make_pair(x, z));
    }

    dijkstra();

    AStar();

    return 0;
}

