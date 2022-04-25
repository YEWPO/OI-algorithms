#include <bits/stdc++.h>
using namespace std;
#define Ls(x) (x << 1)
#define Rs(x) (x << 1 | 1)
const int MAXN = 200003;
struct Tree {
	int l, r, lazy;
	long long sum;
}tree[MAXN << 2];
int A[MAXN];

void push_up(int x) {
	tree[x].sum = tree[Ls(x)].sum + tree[Rs(x)].sum;
}

void push_down(int x) {
	if(tree[x].lazy) {
		tree[Ls(x)].sum += tree[x].lazy * (tree[Ls(x)].r - tree[Ls(x)].l + 1);
		tree[Rs(x)].sum += tree[x].lazy * (tree[Rs(x)].r - tree[Rs(x)].l + 1);
		tree[Ls(x)].lazy += tree[x].lazy;
		tree[Rs(x)].lazy += tree[x].lazy;
		tree[x].lazy = 0;
	}
}

void build(int x, int L, int R) {
	tree[x].lazy = 0;
	tree[x].l = L; tree[x].r = R;
	if(L == R) {
		tree[x].sum = A[L];
		return ;
	}
	int mid = (L + R) >> 1;
	build(Ls(x), L, mid);
	build(Rs(x), mid + 1, R);
	push_up(x);
}

void update(int x, int L, int R, int val) {
	if(tree[x].l >= L && tree[x].r <= R) {
		tree[x].lazy += val;
		tree[x].sum += val * (tree[x].r - tree[x].l + 1);
		return ;
	}
	push_down(x);
	int mid = (tree[x].l + tree[x].r) >> 1;
	if(L <= mid) update(Ls(x), L, R, val);
	if(R > mid) update(Rs(x), L, R, val);
	push_up(x);
}

long long query(int x, int L, int R) {
	if(tree[x].l >= L && tree[x].r <= R)
		return tree[x].sum;
	push_down(x);
	int mid = (tree[x].l + tree[x].r) >> 1;
	long long res = 0;
	if(L <= mid) res += query(Ls(x), L, R);
	if(R > mid) res += query(Rs(x), L, R);
	return res;
}

int main() {
	freopen("in.txt","r",stdin);
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", A + i);
	}
	build(1, 1, n);
	int Q;
	scanf("%d", &Q);
	int temp, a, b, x;
	for(int i = 1; i <= Q; i++) {
		scanf("%d", &temp);
		if(temp == 1){
			scanf("%d%d%d", &a, &b, &x);
			update(1, a, b, x);
		}
		else{
			scanf("%d%d", &a, &b);
			printf("%lld\n", query(1, a, b));
		}
	}
	return 0;
}
