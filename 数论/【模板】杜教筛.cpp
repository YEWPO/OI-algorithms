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

const int N = 2e6;
typedef long long ll;

int prime[N + 5], tot;
bool vis[N + 5];
int mu[N + 5];
ll preSum[N + 5];
map<int, ll> preMuSum;

inline void init() {
    mu[1] = 1;

    for (int i = 2; i <= N; ++i) {
        if (!vis[i]) {
            prime[++tot] = i;
            mu[i] = -1;
        }

        for (int j = 1; i * prime[j] <= N; ++j) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = - mu[i];
        }
    }

    for (int i = 1; i <= N; ++i) {
        preSum[i] = preSum[i - 1] + mu[i];
    }
}

inline ll muSum(int x) {
    if (x <= N) {
        return preSum[x];
    }
    if (preMuSum[x]) {
        return preMuSum[x];
    }

    ll sum = 1ll;

    for (int l = 2, r = 0; l <= x; l = r + 1) {
        int k = x / l;
        r = x / k;
        sum -= muSum(k) * (r - l + 1);
    }

    return preMuSum[x] = sum;
}

inline ll gcd(ll x, ll y) {
    return !y ? x : gcd(y, x % y);
}

int T;
int L, R;
ll ans1, ans2, num;

int main() {
    init();

    read(T);

    while (T--) {
        read(L);
        read(R);
        ans1 = 0;

        if (L == 1) {
            ans1 = -1ll;
        }

        L--;

        ans2 = 1ll * (R - L) * (R - L - 1);

        for (int l = 1, r = 0; l <= R; l = r + 1) {
            int k1 = R / l;
            int k2 = L / l;

            r = min(!k1 ? R : R / k1, !k2 ? R : L / k2);

            ans1 += 1ll * (k1 - k2) * (k1 - k2) * (muSum(r) - muSum(l - 1));
        }

        num = gcd(ans1, ans2);

        write(ans1 / num);
        putchar('/');
        write(ans2 / num);
        putchar('\n');
    }

    return 0;
}
