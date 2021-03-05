#include<bits/stdc++.h>
 
#define N 300010
 
using namespace std;
 
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^'0');
        ch=getchar();
    }
    return x*f;
}
 
int n,m,u[N],v[N],d[N];
int cnt=1,head[N],to[N<<1],nxt[N<<1];
int idx,dfn[N],low[N];
int tot,scc[N],deg[N];
bool cut[N];
 
stack<int>sta;
 
inline void adde(int u,int v)
{
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
 
void tarjan(int u,int fa)
{
    dfn[u]=low[u]=++idx;
    sta.push(u);
    int child=0;
    for(int i=head[u];i;i=nxt[i])
    {
        int v=to[i];
        if(!dfn[v])
        {
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u])
            {
                if(u==1) child++;
                else cut[u]=1;
                deg[u]++;
                tot++;
                int now;
                do
                {
                    now=sta.top();
                    sta.pop();
                    scc[now]=tot;
                }while(now!=v);         
            }
        }
        else low[u]=min(low[u],dfn[v]);
    }
    if(u==1&&child>1) cut[u]=1;
}
 
int main()
{
//  freopen("split1.in","r",stdin);
  freopen("A.in","r",stdin);
  freopen("std.out","w",stdout);
    n=read(),m=read();
    for(int i=1;i<=m;i++)
    {
        u[i]=read(),v[i]=read();
        adde(u[i],v[i]),adde(v[i],u[i]);
        d[u[i]]++,d[v[i]]++;
    }
    for(int i=2;i<=n;i++) deg[i]=1;
    tarjan(1,0);
    for(int i=1;i<=m;i++)
    {
        if(cut[u[i]]&&cut[v[i]]) putchar('1');
        else if((!cut[u[i]])&&(!cut[v[i]])) putchar('0');
        else
        {
            if(cut[v[i]]) swap(u[i],v[i]);
            if(d[v[i]]==1&&deg[u[i]]<=2) putchar('0');
            else putchar('1');
        }
    }
    return 0;
}
