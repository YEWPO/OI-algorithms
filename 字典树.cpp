#include<iostream>
#include<cstdio>
#include<cstring>
#define N 100001
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
int tot,char_tree[N][10];
bool b_dot[N],check;
int T,n;
char s[10];
bool insert(char *s)
{
    int len=strlen(s),u=1;
    bool flag=0;
    for(rg int i=0;i<len;++i)
    {
        int c=s[i]-'0';
        if(!char_tree[u][c])
            char_tree[u][c]=++tot;
        else if(i==len-1)
            flag=true;
        u=char_tree[u][c];
        if(b_dot[u])
            flag=true;
    }
    b_dot[u]=1;
    return flag;
}
int main()
{
    in("phone"),out("phone");
    T=read();
    while(T--)
    {
        memset(b_dot,false, sizeof(b_dot));
        memset(char_tree,0, sizeof(char_tree));
        check=0,tot=1;
        n=read();
        for(rg int i=1;i<=n;++i)
        {
            scanf("%s",s);
            if (insert(s))
                check=1;
        }
        if(check)
            printf("NO\n");
        else
            printf("YES\n");
    }
    return 0;
}

