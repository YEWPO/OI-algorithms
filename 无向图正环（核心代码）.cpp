void dfs(int x,int p)
{
    for(rg int i=head[x];i;i=e[i].net)
    {
        int to=e[i].v;
        if(!vis[to])
        {
            vis[to]=1;
            dfs(to,x);
        }
        else if(to!=p&&vis[to])
        {
            if(!flag)
            {
                flag=1;
                findp();//Êä³ö»·£» 
            }
            return;
        }
    }
    vis[x]=2;
    return;
}
