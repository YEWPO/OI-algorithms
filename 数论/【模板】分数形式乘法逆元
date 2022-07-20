#include <bits/stdc++.h>
using namespace std;

template<typename T>
inline void read(T &x) {
    T s = 0, w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if (ch == '-') w = -w;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        s = (s << 1) + (s << 3) + ch - '0';
        ch = getchar();
    }
    x = w * s;
}

template<typename T>
inline void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

pair<int, int> nextPair(int &x) {
    int a, b;
    x ^= x << 13; x ^= x >> 17; x ^= x << 5; x %= 10000000; a = x;
    x ^= x << 13; x ^= x >> 17; x ^= x << 5; x %= 10000000; b = x;
    b = max(b, 1); a = max(a % b, 1);
    return {a, b};
}

typedef long long ll;

const ll Mod = 1e9 + 7;

int n, x;

inline ll ksm(ll x, ll y) {
    ll ans = 1ll;

    while (y) {
        if (y & 1) {
            ans = ans * x % Mod;
        }
        x = x * x % Mod;
        y >>= 1ll;
    }

    return ans;
}

ll ans;

int main() {
    read(n);
    read(x);

    for (int i = 1; i <= n; ++i) {
        auto var = nextPair(x);
        int a = var.first, b = var.second;
        ans = (ans + b * ksm(a, Mod - 2) % Mod) % Mod;
    }

    write(ans);

    return 0;
}
