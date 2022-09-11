#include <iostream>
#include <cstdio>
#define rg register
#define MAXN 100001
using namespace std;
int n,m;
struct edge{
    int u,v,net;
};
edge e[5*MAXN];
int tot,head[MAXN];
void add_edge(int u,int v)
{
    e[++tot].u=u;
    e[tot].v=v;
    e[tot].net=head[u];
    head[u]=tot;
    return;
}
int color[MAXN],col;
int dfn[MAXN],low[MAXN];
int num,top;
int st[MAXN];
void tarjan(int u)
{
    dfn[u]=low[u]=++num;
    st[++top]=u;
    for(rg int i=head[u];i;i=e[i].net)
    {
        int v=e[i].v;
        if(!dfn[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!color[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(low[u]==dfn[u])
    {
        color[u]=++col;
        while(st[top]!=u)
        {
            color[st[top]]=col;
            top--;
        }
        top--;
    }
    return;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(rg int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add_edge(x,y);
    }
    for(rg int i=1;i<=n;++i)
    if(!dfn[i])
    tarjan(i);
    for(rg int i=1;i<=col;++i)
    {
        for(rg int j=1;j<=n;++j)
            if(color[j]==i)
                printf("%d ",j);
            printf("\n");
    }

    return 0;
}
