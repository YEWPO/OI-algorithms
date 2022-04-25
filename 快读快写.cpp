#include<iostream>
#include<cstdio>
#define rg register
#define in(a) freopen(a".in","r",stdin)
#define out(a) freopen(a".out","w",stdout)
using namespace std;
int read()
{
    int w=1,s=0;
    char ch;
    ch=getchar();
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
void write(int x)
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
int main()
{
    int a=read();
    write(a);
    return 0;
}
