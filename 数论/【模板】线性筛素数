#include<iostream>
#include<cstdio>
#define rg register
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
		s=(s<<3)+(s<<1)+ch-'0';
		ch=getchar();
	}
	return w*s;
}
const int MAXN=1e7+5;
int n,m;
int v[MAXN],prime[MAXN],tot;
bool vis[MAXN];
int main()
{
	n=read(),m=read();
	for(rg int i=2;i<=n;++i)
	{
		if(!v[i])
		{
			prime[++tot]=i;
			v[i]=i;
			vis[i]=1;
		}
		for(rg int j=1;j<=tot&&prime[j]*i<=MAXN;++j)
		{
			if(prime[j]>v[i])
			break;
			v[prime[j]*i]=prime[j];
		}
	}
	for(rg int i=1;i<=m;++i)
	printf(vis[read()]?"Yes\n":"No\n");
	return 0;
}
