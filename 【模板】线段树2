#include<iostream>
#include<cstdio>
#define int long long
#define ls(k) k<<1
#define rs(k) k<<1|1
using namespace std;
const int MAXN=100001;
int n,m,p=998244353,a[MAXN];
struct Node{
    int l,r,v;
    int ctag,dtag;
    Node(){
        l=r=v=dtag=0ll;
        ctag=1ll;
    }
}tree[4*MAXN];
void pushup(int k)
{
    tree[k].v=(tree[ls(k)].v+tree[rs(k)].v)%p;
    return ;
}
void pushdown(int k)
{
    if(tree[k].ctag!=1)
    {
        tree[ls(k)].ctag=tree[ls(k)].ctag*tree[k].ctag%p;
        tree[rs(k)].ctag=tree[rs(k)].ctag*tree[k].ctag%p;
        tree[ls(k)].dtag=tree[ls(k)].dtag*tree[k].ctag%p;
        tree[rs(k)].dtag=tree[rs(k)].dtag*tree[k].ctag%p;
        tree[ls(k)].v=tree[ls(k)].v*tree[k].ctag%p;
        tree[rs(k)].v=tree[rs(k)].v*tree[k].ctag%p;
        tree[k].ctag=1ll;
    }
    if(tree[k].dtag)
    {
        tree[ls(k)].v=(tree[ls(k)].v+tree[k].dtag*(tree[ls(k)].r-tree[ls(k)].l+1))%p;
        tree[rs(k)].v=(tree[rs(k)].v+tree[k].dtag*(tree[rs(k)].r-tree[rs(k)].l+1))%p;
        tree[ls(k)].dtag=(tree[ls(k)].dtag+tree[k].dtag)%p;
        tree[rs(k)].dtag=(tree[rs(k)].dtag+tree[k].dtag)%p;
        tree[k].dtag=0ll;
    }
    return;
}
void build(int k,int l,int r)
{
    tree[k].l=l;
    tree[k].r=r;
    if(l==r)
    {
        tree[k].v=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(ls(k),l,mid);
    build(rs(k),mid+1,r);
    pushup(k);
    return ;
}
void update1(int k,int L,int R,int v)
{
    int l=tree[k].l;
    int r=tree[k].r;
    if(R<l||L>r)
        return;
    if(L<=l&&r<=R)
    {
        tree[k].v=(tree[k].v+v*(tree[k].r-tree[k].l+1))%p;
        tree[k].dtag=(tree[k].dtag+v)%p;
        return;
    }
    pushdown(k);
    int mid=(l+r)>>1;
    if(L<=mid)
        update1(ls(k),L,R,v);
    if(R>=mid)
        update1(rs(k),L,R,v);
    pushup(k);
    return;
}
void update2(int k,int L,int R,int v)
{
    int l=tree[k].l;
    int r=tree[k].r;
    if(L>r||R<l)
        return;
    if(L<=l&&r<=R)
    {
        tree[k].v=v*tree[k].v%p;
        tree[k].ctag=tree[k].ctag*v%p;
        tree[k].dtag=tree[k].dtag*v%p;
        return;
    }
    pushdown(k);
    int mid=(l+r)>>1;
    if(L<=mid)
        update2(ls(k),L,R,v);
    if(R>=mid)
        update2(rs(k),L,R,v);
    pushup(k);
    return;
}
int query(int k,int L,int R)
{
    int ret=0;
    int l=tree[k].l;
    int r=tree[k].r;
    if(L>r||R<l)
        return 0;
    if(L<=l&&r<=R)
        return tree[k].v%p;
    pushdown(k);
    int mid=(l+r)>>1;
    if(L<=mid)
        ret=(ret+query(ls(k),L,R))%p;
    if(R>=mid)
        ret=(ret+query(rs(k),L,R))%p;
    return ret%p;
}
signed main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;++i)
        scanf("%lld",&a[i]);
    build(1,1,n);
    for(int i=1;i<=m;++i)
    {
        int k;
        scanf("%lld",&k);
        if(k==1)
        {
            int l,r,v;
            scanf("%lld%lld%lld",&l,&r,&v);
            update2(1,l,r,v);
        }
        else if(k==2)
        {
            int l,r,v;
            scanf("%lld%lld%lld",&l,&r,&v);
            update1(1,l,r,v);
        }
        else
        {
            int l,r;
            scanf("%lld%lld",&l,&r);
            printf("%lld\n",query(1,l,r)%p);
        }
    }
    return 0;
}
