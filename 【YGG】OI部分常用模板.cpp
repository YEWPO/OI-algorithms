//by YGG 
//负环
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200100;
const int MAXE = 400400;
const int INF = 0x3f3f3f3f;

struct Edge {
    int to, nxt, len;
    Edge() {} 
    Edge(int _to, int _nxt, int _len) : to(_to), nxt(_nxt), len(_len) {}
}E[MAXE << 1];

int h[MAXN], d[MAXN], cnt, S[MAXN], n, m, T;
bool vis[MAXN], flag;

inline void add_edge(int x, int y, int v) {
    E[++cnt] = Edge(y, h[x], v), h[x] = cnt;
}

void SPFA(int x) {
    vis[x] = 1;
    for(int i = h[x]; i; i = E[i].nxt) {
        int v = E[i].to;
        if(d[v] > d[x] + E[i].len) {
            d[v] = d[x] + E[i].len;
            if(!vis[v])
                SPFA(v);
            else {
                flag = 1;
                return ;
            }
        }
    }
    vis[x] = 0;
    return ;
}
signed main() {
    scanf("%d", &T);
    while(T--) {
        flag = 0; cnt = 0;
        scanf("%d%d", &n, &m);
        memset(h, 0, sizeof(h));
        memset(d, 0, sizeof(d));
        memset(vis, 0, sizeof(vis));
        for(int i = 1, a, b, c; i <= m; i++) {
            scanf("%d%d%d", &a, &b, &c);
            add_edge(a, b, c);
            if(c >= 0) add_edge(b, a, c);
        }
        for(int i = 1; i <= n; i++) {
            SPFA(i);
            if(flag)
                break;
        }
        if(flag) printf("YE5\n");
        else printf("N0\n");
    }
    return 0;
}

//ST表
#include <bits/stdc++.h> 

using std::max;
using std::min;

const int MAXN = 200100;
const int INF = 0x7FFFFFFF;

#define Get(x) (int) log2(x) + 1
#define Debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> inline void Read(T &x) {
	int c = getchar();
	bool f = false;
	for (x = 0; !isdigit(c); c = getchar()) {
		if (c == '-') {
			f = true;
		}
	}
	for (; isdigit(c); c = getchar()) {
		x = x * 10 + c - '0';
	}
	if (f) {
		x = -x;
	}
}

template <typename T> inline bool CheckMax(T &a, const T &b) {
	return a < b ? a = b, true : false;
}

template <typename T> inline bool CheckMin(T &a, const T &b) {
	return a > b ? a = b, true : false;
}

int f[MAXN][20];
int a[MAXN], n;
int Q;

void init() {
	for(int i = 1; i <= n; i++) f[i][0] = a[i]; 
	for(int j = 1; (1 << j) <= n; j++) {
		for(int i = 1; i + (1 << j) - 1 <= n; i++) {
			f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
		}
	}
}

int query(int l, int r) {
	int p = 0; while((1 << (p + 1)) <= (r - l + 1)) p++;
	return max(f[l][p], f[r - (1 << p) + 1][p]);
}

signed main() {
	Read(n), Read(Q);
	for(int i = 1; i <= n; i++) Read(a[i]);
	init();
	while(Q --) {
		int l, r; Read(l), Read(r);
		printf("%d\n", query(l, r));
	}
#ifdef LOCAL
	Debug("My Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}

//Manacher
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 51000000;
char s1[MAXN], s2[MAXN];
int len1, len2, ans;
int p[MAXN]; 
void init() {
    len1 = (int)strlen(s1);
    s2[0] = '$';
    s2[1] = '#';
    for(int i = 0; i < len1; i++) {
        s2[2 * i + 2] = s1[i];
        s2[2 * i + 3] = '#';
    }
    len2 = len1 * 2 + 2;
    s2[len2] = '&';
}

void manacher() {
    int id = 0, mx = 0;
    for(int i = 1; i < len2; i++) {
        if(mx > i) p[i] = min(p[2 * id - i], mx - i);
        else p[i] = 1;
        while(s2[i + p[i]] == s2[i - p[i]]) p[i]++;
        if(i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
    }
}

signed main() {
    scanf("%s", s1);
    init();
    manacher();
    ans = 0;
    for(int i = 1; i < len2; i++) ans = max(ans, p[i] - 1);
    printf("%d\n", ans);
    return 0;
}

//线性基
#include <bits/stdc++.h>

using namespace std;

#define LL long long
const int MAXN = 110;

LL bit[MAXN]; 
int n;
LL a[MAXN], tot, delta;

void Gauss() {
    tot = delta = 0LL;
    for(LL i = bit[60]; i; i >>= 1) {
        int j = tot + 1;
        while(!(i & a[j]) && j <= n) j++;
        if(j == n + 1) continue;
        tot++;
        swap(a[tot], a[j]);
        for(int k = 1; k <= n; k++) {
            if(k != tot && (a[k] & i))
                a[k] ^= a[tot];
        }
    }
    if(tot != n) delta = 1;
}

signed main() {
    bit[0] = 1; for(int i = 1; i <= 62; i++) bit[i] = (bit[i - 1] << 1);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%lld", a + i);
    Gauss(); LL res = 0; 
    for(int i = 2; i <= tot; i++) a[i] ^= a[i - 1];
    printf("%lld\n", a[tot]);
    return 0;
}  

//sort by Splay
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500500;
const int INF = 0x3f3f3f3f;
int n, m, M = -INF;
int a[MAXN];

struct Splay {
    int sz[MAXN], key[MAXN], sum[MAXN], ch[MAXN][2], fa[MAXN], root, tot;
    void clear(int x) {
        ch[x][0] = ch[x][1] = fa[x] = sz[x] = sum[x] = key[x] = 0;
    }
    int Reflect(int x) {
    	int cur = root; 
    	while(1) {
    		if(key[cur] == x) return cur;
            else if(key[cur] > x) cur = ch[cur][0];
            else cur = ch[cur][1];
        }
    }
    int Get(int x) {
        return ch[fa[x]][1] == x;
    }
    void update(int x) {
        if(x) {
            sz[x] = 0; sz[x] += sum[x];
            if(ch[x][0]) sz[x] += sz[ch[x][0]];
            if(ch[x][1]) sz[x] += sz[ch[x][1]];
        }
    }
    void Rotate(int x) {
        int y = fa[x], z = fa[y], w = Get(x);
        ch[y][w] = ch[x][w ^ 1]; fa[ch[y][w]] = y;
        ch[x][w ^ 1] = y; fa[y] = x; fa[x] = z;
        if(z) ch[z][ch[z][1] == y] = x;
        update(y), update(x);
    }
    void splay(int x) {
        for(int F; (F = fa[x]); Rotate(x))
            if(fa[F]) Rotate(Get(x) == Get(F) ? F : x);
        root = x;
    }
    void insert(int x) {
        if(!root) {
            root = ++tot, ch[root][0] = ch[root][1] = 0; key[root] = x, sz[root] = sum[root] = 1;
            return ;
        }
        int now = root, F = 0;
        while(1) {
            if(x == key[now]) {
                sum[now] ++; update(now);
                update(F); splay(now); return ;
            }
            F = now, now = ch[now][x > key[now]];
            if(!now) {
                tot++;
                ch[tot][0] = ch[tot][1] = 0; key[tot] = x, sz[tot] = sum[tot] = 1; fa[tot] = F;
                ch[F][x > key[F]] = tot;
                update(F);
                splay(tot);
                break;
            }
        }
        return ;
    }
    void del(int x) {
        splay(Reflect(x));
        if(sum[root] - 1) {
            sum[root] --; update(root); return ;
        }
        if(!ch[root][0] && !ch[root][1]) {
            clear(root), root = 0;
            return ;
        }
        if(!ch[root][0]) {
            int cur = root; root = ch[root][1]; fa[root] = 0;
            clear(cur); return ;
        }
        else if(!ch[root][1]) {
            int cur = root; root = ch[root][0]; fa[root] = 0;
            clear(cur); return ;
        }
        int rep = pred(x), cur = root;
        splay(rep); ch[root][1] = ch[cur][1];
        fa[ch[cur][1]] = root;
        clear(cur); return ;
    }
    int pred(int x) {
        insert(x);
        int v = ch[root][0];
        while(ch[v][1]) {
            v = ch[v][1];
        }
        del(x);
        return v;
    }
    int succ(int x) {
        insert(x);
        int v = ch[root][1];
        while(ch[v][0]) {
            v = ch[v][0];
        }
        del(x);
        return v;
    }
    int Find(int x) {
        int ret = 0, cur = root;
        while(1) {
            if(key[cur] > x) cur = ch[cur][0];
            else {
                ret += sz[ch[cur][0]];
                if(x == key[cur]) {
                    splay(cur); return ret + 1;
                }
                ret += sum[cur], cur = ch[cur][1];
            }
        }
    }
    int Find_x(int x) {
    	int cur = root;
    	while(1) {
    		if(ch[cur][0] && sz[ch[cur][0]] >= x) cur = ch[cur][0];
    		else {
    			if(sz[ch[cur][0]] + sum[cur] < x) {
    				x -= sz[ch[cur][0]] + sum[cur];
    				cur = ch[cur][1];
    			}
    			else return key[cur];
    		}
    	}
    }
    void print(int x) {
        if(ch[x][0]) print(ch[x][0]);
        while(sum[x] --) {
            if(key[x] != M) {
                printf("%d ", key[x]);
            }
            else {
                printf("%d%c", key[x], sum[x] == 0 ? '\n' : ' ');
            }
        }
        if(ch[x][1]) print(ch[x][1]);
    }
}S;

signed main() {
    read(n);
    for(int i = 1; i <= n; i++) {
        read(a[i]); M = max(M, a[i]);
        S.insert(a[i]);
    }
    S.print(S.root);
    return 0;
}

//并查集 & 最小生成树
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;
inline int read() 
{
    int x=0; char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x;
}
int ans;
struct Node
{
    int u,v; int len;
    Node(int x1=0,int x2=0,int x3=0):u(x1),v(x2),len(x3){};
}Road[200005];
bool cmp(const Node& Road1,const Node& Road2)
{
    return Road1.len<Road2.len;
}
int f[40005];
int Find(int x)
{
    if(f[x]==x)return x;
    else return f[x]=Find(f[x]);
}
int n,m;
int rnk[40005];
void unite(int x,int y) 
{
    x=Find(x); y=Find(y);
    if(x==y) return;
    if(rnk[x]<rnk[y]) f[x]=y;
    else 
    {
        f[y]=x;
        if(rnk[x]==rnk[y]) rnk[x]++;
    }
}
int main()
{
 	n=read();m=read();
 	for(int i=1;i<=m;i++)
 	{
 		int u,v;int len;
 		scanf("%d%d%d",&u,&v,&len);
 		Road[i]=Node(u,v,len);
 	}
 	sort(Road+1,Road+m+1,cmp);
    int sum=0;
    for(int i=1;i<=n;i++)
        f[i]=i;
 	for(int i=1;i<=m;i++)
 	{
 		int u=Road[i].u;
 		int v=Road[i].v;
 		int len=Road[i].len;
 		if(Find(u)!=Find(v))
 		{
 			unite(u,v);
            ans+=len;
            sum++;
 		}
 	}
 	if(sum<n-1)
 		printf("orz\n");
 	else
 		printf("%d\n",ans);
 	return 0;	
} 

//乘法逆元
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 20000528;
int fac[MAXN + 3], inv[MAXN + 3];
int mod;

void init() {
    fac[0] = 1;
    for(int i = 1; i < mod; i++) fac[i] = (long long)fac[i - 1] * i % mod;
    inv[0] = inv[1] = 1;
    for(int i = 2; i < mod; i++) inv[i] = (long long)(mod - mod / i) * inv[mod % i] % mod;
}

int main() {
    int n;
    scanf("%d%d", &n, &mod);
    init();
    for(int i = 1; i <= n; i++) printf("%d\n", inv[i]);
    return 0;
}

//后缀排序
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAXN = 3010100;
char s[MAXN];

int * x, * y;
int a[MAXN], fir[MAXN], sec[MAXN];
int rnk[MAXN], sa[MAXN], h[MAXN], len, n, sum[MAXN];

void init() {
        x = rnk; y = sec;
        len = strlen(s + 1);
        for(int i = 1; i <= len; i++) a[i] = (int) s[i];
}

inline void radix_sort(int * f) {
    memset(sum, 0, sizeof(sum));
    for(int i = 1; i <= len; i++) sum[f[i]] ++;
    for(int i = 1; i <= n; i++) sum[i] += sum[i - 1];
    for(int i = len; i; i--) sa[sum[f[i]] --] = y[i];
}

void SA() {
    int i, j, p; n = 255;
    memset(sum, 0, sizeof(sum));
    for(i = 1; i <= len; i++) sum[(x[i] = a[i])] ++;
    for(i = 1; i <= n; i++) sum[i] += sum[i - 1];
    for(i = len; i; i--) sa[sum[x[i]] --] = i;
    for(j = 1, p = 1; p < len; j <<= 1, n = p) {
        for(i = len - j + 1, p = 0; i <= len; i++) y[++p] = i;
        for(i = 1; i <= len; i++) (sa[i] - j > 0) && (y[++p] = sa[i] - j);
        for(i = 1; i <= len; i++) fir[i] = x[y[i]]; 
        radix_sort(fir);
        swap(x, y); x[sa[1]] = 1;
        for(i = 2, p = 1; i <= len; i++) {
            if((y[sa[i - 1]] != y[sa[i]]) || (y[sa[i] + j] != y[sa[i - 1] + j]))
                p++;
            x[sa[i]] = p;
        }
    }
    for(i = 1; i <= len; i++) rnk[sa[i]] = i;
}

inline void GetH() {
    int k = 0; 
    for(int i = 1; i <= len; i++) {
        if(rnk[i] == 1) h[rnk[i]] = 0;
        else {
            int j = sa[rnk[i] - 1];
            while(a[i + k] == a[j + k]) k++;
            h[rnk[i]] = k;
            if(k > 0) k--;
        }
    }	
}

inline void print() {
    for(int i = 1; i <= len; i++) 
        printf("%d%c", sa[i], i == len ? '\n' : ' ');
}

signed main() {
    scanf("%s", s + 1);
    init();
    SA();
    GetH();
    print();
    return 0;
}

//线段树SegmentTree
#include <bits/stdc++.h>
#define Ls(x) x << 1
#define Rs(x) x << 1 | 1
using namespace std;
int n, m;
long long mod;
const int MAXN = 100000 + 10;
long long a[MAXN];
inline int read()
{
    int ch, x = 0, f = 1;ch = getchar();
    while((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    ch == '-' ? f = -1, ch = getchar() : 0;
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return f * x;
}
inline long long readl()
{
    long long ch, x = 0, f = 1;ch = getchar();
    while((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    ch == '-' ? f = -1, ch = getchar() : 0;
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return f * x;
}
struct SegmentTree{
    int l, r, len;
    long long tag;
    long long mult;
    long long val;
    SegmentTree()
    {
        tag = 0;val = 0;mult = 1;
        l = r = len = 0;
    }
}tre[MAXN << 2];
void build(int rt, int l, int r)
{
    tre[rt].l = l, tre[rt].r = r, tre[rt].len = r - l + 1;
    if(l == r) {
        tre[rt].val = a[l];
        return ;
    }
    int mid = (l + r) >> 1;
    build(Ls(rt), l, mid);
    build(Rs(rt), mid + 1, r);
    tre[rt].val = (tre[Ls(rt)].val + tre[Rs(rt)].val) % mod;
}
void push_down(int rt) {
    tre[Ls(rt)].mult =  tre[Ls(rt)].mult * tre[rt].mult % mod;
    tre[Ls(rt)].tag = (tre[Ls(rt)].tag * tre[rt].mult + tre[rt].tag) % mod;
    tre[Ls(rt)].val  = (tre[Ls(rt)].val  * tre[rt].mult + tre[rt].tag * (tre[Ls(rt)].len)) % mod;
    tre[Rs(rt)].mult =  tre[Rs(rt)].mult * tre[rt].mult % mod;
    tre[Rs(rt)].tag = (tre[Rs(rt)].tag * tre[rt].mult + tre[rt].tag) % mod;
    tre[Rs(rt)].val  = (tre[Rs(rt)].val  * tre[rt].mult + tre[rt].tag * (tre[Rs(rt)].len)) % mod;
    tre[rt].mult=1;tre[rt].tag=0;
}
void update(int rt, int L, int R, long long delta, int k) {
    int l = tre[rt].l, r = tre[rt].r;
    int mid = (l + r) >> 1;
    if(l >= L && r <= R) {
        if(k == 2) {
            tre[rt].tag = (tre[rt].tag + delta) % mod;
            tre[rt].val = (tre[rt].val + delta * tre[rt].len) % mod;
        }
        else {
            tre[rt].mult = tre[rt].mult * delta % mod;
            tre[rt].tag = tre[rt].tag * delta % mod;
            tre[rt].val = tre[rt].val * delta % mod;
        }
        return ;
    }
    if(tre[rt].mult != 1 || tre[rt].tag ) push_down(rt);
    if(L <= mid) update(Ls(rt), L, R, delta, k);
    if(R > mid)  update(Rs(rt), L, R, delta, k);
    tre[rt].val = (tre[Ls(rt)].val + tre[Rs(rt)].val) % mod;
    return ;
}
long long query(int rt, int L, int R) {
    int l = tre[rt].l, r = tre[rt].r;int mid = (l + r) >> 1;
    if(l >= L && r <= R) {
    	return tre[rt].val;
    }
    if(tre[rt].mult != 1 || tre[rt].tag ) push_down(rt);
    long long res = 0;
    if(L <= mid) res += query(Ls(rt), L, R);
    if(mid < R) res += query(Rs(rt), L, R);
    return res % mod;
    
}

signed main()
{
    n = read();m = read();mod = readl();
    for(int i = 1; i <= n; i++) a[i] = readl();
    build(1, 1, n);
    for(int i = 1, opt, l, r; i <= m; i++) {
        opt = read(); l = read(); r = read();
        long long dif;
        if(opt == 3) {
            printf("%lld\n", query(1, l, r));
        }
        else {
            dif = readl();
            update(1, l ,r, dif, opt);
        }
    }
    return 0;
}

//树链剖分带修改
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 500005;
inline int read() {
    int ch,  x = 0,  f = 1;ch = getchar();
    while((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    ch == '-' ? f = -1,  ch = getchar() : 0;
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return f * x; 
}
int A[MAXN], B[MAXN];
int n, m, sta, mod;
#define Ls(x) (x << 1)
#define Rs(x) (x << 1 | 1)
struct SegmentTree{
    int l, r, len;
    long long tag;
    long long mult;
    long long val;
    SegmentTree()
    {
        tag = 0;val = 0;mult = 1;
        l = r = len = 0;
    }
}tre[MAXN << 2];
void build(int rt, int l, int r)
{
    tre[rt].l = l, tre[rt].r = r, tre[rt].len = r - l + 1;
    if(l == r) {
        tre[rt].val = B[l];
        return ;
    }
    int mid = (l + r) >> 1;
    build(Ls(rt), l, mid);
    build(Rs(rt), mid + 1, r);
    tre[rt].val = (tre[Ls(rt)].val + tre[Rs(rt)].val) % mod;
}
void push_down(int rt) {
    //tre[Ls(rt)].mult =  tre[Ls(rt)].mult * tre[rt].mult % mod;
    tre[Ls(rt)].tag = (tre[Ls(rt)].tag + tre[rt].tag) % mod;
    tre[Ls(rt)].val  = (tre[Ls(rt)].val + tre[rt].tag * (tre[Ls(rt)].len)) % mod;
    //tre[Rs(rt)].mult =  tre[Rs(rt)].mult * tre[rt].mult % mod;
    tre[Rs(rt)].tag = (tre[Rs(rt)].tag + tre[rt].tag) % mod;
    tre[Rs(rt)].val  = (tre[Rs(rt)].val + tre[rt].tag * (tre[Rs(rt)].len)) % mod;
    tre[rt].tag=0;
}
void update(int rt, int L, int R, long long delta) {
    int l = tre[rt].l, r = tre[rt].r;
    int mid = (l + r) >> 1;
    if(l >= L && r <= R) {
    
        tre[rt].tag = (tre[rt].tag + delta) % mod;
        tre[rt].val = (tre[rt].val + delta * tre[rt].len) % mod;
        
        return ;
    }
    if(tre[rt].mult != 1 || tre[rt].tag ) push_down(rt);
    if(L <= mid) update(Ls(rt), L, R, delta);
    if(R > mid)  update(Rs(rt), L, R, delta);
    tre[rt].val = (tre[Ls(rt)].val + tre[Rs(rt)].val) % mod;
    return ;
}
long long query(int rt, int L, int R) {
    int l = tre[rt].l, r = tre[rt].r;int mid = (l + r) >> 1;
    if(l >= L && r <= R) {
    	return tre[rt].val;
    }
    if(tre[rt].mult != 1 || tre[rt].tag ) push_down(rt);
    long long res = 0;
    if(L <= mid) res += query(Ls(rt), L, R);
    if(mid < R) res += query(Rs(rt), L, R);
    return res % mod;
    
}

struct Edge {
    int to, len, nxt;
    Edge() {}
    Edge(int _to, int _len, int _nxt):to(_to), len(_len), nxt(_nxt) {}
}E[MAXN << 1];
int h[MAXN], cnte, tot, cnt;
int val[MAXN];
int a[MAXN];
int Lr[MAXN], Rr[MAXN];
int dep[MAXN], fa[MAXN], sz[MAXN], top[MAXN], son[MAXN],ID[MAXN];
inline void add_edge(int u, int v, int w) {
    E[++cnte] = Edge(v, w, h[u]), h[u] = cnte;
    E[++cnte] = Edge(u, w, h[v]), h[v] = cnte;
}
void dfs1(int x) {
    
    sz[x] = 1; dep[x] = dep[fa[x]] + 1;
    for(int i = h[x]; i; i = E[i].nxt) {
        int to = E[i].to;
        if(to == fa[x]) continue;
        fa[to] = x;val[x] = E[i].len;
        dfs1(to);
        sz[x] += sz[to];
        if(sz[to] > sz[son[x]]) son[x] = to;
    }
    
}
void dfs2(int x) {
    Lr[x] = ++tot;
    B[Lr[x]] = a[x];
     
    if(x == son[fa[x]]) top[x] = top[fa[x]];
    else top[x] = x;
    if(son[x]) dfs2(son[x]);
    for(int i = h[x]; i; i = E[i].nxt) {
        int to = E[i].to;
        if(to == fa[x] || to == son[x]) continue;
        dfs2(to);
    }
    Rr[x] = tot;
}

void up(int a, int b, int c) {
    int f1 = top[a], f2 = top[b];
    while(f1 != f2) {
        if(dep[f1] < dep[f2]) { swap(a, b); swap(f1, f2); }
        update(1, Lr[f1], Lr[a], c);
        a = fa[f1];
        f1 = top[a];
    }
    if(dep[a] > dep[b]) swap(a, b);
    update(1, Lr[a], Lr[b], c);
}

int qsum(int x, int y) {
    int ans=0;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])swap(x, y);
        ans += query(1,Lr[top[x]], Lr[x]);
        x = fa[top[x]];
    }
    if(dep[x]<dep[y])swap(x, y);
    ans+=query(1,Lr[y],Lr[x]);
    return ans;
}


signed main() {
    n = read(), m = read(), sta = read(), mod = read();
    for(int i = 1; i <= n; i++) a[i] = read();
    for(int i = 1; i < n; i++) add_edge(read(), read(), 0);
    dfs1(sta);
    dfs2(sta);
    int x, y, z, opt;
    build(1, 1, tot);
    while(m--) {
        opt = read();
        if(opt == 1) {
            x = read(), y = read(), z = read();
            up(x, y, z);
        }
        else if(opt == 2) {
            x = read(); y = read();
            printf("%d\n", qsum(x, y) % mod);
        }
        else if(opt == 3) {
            x = read(); z = read();
            update(1, Lr[x], Rr[x], z);
        }
        else {
            x = read();
            printf("%d\n", query(1, Lr[x], Rr[x]) % mod);
        }
    }
    return 0;
}

//矩阵快速幂
#include <stdio.h>
#include <string.h>
#include <algorithm>
const int MAXN = 101;
const int mod = 1000000007;
int n;
long long k;
inline long long read()
{
    char ch;long long x = 0ll;long long f = 1ll;ch=getchar();
    while (ch!='-'&&(ch<'0'||ch>'9'))
        ch=getchar();
    ch=='-'?f=-1ll:x=ch-'0',ch=getchar();
     while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
     return x*f;
}

struct Mat {
    long long mat[MAXN][MAXN];
};

Mat operator * (Mat a, Mat b) {
    Mat c;
    memset(c.mat, 0, sizeof(c.mat));
    for(int i = 0; i < n; i++) {
        for(int k = 0; k < n; k++) {
            for(int j = 0; j < n; j++) {
                c.mat[i][j] += (a.mat[i][k] % mod) * (b.mat[k][j] % mod) % mod;
                c.mat[i][j] %= mod;
            }
        }
    }
    return c;
}

Mat operator ^ (Mat a, long long k)  {
    Mat c;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) c.mat[i][j] = (i == j);
    while(k) {
        if(k & 1) c = c * a;
        a = a * a;
        k >>= 1;
    }
    return c;
}

signed main()
{
    scanf("%d%lld", &n, &k);
    Mat MMat;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            MMat.mat[i][j] = read();
    MMat = MMat ^ k;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            j == n - 1 ? printf("%d\n", MMat.mat[i][j]) : printf("%d ", MMat.mat[i][j]);
    return 0; 
}

//网络流isap
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <functional>
#define DBG printf("problems are here!!!!!\n");

const int MAXN = 100100;
const int MAXE = 400400;
const int INF = 0x3f3f3f3f;

using std::min;
using std::max;
using std::queue;

template<class T>void read(T &x) {
    x = 0;int f = 0;int ch = getchar();
    while(ch < '0' || ch > '9')  {f |= (ch == '-'); ch = getchar();}
    while(ch >=  '0'&&ch <= '9'){x = x * 10+(ch^48); ch = getchar();}
    x = f?-x:x;
    return;
}

struct Edge {
    int to, nxt, flow;
    Edge() {}
    Edge(int _to, int _nxt, int _flow) : to(_to), nxt(_nxt), flow(_flow) {}
}E[MAXE];

int h[MAXN], cur[MAXN], pre[MAXN], vis[MAXN], p;
int num[MAXN], d[MAXN], source, sink;
int tot, n, m;
queue<int>q;

inline void add_edge(int x, int y, int flow) {
    E[p] = Edge(y, h[x], flow), h[x] = p++;
    E[p] = Edge(x, h[y], 0), h[y] = p++;
}

void bfs() {
    memset(vis, 0, sizeof(vis));
    d[sink] = 0, vis[sink] = 1;
    q.push(sink);
    while(!q.empty()) {
        int u = q.front();
        num[d[u]]++;
        q.pop();
        for(int i = h[u]; ~i; i = E[i].nxt) {
            int v = E[i].to;
            if(!vis[v]) {
                vis[v] = 1;
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
}

void augment(int flow) {
    for(int i = source; i != sink; i = E[cur[i]].to) {
        E[cur[i]].flow -= flow;
        E[cur[i] ^ 1].flow += flow;
    }
}

int isap() {
    memset(num, 0, sizeof(num));
    bfs();
    //DBG;
    memcpy(cur, h, sizeof(h));
    int u = source, f = INF, flow = 0;
    while(d[source] < tot) {
        //DBG;
        bool fg = 0;
        for(int i = cur[u]; ~i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i].flow > 0&& d[u] == d[v] + 1) {
                cur[u] = i;
                pre[v] = u;
                u = v;
                fg = 1;
                f = min(f, E[i].flow);
                if(u == sink) {
                    flow += f;
                    augment(f);
                    f = INF;
                    u = source;	
                }
                break;
            }
        }
        if(fg) continue;
        if(--num[d[u]] == 0) break;
        int M = tot - 1;
        for(int i = h[u]; ~i; i = E[i].nxt) {
            int v = E[i].to;
            if(E[i].flow > 0&& d[v] < M) {
                M = d[v];
                cur[u] = i;
            } 
        }
        num[d[u] = M + 1]++;
        if(u != source) u = pre[u];
    }
    return flow;
}

signed main() {
    memset(h, -1, sizeof(h)); 
    read(n), read(m);
    read(source), read(sink);
    tot = n;
    for(int i = 1, a, b, c; i <= m; i++) {
        read(a), read(b), read(c);
        add_edge(a, b, c);
    }
    printf("%d\n", isap());
    return 0;
}

//Lucas定理
#include <bits/stdc++.h>   
using namespace std;       
typedef long long LL;    
LL m,n,p;    
LL qpow(LL a, LL b, LL mod) {
    LL ret = 1;
    while(b) {
        if(b & 1) ret *= a, ret %= mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ret;
} 
LL C(LL a,LL b) {    
    if(a < b) return 0;    
    LL ret = 1;    
    for(int i = 1; i <= b; i++) 
        ret = ret * (a - b + i) % p * qpow(i, p - 2, p) % p;   
    return ret;    
}    
LL Lucas(LL a,LL b) {    
    if(b == 0)    
        return 1;    
    return (Lucas(a / p, b / p) * C(a % p, b % p)) % p;    
}  
signed main() {    
    int t;    
    scanf("%d", &t);    
    while(t--) {    
        scanf("%lld%lld%lld", &n, &m, &p);    
        printf("%lld\n", Lucas(n + m, m));    
    }  
    return 0;  
}

//树状数组(BIT)
#include <bits/stdc++.h>
#define lowbit(x) x & -x
using namespace std;

const int MAXN = 100100;
const int INF = 0x3f3f3f3f;

int bit[MAXN], n, Q;

inline void update(int x, int y) {
    for(int i = x; i <= MAXN; i += lowbit(i)) bit[i] += y;
}

inline int query(int x) {
    int ret = 0; for(int i = x; i; i -= lowbit(i)) ret += bit[i]; return ret;
}

signed main() {
    scanf("%d%d", &n, &Q);
    for(int i = 1, a; i <= n; i++) {
        scanf("%d", &a);
        update(i, a);
    }
    while(Q -- ) {
        char com[10];
        int u, v;
        scanf("%s%d%d", com, &u, &v);
        if(com[0] == 'I') {
            update(u, v);
        }
        else if(com[0] == 'D') {
            update(u, -v);
        }
        else printf("%d\n", query(v) - query(u - 1));
    }
    return 0;
}

//Gauss消元
#include <bits/stdc++.h>
#define eps 1e-8
using namespace std;
const int MAXN = 230;
typedef double Matrix[MAXN][MAXN];
Matrix a;
int nn;
bool Gauss(Matrix A, int n) {
    int i, j, k, r;
    for(i = 0; i < n; i++) {
        r = i;
        for(j = i + 1; j < n; j++)
            if(fabs(A[j][i]) > fabs(A[r][i])) r = j;
    if(fabs(A[r][i]) < eps) {
            printf("No Solution\n");
            return 0;
        }
        if(r != i) for(j = 0; j <= n; j++) swap(A[r][j], A[i][j]);
        for(j = n; j >= i; j--)
            for(k = i + 1; k < n; k++)
                A[k][j] -= A[k][i] / A[i][i] * A[i][j];
    }
    for(i = n - 1; i >= 0; i--) {
        for(j = i + 1; j < n; j++)
            A[i][n] -= A[j][n] * A[i][j];
        A[i][n] /= A[i][i];
    }
    return 1;
} 
signed main() {
    scanf("%d", &nn);
    for(int i= 0; i < nn; i++)
        for(int j = 0; j <= nn; j++) scanf("%lf", &a[i][j]);
    bool ans = Gauss(a, nn);
    if(ans) for(int i = 0; i < nn; i++) printf("%.2lf\n", a[i][nn]);
    return 0;
}

//矩阵优化递推式
#include <bits/stdc++.h>
const int mod = 1000000007;
int n;
inline int read()
{
    int ch;int x = 0;int f = 1;ch=getchar();
    while (ch!='-'&&(ch<'0'||ch>'9'))
        ch=getchar();
    ch=='-'?f=-1:x=ch-'0',ch=getchar();
     while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
     return x*f;
}
struct Mat {
    long long mat[3][3];
};
Mat operator * (Mat a, Mat b) {
    Mat c;
    memset(c.mat, 0, sizeof(c.mat));
    for(int i = 0; i < 3; i++) {
        for(int k = 0; k < 3; k++) {
            for(int j = 0; j < 3; j++) {
                c.mat[i][j] += (a.mat[i][k] % mod) * (b.mat[k][j] % mod) % mod;
                c.mat[i][j] %= mod;
            }
        }
    }
    return c;
}
Mat operator ^ (Mat a, long long k)  {
    Mat c;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++) c.mat[i][j] = (i == j);
    while(k) {
        if(k & 1) c = c * a;
        a = a * a;
        k >>= 1;
    }
    return c;
}
Mat init;
Mat fi;
int t;
signed main()
{
    scanf("%d", &t);
    while(t--)
    {
        memset(init.mat, 0, sizeof(init.mat));
        memset(fi.mat, 0, sizeof(fi.mat));
        scanf("%d", &n);
        init.mat[0][0] = 1;
        init.mat[0][2] = 1;
        init.mat[1][0] = 1;
        init.mat[2][1] = 1;
        fi.mat[0][0] = 1;
        fi.mat[1][0] = 1;
        fi.mat[2][0] = 1;
        if(n <= 3) printf("%d\n", 1);
        else{
            init = init ^ (n - 3);
            fi = init * fi;
            printf("%d\n", fi.mat[0][0]);
        }
    }
    return 0;
}

//后缀自动机
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

const int MAXN = 2000100;
const int MAXW = 30;
char S[MAXN];
int str;

using std::copy;
using std::max;

namespace SAM {
    int len[MAXN], cnt, ch[MAXN][MAXW], root, fa[MAXN], lst;
    int sz[MAXN], tp[MAXN], End[MAXN], mn[MAXN], mx[MAXN];
    long long ans;
    void init() {
        lst = cnt = root = 1;
        ans = 0;
    }
    int add_node(int u) {
        len[++cnt] = u; mn[cnt] = u; return cnt;
    }
    
    int insert(int w) {
        int p = lst; int u = add_node(len[p] + 1);
        for(; p && !ch[p][w]; ch[p][w] = u, p = fa[p]);
        if(!p) fa[u] = root;
        else {
            int cur = ch[p][w];
            if(len[cur] == len[p] + 1) fa[u] = cur;
            else {
                int n = add_node(len[p] + 1);
                copy(ch[cur], ch[cur] + MAXW, ch[n]);
                fa[n] = fa[cur]; fa[cur] = fa[u] = n;
                for(; p && ch[p][w] == cur; ch[p][w] = n, p = fa[p]);
            }
        } 
        return lst = u;
    }
    
    void build() {
        for(int i = 1; i <= str; i++) End[insert(S[i] - 'a')] = 1;
    }
    
    void toposort() {
        int L = len[lst];
        for(int i = 1; i <= L; i++) sz[i] = 0;
        for(int i = 1; i <= cnt; i++) sz[len[i]] ++;
        for(int i = 1; i <= L; i++) sz[i] += sz[i - 1];
        for(int i = 1; i <= cnt; i++) tp[sz[len[i]] --] = i;
    }
    
    void solve() {
        toposort();
        for(int i = cnt; i; i--) {
            int p = tp[i];
            End[fa[p]] += End[p];
            //printf("%d %d\n", fa[p], End[fa[p]]);
        }
        //puts("");
        for(int i = 2; i <= cnt; i++) 
            if(End[i] != 1)
                ans = max(ans, (long long)End[i] * len[i]);
        printf("%lld\n", ans);
    }
}

using namespace SAM;

signed main() {
    scanf("%s", S + 1); str = strlen(S + 1);
    init();
    build();
    solve();
    return 0;
}

//二分图匹配
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12306;

int lnk[MAXN],used[MAXN];
vector<int> divide[MAXN];
int n,m,e,ans;
inline int read() 
{
    int x=0; char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return x;
}
bool Find(int x, int f)
{
    for(int i = 0; i < (int) divide[x].size(); i++)
    {
        int v = divide[x][i];
        if(used[v] != f)
        {
            used[v] = f;
            if(lnk[v] == -1 | Find(lnk[v], f))
            {
                lnk[v] = x;
                return 1;
            }
        }
    }
    return 0;
}
int main()
{
    n = read();m = read(); e = read();
    memset(lnk, -1, sizeof(lnk));
    for(int i = 1, a, b; i <= e; i++)
    {
        a = read(); b = read();
        if(b > m || a > n)  continue;
        divide[a].push_back(b);
    }
    for(int i = 1; i <= n; i++) {
        if(Find(i, i))
          ans++;
    }
    printf("%d\n", ans);
    return 0;
} 
 
//快速傅里叶变换FFT
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

const int MAXN = 4000500;
const int INF = 0x3f3f3f3f;
const double pi = 3.14159265358979323846264338327950288;

using std::min;
using std::swap;
using std::max;

struct comp {
    double x, y;
    comp(double _x = 0.0000, double _y = 0.0000) : x(_x), y(_y) {}
    comp operator + (const comp&a) const {return comp(x + a.x, y + a.y);}
    comp operator - (const comp&a) const {return comp(x - a.x, y - a.y);}
    comp operator * (const comp&a) const {return comp(x * a.x - y * a.y, x * a.y + y * a.x);}	 
};

comp A[MAXN], B[MAXN], tmp, C[MAXN];
int rev[MAXN], T, n, m;
comp Sin[MAXN];

void init() {
    for(T = 1; T <= n + m; T <<= 1);
    for(int i = 1; i < T; i++) {
        if(i & 1) rev[i] = rev[i >> 1] >> 1 ^ (T >> 1);
        else rev[i] = rev[i >> 1] >> 1;
    } 
    Sin[0] = comp(1, 0), Sin[1] = comp(cos(2.000 * pi / T), sin(2.000 * pi / T));
    for(int i = 2; i < (T >> 1); i++) Sin[i] = Sin[i - 1] * Sin[1];
}

void fft(comp * a) {
    for(int i = 1; i < T; i++) if(rev[i] > i) swap(a[rev[i]], a[i]);
    for(int i = 2, mid = 1, s = (T >> 1); i <= T; mid = i, s >>= 1, i <<= 1) {
        for(int j = 0; j < T; j += i) {
            for(int k = j, cur = 0; k < j + mid; k++, cur += s) {
                tmp = a[k + mid] * Sin[cur];
                a[k + mid] = a[k] - tmp;
                a[k] = a[k] + tmp;
            }
        }
    } 
}

signed main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i <= n; i++) scanf("%lf", &A[i].x);
    for(int i = 0; i <= m; i++) scanf("%lf", &B[i].x);
    init();
    fft(A), fft(B);
    for(int i = 0; i < (T >> 1); i++) Sin[i].y = -Sin[i].y;
    for(int i = 0; i < T; i++) C[i] = A[i] * B[i];
    fft(C);
    for(int i = 0; i <= n + m; i++) 
        printf("%d%c", (int) (C[i].x / T + 0.5), i == n + m ? '\n' : ' ');
    return 0;
}

//SPFA
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100100;
const int MAXE = 500400;
const int INF = 2147483647;

struct Edge {
    int to, nxt, len;
    Edge() {} 
    Edge(int _to, int _nxt, int _len) : to(_to), nxt(_nxt), len(_len) {}
}E[MAXE << 1];

int h[MAXN], d[MAXN], cnt;
bool vis[MAXN];
queue<int>Q;

inline void add_edge(int x, int y, int v) {
    E[++cnt] = Edge(y, h[x], v), h[x] = cnt;
}

int n, m, S;

void SPFA(int x) {
    d[x] = 0; vis[x] = 1;
    Q.push(x);
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        vis[u] = 0;
        for(int i = h[u]; i; i = E[i].nxt) {
            int v = E[i].to;
            if(d[v] > d[u] + E[i].len) {
                d[v] = d[u] + E[i].len;
                if(!vis[v]) {
                    Q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
}
signed main() {
    for(int i = 1; i <= MAXN; i++) d[i] = INF;
    scanf("%d%d%d", &n, &m, &S);
    for(int i = 1 ; i <= m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add_edge(a, b, c);
    }
    SPFA(S);
    for(int i = 1; i <= n; i++)
        printf("%d%c", d[i], i == n ? '\n' : ' ');
    return 0;
}

//Tarjan
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>

const int MAXN = 200100;
const int MAXE = 600400;
const int INF = 0x3f3f3f3f;

using std::min;

struct Edge {
    int to, nxt;
    Edge() {}
    Edge(int _to, int _nxt) : to(_to), nxt(_nxt) {}
}E[MAXE];

int h[MAXN], ins[MAXN], dfn[MAXN], Clock_t, Stack[MAXN], SCC;
int top, belong[MAXN], in[MAXN], sz[MAXN], cnt, low[MAXN];
int vis[MAXN], n, m;

inline void add_edge(int u, int v) {
    E[++cnt] = Edge(v, h[u]), h[u] = cnt;
    //E[++cnt] = Edge(u, h[v]), h[v] = cnt;
}

void Tarjan(int x) {
    ins[x] = 1;
    low[x] = dfn[x] = ++Clock_t;
    Stack[++top] = x;
    for(int i = h[x]; ~i; i = E[i].nxt) {
        int v = E[i].to;
        if(!dfn[v]) {
            Tarjan(v);
            low[x] = min(low[x], low[v]);
        }
        else if(ins[v]) low[x] = min(low[x], low[v]);
    }
    if(low[x] == dfn[x]) {
        SCC++;int v;
        do {
            v = Stack[top--];
            ins[v] = 0;
            belong[v] = SCC;
            sz[SCC]++;
        }while(v != x);
    }
    return ;
}

void dfs(int x) {
    vis[x] = 1;
    for(int i = h[x]; ~i; i = E[i].nxt) {
        int v = E[i].to;
        if(belong[x] != belong[v]) in[belong[v]]++;
        if(!vis[v]) dfs(v);
    }
}

signed main() {
    scanf("%d%d", &n, &m); memset(h, -1, sizeof(h));
    for(int i = 1, a, b; i <= m; i++) {
        scanf("%d%d", &a, &b);
        add_edge(a, b);
    }
    
    for(int i = 1; i <= n; i++) 
        if(!dfn[i])
            Tarjan(i);
    int ans = 0;
    for(int i = 1; i <= n; i++)
        if(!vis[i])
            dfs(i);
    for(int i = 1; i <= SCC; i++) {
        if(!in[i]) ans++;
    }
    printf("%d\n", ans);
    return 0;
} 

//KMP
#include <bits/stdc++.h>
using namespace std;
int next[3000000];
char s[3000000],p[3000000];
void KmpSearch(char* s, char* p)  
{  
    int i = 0;  
    int j = 0;  
    int sLen = strlen(s);  
    int pLen = strlen(p);  
    while(i < sLen && j < pLen) {  
        if(s[i] != p[j]) {
            if(j == 0) i++;			
            j = next[j];
        }		  
        while(j < pLen && s[i] == p[j]) {  
            i++;  
            j++;  
        }  
        if(j == pLen) {   
          printf("%d\n",i - j + 1) ;
          j = next[j];
        }  
    }  
}  
void GetNext(char* p, int next[])  
{  
    int pLen = strlen(p);  
    next[0] = 0;
    next[1] = 0;  
    int j = 0, i = 1;
    for(int i = 1; i < pLen; i++) {  
        while(j > 0 && p[i] != p[j]) j = next[j];  
        if(p[i] == p[j]) j++;  
        next[i + 1] = j;  
    }  
}  
signed main() {
    scanf("%s", s); 
	scanf("%s",p);
    GetNext(p, next);
    KmpSearch(s, p);
    for(int i = 1; i < (int) strlen(p); i++)
      cout << next[i] << " ";
    cout << next[strlen(p)] << endl;  
    return 0;
}  

//LCA
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500100;
const int INF = 0x3f3f3f3f;

struct Edge {
    int to, nxt;
    Edge() {}
    Edge(int _to, int _nxt) : to(_to), nxt(_nxt) {}
}E[MAXN << 1];

int h[MAXN], cnt, fa[MAXN], son[MAXN], sz[MAXN];
int dep[MAXN], top[MAXN], n, rt, Q;

inline void add_edge(int u, int v) {
    E[++cnt] = Edge(v, h[u]), h[u] = cnt;
    E[++cnt] = Edge(u, h[v]), h[v] = cnt;
}

inline void dfs1(int x) {
    dep[x] = dep[fa[x]] + 1; sz[x] = 1;
    for(int i = h[x]; ~i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == fa[x]) continue;
        fa[v] = x;
        dfs1(v);
        sz[x] += sz[v];
        (sz[v] > sz[son[x]]) && (son[x] = v);
    }
    return ;
}

void dfs2(int x) {
    if(x == son[fa[x]]) top[x] = top[fa[x]];
    else top[x] = x;
    if(son[x]) dfs2(son[x]);
    for(int i = h[x]; ~i; i = E[i].nxt) {
        int v = E[i].to;
        if(v == fa[x] || v == son[x]) continue;
        dfs2(v);
    }
    return ;
}

int LCA(int x, int y) {
    int f1 = top[x], f2 = top[y];
    while(f1 != f2) {
        if(dep[f1] < dep[f2]) swap(f1, f2), swap(x, y);
        x = fa[f1];
        f1 = top[x];
    }
    if(dep[x] > dep[y]) return y;
    else return x;
}
signed main() {
    scanf("%d%d%d", &n, &Q, &rt);
    memset(h, -1, sizeof(h));
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d%d", &a, &b);
        add_edge(a, b);
    }
    dfs1(rt); dfs2(rt);
    while(Q --) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", LCA(a, b));
    }
    return 0;
}

//Splay
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500500;
const int INF = 0x3f3f3f3f;
int n, m, M = -INF;
int a[MAXN];

struct Splay {
    int sz[MAXN], key[MAXN], sum[MAXN], ch[MAXN][2], fa[MAXN], root, tot;
    void clear(int x) {
        ch[x][0] = ch[x][1] = fa[x] = sz[x] = sum[x] = key[x] = 0;
    }
    int Reflect(int x) {
    	int cur = root; 
    	while(1) {
    		if(key[cur] == x) return cur;
            else if(key[cur] > x) cur = ch[cur][0];
            else cur = ch[cur][1];
        }
    }
    int Get(int x) {
        return ch[fa[x]][1] == x;
    }
    void update(int x) {
        if(x) {
            sz[x] = 0; sz[x] += sum[x];
            if(ch[x][0]) sz[x] += sz[ch[x][0]];
            if(ch[x][1]) sz[x] += sz[ch[x][1]];
        }
    }
    void Rotate(int x) {
        int y = fa[x], z = fa[y], w = Get(x);
        ch[y][w] = ch[x][w ^ 1]; fa[ch[y][w]] = y;
        ch[x][w ^ 1] = y; fa[y] = x; fa[x] = z;
        if(z) ch[z][ch[z][1] == y] = x;
        update(y), update(x);
    }
    void splay(int x) {
        for(int F; (F = fa[x]); Rotate(x))
            if(fa[F]) Rotate(Get(x) == Get(F) ? F : x);
        root = x;
    }
    void insert(int x) {
        if(!root) {
            root = ++tot, ch[root][0] = ch[root][1] = 0; key[root] = x, sz[root] = sum[root] = 1;
            return ;
        }
        int now = root, F = 0;
        while(1) {
            if(x == key[now]) {
                sum[now] ++; update(now);
                update(F); splay(now); return ;
            }
            F = now, now = ch[now][x > key[now]];
            if(!now) {
                tot++;
                ch[tot][0] = ch[tot][1] = 0; key[tot] = x, sz[tot] = sum[tot] = 1; fa[tot] = F;
                ch[F][x > key[F]] = tot;
                update(F);
                splay(tot);
                //printf("insert no problem\n");
                break;
            }
        }
        return ;
    }
    void del(int x) {
        splay(Reflect(x));
        if(sum[root] - 1) {
            sum[root] --; update(root); return ;
        }
        if(!ch[root][0] && !ch[root][1]) {
            clear(root), root = 0;
            return ;
        }
        if(!ch[root][0]) {
            int cur = root; root = ch[root][1]; fa[root] = 0;
            clear(cur); return ;
        }
        else if(!ch[root][1]) {
            int cur = root; root = ch[root][0]; fa[root] = 0;
            clear(cur); return ;
        }
        int rep = pred(x), cur = root;
        splay(rep); ch[root][1] = ch[cur][1];
        fa[ch[cur][1]] = root;
        clear(cur); return ;
    }
    int pred(int x) {
        insert(x);
        int v = ch[root][0];
        while(ch[v][1]) {
            v = ch[v][1];
        }
        del(x);
        return v;
    }
    int succ(int x) {
        insert(x);
        int v = ch[root][1];
        while(ch[v][0]) {
            v = ch[v][0];
        }
        del(x);
        return v;
    }
    int Find(int x) {
        int ret = 0, cur = root;
        while(1) {
            if(key[cur] > x) cur = ch[cur][0];
            else {
                ret += sz[ch[cur][0]];
                if(x == key[cur]) {
                    splay(cur); return ret + 1;
                }
                ret += sum[cur], cur = ch[cur][1];
            }
        }
    }
    int Find_x(int x) {
    	int cur = root;
    	while(1) {
    		if(ch[cur][0] && sz[ch[cur][0]] >= x) cur = ch[cur][0];
    		else {
    			if(sz[ch[cur][0]] + sum[cur] < x) {
    				x -= sz[ch[cur][0]] + sum[cur];
    				cur = ch[cur][1];
    			}
    			else return key[cur];
    		}
    	}
    }
}S;

signed main() {
    scanf("%d", &n);
    for(int i = 1, opt, x; i <= n; i++) {
        scanf("%d%d", &opt, &x);
        if(opt == 1) S.insert(x);
        else if(opt == 2) S.del(x);
        else if(opt == 3) printf("%d\n", S.Find(x));
        else if(opt == 4) printf("%d\n", S.Find_x(x));
        else if(opt == 5) printf("%d\n", S.key[S.pred(x)]);
        else printf("%d\n", S.key[S.succ(x)]);
    }
    return 0;
}

//最小费用最大流MCMF
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>

const int MAXN = 100100;
const int MAXE = 400400;
const int INF = 0x3f3f3f3f;

using std::min;
using std::queue;
using std::pair;
using std::make_pair;

struct Edge {
    int from, to, nxt, flow, cost;
    Edge() {}
    Edge(int _f, int _t, int _n, int _F, int _c) : from(_f), to(_t), nxt(_n), flow(_F), cost(_c) {}
}E[MAXE];

int h[MAXN], d[MAXN], vis[MAXN], source, sink;
int cur[MAXN], pre[MAXN], p, n, m;
queue<int>q;

inline void add_edge(int x, int y, int flow, int cost) {
    E[p] = Edge(x, y, h[x], flow, cost), h[x] = p++;
    E[p] = Edge(y, x, h[y], 0, -cost), h[y] = p++;
}

bool SPFA() {
    memset(vis, 0, sizeof(vis));
    memset(d, 0x3f, sizeof(d));
    d[source] = 0; vis[source] = 1;
    q.push(source);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = 0;
        for(int i = h[u]; ~i; i = E[i].nxt) {
            int v = E[i].to;
            if(d[v] > d[u] + E[i].cost && E[i].flow) {
                d[v] = d[u] + E[i].cost;
                cur[v] = i;
                if(!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return d[sink] != INF;
}

pair<int, int> MCMF() {
    int flow = 0; int cost = 0;
    while(SPFA()) {
        int f = INF;
        for(int i = sink; i != source; i = E[cur[i]].from) f = min(f, E[cur[i]].flow);
        for(int i = sink; i != source; i = E[cur[i]].from) {
            E[cur[i]].flow -= f;
            E[cur[i] ^ 1].flow += f;
        }
        cost += f * d[sink];
        flow += f;
    }
    return make_pair(flow, cost);
}

signed main() {
    scanf("%d%d%d%d", &n, &m, &source, &sink);
    memset(h, -1, sizeof(h));
    for(int i = 1, a, b, c, f; i <= m; i++) {
        scanf("%d%d%d%d", &a, &b, &c, &f);
        add_edge(a, b, c, f);
    }
    pair<int, int> P = MCMF();
    printf("%d %d\n", P.first, P.second);
    return 0;
}

//主席树
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int MAXN = 100100 * 35;
template<class T>void read(T &g)
{
    g = 0;int f = 0;int ch = getchar();
    while(ch < '0' || ch > '9')  {f |= (ch == '-'); ch = getchar();}
    while(ch >=  '0'&&ch <= '9'){g = g * 10+(ch^48); ch = getchar();}
    g = f ? - g : g;
    return;
}
int rt[MAXN], n, m;
int a[MAXN];
int b[MAXN];
int val[MAXN], rs[MAXN], ls[MAXN], Clock_t;
void insert(int x, int pre, int l, int r, int pos) {
    int cur = rt[pre]; rt[x] = ++Clock_t; x = rt[x];
ygg:
    int mid = (l + r) >> 1;
    ls[x] = ls[cur], rs[x] = rs[cur], val[x] = val[cur] + 1;
    if(l == r) return ;
    if(pos <= mid) {
        ls[x] = ++Clock_t; x = ls[x]; cur = ls[cur]; r = mid;
        goto ygg;
    }
    else {
        rs[x] = ++Clock_t; x = rs[x]; cur = rs[cur]; l = mid + 1;
        goto ygg;
    }
}
int query(int x, int y, int l, int r, int kth) {
YGG:
    if(l >= r) return l;
    int mid = (l + r) >> 1;
    int tp = val[ls[y]] - val[ls[x]];
    if(tp >= kth) {
        x = ls[x]; y = ls[y]; r = mid;
        goto YGG;
    }
    else {
        x = rs[x]; y = rs[y]; l = mid + 1; kth -= tp;
        goto YGG;
    }
}
signed main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) read(a[i]), b[i] = a[i];
    sort(b + 1, b + n + 1);
    int t = unique(b + 1, b + n + 1) - b - 1;
    for(int i = 1, p; i <= n; i++) {
        p = lower_bound(b + 1, b + t + 1, a[i]) - b;
        insert(i, i - 1, 1, t, p);
    }
    while(m--) {
        int L, R, K;
        read(L), read(R), read(K);
        int p = query(rt[L - 1], rt[R], 1, t, K);
        printf("%d\n", b[p]);
    }
    return 0;
} 


