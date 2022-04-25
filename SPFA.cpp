#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define MAXN 100000
#define rg register
using namespace std;
struct edge{
    int u,v,w,net;
}e[MAXN];
int tot,head[MAXN];
void add_edge(int u,int v,int w)
{
    e[++tot].u=u;
    e[tot].v=v;
    e[tot].w=w;
    e[tot].net=head[u];
    head[u]=tot;
    return;
}
int dis[MAXN],vis[MAXN];
void SPFA()
{
	queue<int>q;
    memset(dis,0x3f, sizeof(dis));
    dis[1]=0;
    vis[1]=1;
    q.push(1);
    while (q.size())
    {
        int x=q.front();
        q.pop();
        vis[x]=false;
        for(rg int i=head[x];i;i=e[i].net)
        {
            int y=e[i].v;
            int z=e[i].w;
            if(dis[x]+z<dis[y])
            {
                dis[y] = dis[x] + z;
                if (!vis[y])
                {
                    q.push(y);
                    vis[y] = 1;
                }
            }
        }
    }
    return;
}
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    for(rg int i=1;i<=m;++i)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        add_edge(x,y,z);
//        add_edge(y,x,z);
    }
    SPFA();
    printf("%d",dis[n]);
    return 0;
}
