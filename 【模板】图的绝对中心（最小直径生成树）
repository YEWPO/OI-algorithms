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
}

const int N = 505;
const int SIZE = N * N;
typedef long long ll;

struct Edge {
    int u, v;
    ll w;
}e[SIZE];

int tot;

void addEdge(int u, int v, ll w) {
    e[++tot].u = u;
    e[tot].v = v;
    e[tot].w = w;
}

int n, m;
ll dis[N][N];
int rk[N][N];

inline void floyed() {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
}

ll tant[N];
ll ans = 0x3f3f3f3f3f3f3f3f;

inline void minTheta() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            tant[j] = dis[i][j];
            rk[i][j] = j;
        }
        sort(rk[i] + 1, rk[i] + n + 1, [](int x, int y) {return tant[x] < tant[y];});
    }

    for (int i = 1; i <= n; ++i) {
        ans = min(ans, dis[i][rk[i][n]] << 1);
    }

    for (int i = 1; i <= m; ++i) {
        int u = e[i].u;
        int v = e[i].v;
        ll w = e[i].w;

        int maxPosition = n;

        for (int j = n - 1; j; j--) {
            if (dis[v][rk[u][j]] > dis[v][rk[u][maxPosition]]) {
                ans = min(ans, dis[u][rk[u][j]] + w + dis[v][rk[u][maxPosition]]);
                maxPosition = j;
            }
        }
    }
}

int main() {
    read(n);
    read(m);

    memset(dis, 0x3f, sizeof dis);

    for (int i = 1; i <= n; ++i) {
        dis[i][i] = 0ll;
    }

    for (int i = 1; i <= m; ++i) {
        int x, y;
        ll z;
        read(x);
        read(y);
        read(z);
        dis[x][y] = dis[y][x] = min(dis[x][y], z);
        addEdge(x, y, z);
        addEdge(y, x, z);
    }

    m <<= 1;

    floyed();

    minTheta();

    write(ans);

    return 0;
}
