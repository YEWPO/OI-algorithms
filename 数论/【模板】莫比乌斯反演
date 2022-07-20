#include <bits/stdc++.h>
using namespace std;

const int Mod = 1e9 + 7;
const int N = 1e7;

int n, m, a, q;
int prime[N + 5], tot;
int mou[N + 5], pre[N + 5], ans;
bool vis[N + 5];

inline void euler() {
    mou[1] = 1;
    pre[1] = 1;

    for (int i = 2; i <= N; ++i) {
        if (!vis[i]) {
            prime[++tot] = i;
            mou[i] = -1;
        }

        for (int j = 1; i * prime[j] <= N; ++j) {
            vis[i * prime[j]] = true;

            if (i % prime[j] == 0) {
                mou[i * prime[j]] = 0;
                break;
            }

            mou[i * prime[j]] = -mou[i];
        }

        pre[i] = (pre[i - 1] + 1ll * i * i % Mod * (mou[i] + Mod)) % Mod;
    }
}

inline int query(int x, int y) {
    return (1ll * x * (1 + x) / 2 % Mod) * (1ll * y * (1 + y) / 2 % Mod) % Mod;
}

inline int func(int x, int y) {
    int sum = 0;
    int p = min(x, y);

    for (int l = 1, r = 0; l <= p; l = r + 1) {
        int k1 = x / l;
        int k2 = y / l;

        r = min(min(x / k1, y / k2), p);

        sum = (sum + 1ll * (pre[r] - pre[l - 1] + Mod) * query(k1, k2) % Mod) % Mod;
    }

    return sum;
}

int main() {
    euler();

    scanf("%d%d%d", &n, &m, &a);
    q = min(min(n, m), a);

    for (int l = 1, r = 0; l <= q; l = r + 1) {
        int k1 = n / l;
        int k2 = m / l;

        r = min(min(n / k1, m / k2), q);

        ans = (ans + 1ll * (l + r) * (r - l + 1) / 2 % Mod * func(k1, k2) % Mod) % Mod;
    }

    printf("%d", ans);

    return 0;
}
