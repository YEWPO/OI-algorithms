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

const int N = 2e5 + 5;

int n1, n2, m = 1e3 + 5, tot;
int a[N], b[N];
int q[N << 1], c[N << 1], d[N << 1], sum[N << 1], sa[N << 1], rk[N << 1];

inline void SA() {
    int *x = c, *y = d, *t;
    int i, j, p;

    for (i = 1; i <= tot; ++i) {
        sum[x[i] = q[i]]++;
    }
    for (i = 1; i <= m; ++i) {
        sum[i] += sum[i - 1];
    }
    for (i = tot; i > 0; --i) {
        sa[sum[x[i]]--] = i;
    }

    for (p = 1, j = 1; p < tot; j <<= 1, m = p) {
        for (p = 0, i = tot - j + 1; i <= tot; ++i) {
            y[++p] = i;
        }
        for (i = 1; i <= tot; ++i) {
            if (sa[i] > j) {
                y[++p] = sa[i] - j;
            }
        }
        for (i = 0; i <= m; ++i) {
            sum[i] = 0;
        }
        for (i = 1; i <= tot; ++i) {
            sum[x[y[i]]]++;
        }
        for (i = 1; i <= m; ++i) {
            sum[i] += sum[i - 1];
        }
        for (i = tot; i > 0; --i) {
            sa[sum[x[y[i]]]--] = y[i];
        }

        t = x;
        x = y;
        y = t;

        for (p = 0, i = 1; i <= tot; ++i) {
            x[sa[i]] = y[sa[i]] == y[sa[i - 1]] && y[sa[i] + j] == y[sa[i - 1] + j] ? p : ++p;
        }
    }

    for (i = 1; i <= tot; ++i) {
        rk[i] = x[i];
    }
}

int main() {
    read(n1);

    for (int i = 1; i <= n1; ++i) {
        read(a[i]);
        q[++tot] = a[i];
    }
    q[++tot] = 1e3 + 5;

    read(n2);

    for (int i = 1; i <= n2; ++i) {
        read(b[i]);
        q[++tot] = b[i];
    }
    q[++tot] = 1e3 + 5;

    SA();

    int i = 1, j = 1;

    while (i <= n1 && j <= n2) {
        if (rk[i] < rk[n1 + 1 + j]) {
            write(a[i]);
            i++;
        } else {
            write(b[j]);
            j++;
        }
        putchar(' ');
    }

    while (i <= n1) {
        write(a[i]);
        putchar(' ');
        i++;
    }

    while (j <= n2) {
        write(b[j]);
        putchar(' ');
        j++;
    }

    return 0;
}
