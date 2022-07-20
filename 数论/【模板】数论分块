#include <bits/stdc++.h>
using namespace std;

template<typename T>
inline void read(T &x) {
    T s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
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

typedef __int128 lll;
typedef long long ll;

int T;
ll n;
lll ans, sum;

inline lll query1(ll l, ll r) {
    return (lll) (r + l) * (r - l + 1) / 2;
}

inline lll query2(ll l, ll r) {
    l--;
    return (lll) (2 * (lll)r * r * r - 2 * (lll)l * l * l + 3 * (lll)r * r - 3 * (lll)l * l + r - l);
}

int main() {
    read(T);

    while (T--) {
        read(n);
        ans = sum = 0;

        ans = (lll) n * n * (n + 1) / 2;

        for (ll l = 1, r = 0; l <= n; l = r + 1) {
            ll k = n / l;
            r = n / k;

            sum += (lll) (n + 1) * k * query1(l, r);
            sum -= (lll) (1 + k) * k * query2(l, r) / 12;
        }

        ans -= sum;

        write(ans);
        putchar('\n');
    }

    return 0;
}
