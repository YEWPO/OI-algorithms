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

struct Vector {
    int x, y;
    
    int operator*(const Vector v) const {
        return x * v.x + y * v.y;
    }

    int operator^(const Vector v) const {
        return x * v.y - y * v.x;
    }
};

struct Point {
    int x, y;

    Vector operator-(const Point p) const {
        return {x - p.x, y - p.y};
    }

    bool operator==(const Point p) const {
        return x == p.x && y == p.y;
    }
};

inline int toLeft(Vector x, Vector y) {
    int val = x ^ y;

    if (val > 0) {
        return 1;
    } else if (val == 0) {
        return 0;
    } else {
        return -1;
    }
}

inline void readPoint(Point &p) {
    read(p.x);
    read(p.y);
}

Point a, b, c;
int n;

int main() {
    readPoint(a);
    readPoint(b);
    readPoint(c);
    read(n);

    if (a == b && b == c) {
        for (int  i = 1; i <= n; ++i) {
            Point p{};
            readPoint(p);
            printf(p == a ? "YES\n" : "NO\n");
        }
        return 0;
    }

    for (int i = 1; i <= n; ++i) {
        Point p{};
        readPoint(p);

        bool flag = false;

        if (!toLeft(b - a, p - a) && (p - a) * (p - b) <= 0) {
            flag = true;
        }

        if (!toLeft(c - b, p - b) && (p - b) * (p - c) <= 0) {
            flag = true;
        }

        if (!toLeft(a - c, p - c) && (p - c) * (p - a) <= 0) {
            flag = true;
        }

        int val1 = toLeft(b - a, p - a);
        int val2 = toLeft(c - b, p - b);
        int val3 = toLeft(a - c, p - c);

        if (val1 > 0 && val2 > 0 && val3 > 0) {
            flag = true;
        }

        if (val1 < 0 && val2 < 0 && val3 < 0) {
            flag = true;
        }

        printf(flag ? "YES\n" : "NO\n");
    }

    return 0;
}
