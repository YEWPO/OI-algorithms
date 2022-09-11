#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
#define rg register
#define ll long long
#define cena(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
using namespace std;
int read()
{
	int w=1,s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		s=s*10+ch-'0';
		ch=getchar();
	}
	return w*s;
}
void write(ll x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)
	write(x/10);
	putchar(x%10+'0');
	return;
}
const int MAXN=1e5+5;
const ll INF=0x3f3f3f3f3f3f3f3fll;
struct edge{
	int u,v,w,net;
	bool used;
}e[10*MAXN];
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
vector< pair<int,int> >ee[MAXN];
bool cmp(edge a,edge b)
{
	return a.w<b.w;
}
int fa[MAXN];
int getfa(int x)
{
	return x!=fa[x]?fa[x]=getfa(fa[x]):fa[x];
}
int n,m;
ll ans=INF;
ll smallest_val;
void kruskal()
{
	int all=0;
	sort(e+1,e+tot+1,cmp);
	for(rg int i=1;i<=n;++i)
	fa[i]=i;
	for(rg int i=1;i<=tot;++i)
	{
		int f1=getfa(e[i].u),f2=getfa(e[i].v);
		if(f1!=f2)
		{
			fa[f1]=f2;
			smallest_val+=e[i].w;
			e[i].used=1;
			all++;
			if(all==n-1)
			break;
		}
	}
	return;
}
int bznum;
ll new_small[MAXN][20][2];
int dep[MAXN],fro[MAXN][20];//new_smallµÄ0Îª×î´óÖµ£¬1·´Ö®
void dfs(int u)
{
	for(rg int i=0;i<ee[u].size();++i)
	{
		int v=ee[u][i].first;
		if(!dep[v])
		{
			dep[v]=dep[u]+1;
			fro[v][0]=u;
			int w=ee[u][i].second;
			new_small[v][0][0]=w;
			new_small[v][0][1]=-INF;
			for(rg int j=1;j<=bznum;++j)
			{
				fro[v][j]=fro[fro[v][j-1]][j-1];
				new_small[v][j][0]=max(new_small[v][j-1][0],new_small[fro[v][j-1]][j-1][0]);
				if(new_small[v][j-1][0]==new_small[fro[v][j-1]][j-1][0])
				new_small[v][j][1]=max(new_small[v][j-1][1],new_small[fro[v][j-1]][j-1][1]);
				else if(new_small[v][j-1][0]<new_small[fro[v][j-1]][j-1][0])
				new_small[v][j][1]=max(new_small[v][j-1][0],new_small[fro[v][j-1]][j-1][1]);
				else
				new_small[v][j][1]=max(new_small[v][j-1][1],new_small[fro[v][j-1]][j-1][0]);
			}
			dfs(v);
		}
	}
	return;
}
void lca(int u,int v,ll &val1,ll &val2)
{
	if(dep[u]>dep[v])
	swap(u,v);
	for(rg int i=bznum;i>=0;--i)
	if(dep[fro[v][i]]>=dep[u])
	{
		if(val1>new_small[v][i][0])
		val2=max(val2,new_small[v][i][0]);
		else
		{
			val1=new_small[v][i][0];
			val2=max(val2,new_small[v][i][1]);
		}
		v=fro[v][i];
	}
	if(u==v)
	return;
	for(rg int i=bznum;i>=0;--i)
	if(fro[u][i]!=fro[v][i])
	{
		val1=max(val1,max(new_small[u][i][0],new_small[v][i][0]));
		val2=max(val2,new_small[u][i][0]!=val1?new_small[u][i][0]:new_small[u][i][1]);
		val2=max(val2,new_small[v][i][0]!=val1?new_small[v][i][0]:new_small[v][i][1]);
		u=fro[u][i];
		v=fro[v][i];
	}
	val1=max(val1,max(new_small[u][0][0],new_small[v][0][0]));
	val2=max(val2,new_small[u][0][0]!=val1?new_small[u][0][0]:new_small[u][0][1]);
	val2=max(val2,new_small[v][0][0]!=val1?new_small[v][0][0]:new_small[v][0][1]);
	return;
}
signed main()
{
	cena("tree");
	n=read(),m=read();
	for(rg int i=1;i<=m;++i)
	{
		int x=read(),y=read(),z=read();
		add_edge(x,y,z);
	}
	kruskal();
	for(rg int i=1;i<=tot;++i)
	if(e[i].used)
	{
		ee[e[i].u].push_back(make_pair(e[i].v,e[i].w));
		ee[e[i].v].push_back(make_pair(e[i].u,e[i].w));
	}
	bznum=log(n)/log(2)+1;
	dep[1]=1;
	for(rg int i=0;i<=bznum;++i)
	new_small[1][i][0]=new_small[1][i][1]=-INF;
	dfs(1);
	for(rg int i=1;i<=tot;++i)
	if(!e[i].used)
	{
		ll val1=-INF,val2=-INF;
		lca(e[i].u,e[i].v,val1,val2);
		if(e[i].w>val1)
		ans=min(ans,smallest_val-val1+e[i].w);
		else
		ans=min(ans,smallest_val-val2+e[i].w);
	}
	write(ans);
	return 0;
}
