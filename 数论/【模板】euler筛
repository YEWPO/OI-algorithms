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

const int N = 5e5 + 5;
typedef long long ll;

int n;
int prime[N], tot;
bool vis[N];

ll phi[N];
ll mou[N];
ll cnt[N], minCnt[N];
ll sum[N], minSum[N];
ll f[N], minF[N];

inline void euler() {
    phi[1] = mou[1] = cnt[1] = sum[1] = f[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) {
            prime[++tot] = i;

            phi[i] = i - 1;

            mou[i] = -1;

            cnt[i] = 2;
            minCnt[i] = 1;

            sum[i] = i + 1;
            minSum[i] = i + 1;

            f[i] = 2;
            minF[i] = 2;
        }

        for (int j = 1; i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = true;

            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];

                mou[i * prime[j]] = 0;

                minCnt[i * prime[j]] = minCnt[i] + 1;
                cnt[i * prime[j]] = cnt[i] / (minCnt[i] + 1) * (minCnt[i] + 2);

                minSum[i * prime[j]] = minSum[i] * prime[j] + 1;
                sum[i * prime[j]] = sum[i] / minSum[i] * minSum[i * prime[j]];

                minF[i * prime[j]] = minSum[i] + 1;
                f[i * prime[j]] = f[i] / minF[i] * (minSum[i] + 1);

                break;
            }

            phi[i * prime[j]] =  phi[i] * (prime[j] - 1);

            mou[i * prime[j]] = -mou[i];

            minCnt[i * prime[j]] = 1;
            cnt[i * prime[j]] = cnt[i] * 2;

            minSum[i * prime[j]] = sum[prime[j]];
            sum[i * prime[j]] = sum[i] * sum[prime[j]];

            minF[i * prime[j]] = 2;
            f[i * prime[j]] = f[i] * 2;
        }
    }
}

inline void print() {
    for (int i = 1; i <= n; ++i) {
        write(phi[i]);
        putchar(' ');
    }
    putchar('\n');

    for (int i = 1; i <= n; ++i) {
        write(mou[i]);
        putchar(' ');
    }
    putchar('\n');

    for (int i = 1; i <= n; ++i) {
        write(cnt[i]);
        putchar(' ');
    }
    putchar('\n');

    for (int i = 1; i <= n; ++i) {
        write(sum[i]);
        putchar(' ');
    }
    putchar('\n');

    for (int i = 1; i <= n; ++i) {
        write(f[i]);
        putchar(' ');
    }
}

int main() {
    read(n);

    euler();

    print();

    return 0;
}
