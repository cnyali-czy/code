#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using std::vector;
using std::swap;
int read()
{
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')
        ch=getchar();
    while(ch>='0'&&ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}
struct edge
{
    int n,nxt,v;
    edge(int n,int nxt,int v)
    {
        this->n=n;
        this->nxt=nxt;
        this->v=v;
    }
    edge(){}
}e[5000],E[205][5000];
int head[500],ecnt=-1;
void add(int from,int to,int v)
{
    e[++ecnt]=edge(to,head[from],v);
    head[from]=ecnt;
    e[++ecnt]=edge(from,head[to],0);
    head[to]=ecnt;
}
int Head[205][500],Ecnt[205];
int q[500],pre[500];
bool bfs()
{
    int l=0,r=0;
    memset(pre,-1,sizeof(pre));
    q[++r]=0;
    pre[0]=1;
    while(l<r)
    {
        int x=q[++l];
        if(x==432)
            break;
        for(int i=head[x];~i;i=e[i].nxt)
            if(e[i].v&&pre[e[i].n]==-1)
            {
                pre[e[i].n]=i;
                q[++r]=e[i].n;
            }
    }
    pre[0]=-1;
    if(~pre[432])
    {
        int p=pre[432];
        while(~p)
        {
            --e[p].v;
            ++e[p^1].v;
            p=pre[e[p^1].n];
        }
        return true;
    }
    return false;
}
vector<int> v[205][205];
int n,m;
int b[205],s[205],ans[205];
void solve()
{
    memset(head,-1,sizeof(head));
    ecnt=-1;
    for(int i=1;i<=n;++i)
        add(0,i,1);
    for(int i=1;i<=m;++i)
        add(n+i,432,b[i]);
    Ecnt[0]=ecnt;
    for(int i=0;i<=432;++i)
        Head[0][i]=head[i];
    for(int i=0;i<=ecnt;++i)
        E[0][i]=e[i];
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            for(vector<int>::iterator it=v[i][j].begin();it!=v[i][j].end();++it)
                add(i,n+*it,1);
            if(bfs())
            {
                ans[i]=j;
                break;
            }
            for(vector<int>::iterator it=v[i][j].begin();it!=v[i][j].end();++it)
            {
                ecnt-=2;
                head[i]=e[head[i]].nxt;
                head[n+*it]=e[head[n+*it]].nxt;
            }
            if(j==m)
                ans[i]=m+1;
        }
        Ecnt[i]=ecnt;
        for(int j=0;j<=432;++j)
            Head[i][j]=head[j];
        for(int j=0;j<=ecnt;++j)
            E[i][j]=e[j];
    }
}
void solve1(int x)//恢复 x 之前的图 并增广 x+1
{
    ecnt=Ecnt[x];
    for(int i=0;i<=432;++i)
        head[i]=Head[x][i];
    for(int i=0;i<=ecnt;++i)
        e[i]=E[x][i];
    ++x;
    for(int i=1;i<=m;++i)
    {
        for(vector<int>::iterator it=v[x][i].begin();it!=v[x][i].end();++it)
            add(x,n+*it,1);
        if(bfs())
        {
            ans[x]=i;
            break;
        }
        for(vector<int>::iterator it=v[x][i].begin();it!=v[x][i].end();++it)
        {
            ecnt-=2;
            head[x]=e[head[x]].nxt;
            head[n+*it]=e[head[n+*it]].nxt;
        }
        if(i==m)
            ans[x]=m+1;
    }
}
int main()
{
    int T=read(),u;
    int C=read();
    while(T--)
    {
        n=read();
        m=read();
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
                v[i][j].clear();
        for(int i=1;i<=m;++i)
            b[i]=read();
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
            {
                u=read();
                if(u)
                    v[i][u].push_back(j);
            }
        for(int i=1;i<=n;++i)
            s[i]=read();
        solve();
        for(int i=1;i<=n;++i)
            printf("%d ",ans[i]);
        puts("");
        for(int i=1;i<=n;++i)
        {
            int l=0,r=i,mid;
            while(l<r)
            {
                mid=(l+r)>>1;
                swap(v[i],v[i-mid]);
                solve1(i-mid-1);
                if(ans[i-mid]<=s[i])
                    r=mid;
                else
                    l=mid+1;
                swap(v[i],v[i-mid]);
            }
            printf("%d ",l);
        }
        puts("");
    }
    return 0;
}
