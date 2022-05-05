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

const int SIZE = 1e5 + 5;
const int MAX = 32800;

inline int lowbit(int x) {
    return x & (-x);
}

int rt[SIZE];
int n, m;
int a[SIZE];
int top1, top2;
int sta1[SIZE], sta2[SIZE];

struct Node {
    int val;
    int l, r;
}node[MAX << 10];
int tot;

inline void Insert(int &root, int L, int R, int p, int val) {
    if (!root) {
        root = ++tot;
    }

    node[root].val += val;

    if (L == R) {
        return;
    }

    int mid = (L + R) >> 1;

    if (p <= mid) {
        Insert(node[root].l, L, mid, p, val);
    } else {
        Insert(node[root].r, mid + 1, R, p, val);
    }
}

inline int Query(int L, int R, int k) {
    if (L == R) {
        return L;
    }

    int sum = 0;
    int mid  = (L + R) >> 1;

    for (int i = 1; i <= top1; ++i) {
        sum += node[node[sta1[i]].l].val;
    }
    for (int i = 1; i <= top2; ++i) {
        sum -= node[node[sta2[i]].l].val;
    }

    if (k <= sum) {
        for (int i = 1; i <= top1; ++i) {
            sta1[i] = node[sta1[i]].l;
        }
        for (int i = 1; i <= top2; ++i) {
            sta2[i] = node[sta2[i]].l;
        }

        return Query(L, mid, k);
    } else {
        for (int i = 1; i <= top1; ++i) {
            sta1[i] = node[sta1[i]].r;
        }
        for (int i = 1; i <= top2; ++i) {
            sta2[i] = node[sta2[i]].r;
        }

        return Query(mid + 1, R, k - sum);
    }
}

inline void Add(int x, int p, int val) {
    for (; x <= n; x += lowbit(x)) {
        Insert(rt[x], 1, MAX, p, val);
    }
}

inline int Sum(int L, int R, int k) {
    top1 = top2 = 0;

    for (int i = R; i; i -= lowbit(i)) {
        sta1[++top1] = rt[i];
    }

    for (int i = L - 1; i; i -= lowbit(i)) {
        sta2[++top2] = rt[i];
    }

    return Query(1, MAX, k);
}

int main() {
    read(n);
    read(m);

    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        Add(i, a[i], 1);
    }

    for (int i = 1; i <= m; ++i) {
        char op[2];
        scanf("%s", op);

        if (op[0] == 'Q') {
            int x, y, k;
            read(x);
            read(y);
            read(k);

            write(Sum(x, y, k));
            cout.put('\n');
        } else {
            int x, y;
            read(x);
            read(y);

            Add(x, a[x], -1);
            a[x] = y;
            Add(x, a[x], 1);
        }
    }
    return 0;
}
