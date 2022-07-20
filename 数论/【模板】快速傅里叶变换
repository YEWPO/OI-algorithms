#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;
const double PI = acos(-1);

struct Complex {
    double x, y;

    Complex operator+(const Complex c) const {
        return {x + c.x, y + c.y};
    }

    Complex operator-(const Complex c) const {
        return {x - c.x, y - c.y};
    }

    Complex operator*(const Complex c) const {
        return {x * c.x - y * c.y, x * c.y + y * c.x};
    }
};

int n, m, tot;
Complex A[N], B[N], C[N], Sin[N];
int rev[N];

inline void fft(Complex *c) {
    for (int i = 1; i < tot; ++i) {
        if (rev[i] > i) {
            swap(c[rev[i]], c[i]);
        }
    }

    for(int i = 2, mid = 1, s = (tot >> 1); i <= tot; mid = i, s >>= 1, i <<= 1) {
        for(int j = 0; j < tot; j += i) {
            for(int k = j, cur = 0; k < j + mid; k++, cur += s) {
                Complex tmp;
                tmp = c[k + mid] * Sin[cur];
                c[k + mid] = c[k] - tmp;
                c[k] = c[k] + tmp;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; ++i) {
        scanf("%lf", &A[i].x);
    }
    for (int i = 0; i <= m; ++i) {
        scanf("%lf", &B[i].x);
    }

    for (tot = 1; tot <= n + m; tot <<= 1);
    for (int i = 1; i < tot; ++i) {
        if (i & 1) {
            rev[i] = rev[i >> 1] >> 1 ^ (tot >> 1);
        } else {
            rev[i] = rev[i >> 1] >> 1;
        }
    }

    Sin[0] = {1.0, 0.0};
    Sin[1] = {cos(2.0 * PI / tot), sin(2.0 * PI / tot)};
    for (int i = 1; i < (tot >> 1); ++i) {
        Sin[i] = Sin[i - 1] * Sin[1];
    }

    fft(A);
    fft(B);

    for(int i = 0; i < (tot >> 1); i++) {
        Sin[i].y = -Sin[i].y;
    }
    for (int i = 0; i < tot; ++i) {
        C[i] = A[i] * B[i];
    }
    fft(C);

    for (int i = 0; i <= n + m; ++i) {
        printf("%d ", (int)(C[i].x / tot + 0.5));
    }

    return 0;
}
