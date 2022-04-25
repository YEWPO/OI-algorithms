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
priority_queue<pair<int,int> >q;
void dijkstra()
{
    memset(dis,0x3f, sizeof(dis));
    dis[1]=0;
    q.push(make_pair(0,1));
    while (q.size())
    {
        int x=q.top().second;
        q.pop();
        if (!vis[x])
        {
            vis[x]= true;
            for(rg int i=head[x];i;i=e[i].net)
            {
                int y=e[i].v;
                int z=e[i].w;
                if(dis[x]+z<dis[y])
                {
                    dis[y]=dis[x]+z;
                    q.push(make_pair(-dis[y],y));
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
    dijkstra();
    printf("%d",dis[n]);
    return 0;
}
