#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 5;

int n, m, ans;
int f[N << 1];
char s[N], t[N << 1] = {'#'};

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);

    int pre = 0;

    while (pre < n / 2 && s[pre + 1] == s[n - pre]) {
        pre++;
    }

    ans += 2 * pre;

    for (int i = pre + 1; i <= n - pre; ++i) {
        t[++m] = s[i];
        t[++m] = '#';
    }

    if (m) {
        for (int i = 0; i <= m; ++i) {
            f[i] = 0;
        }

        for (int i = 0, l = 0, r = -1; i <= m; ++i) {
            int k = i > r ? 1 : min(f[l + r - i], r - i + 1);
            while (i - k >= 0 && i + k <= m && t[i - k] == t[i + k]) {
                k++;
            }
            f[i] = k--;
            if (i + k > r) {
                r = i + k;
                l = i - k;
            }
        }

        int pos, r = 0;

        for (int i = 0; i <= m; ++i) {
            if ((i - f[i] + 1 == 0 || i + f[i] - 1 == m) && f[i] > r) {
                r = f[i];
                pos = i;
            }
        }

        for (int i = pos - r + 1; i <= pos + r - 1; ++i) {
            if (t[i] != '#') {
                ans++;
            }
        }
    }

    printf("%d", ans);

    return 0;
}
