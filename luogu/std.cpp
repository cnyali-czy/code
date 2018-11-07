#define REP(i, s, e) for(register int i = s; i <= e ; i++)

#include<queue>
#include<vector>
#include<string.h>
#include<iostream>
#include<algorithm>
#define maxn 300005
using namespace std;
struct nod{
    int p,q,r;
}a[maxn],b[maxn],c[2][maxn];
bool cmp(nod x,nod y){return x.q<y.q;}
bool cmp2(nod x,nod y){return x.r<y.r;}
int cnt0,cnt[2],n,m,s[maxn],e[maxn],ans[maxn],siz[maxn],dfn[maxn],dep[maxn],vis[maxn],t[maxn],sum[maxn],fa[maxn][21];
vector<int> edge[maxn]; queue<nod> q;

int lowbit(int x){return x&(-x);}
void ins(int x,int v){if(!x) return; for(int i=x;i<=n;i+=lowbit(i)) sum[i]+=v;}
int ques(int x){int a=0; for(int i=x;i>0;i-=lowbit(i)) a+=sum[i]; return a;}

void addedge(int x,int y){edge[x].push_back(y),edge[y].push_back(x);}
void add(int x,int y,int k,int baze) {nod &now=c[k][++cnt[k]]; now.p=x,now.q=y,now.r=dep[k?y:x]-baze;}
void dfs(int x)
{
    for(int i=1;i<=20;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    siz[x]=1,vis[x]=1,dfn[x]=++cnt0;
    for(int i=0;i<edge[x].size();i++)
        if(!vis[edge[x][i]])
            fa[edge[x][i]][0]=x,dep[edge[x][i]]=dep[x]+1,dfs(edge[x][i]),siz[x]+=siz[edge[x][i]];
}
int lca(int x,int y)
{
    if(x==y)    return x;
    if(dep[x]<dep[y])
        swap(x,y);
    for(int i=20;i>=0;i--)
        if(dep[fa[x][i]]>=dep[y])
            x=fa[x][i];
    if(x==y)    return x;
    for(int i=20;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}

int main()
{
    int x,y,g,now1=1,now2=1;
    cin>>n>>m;
    for(int i=1;i<n;i++)
        cin>>x>>y,addedge(x,y);
    for(int i=1;i<=n;i++)
        cin>>t[i];
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=m;i++)
        cin>>s[i]>>e[i];
    dep[1]=1,dfs(1);
    for(int i=1;i<=n;i++)
        a[i].q=t[i]+dep[i],b[i].q=dep[i]-t[i],a[i].p=b[i].p=i;
    sort(a+1,a+n+1,cmp),sort(b+1,b+n+1,cmp);
    for(int i=1;i<=m;i++)
    {
        int st=s[i],en=e[i];g=lca(st,en);
        if(g==st)   add(en,st,1,0);
        else if(g==en)  add(st,en,0,0);
        else
        {
            x=st;
            for(int i=20;i>=0;i--)
                if(dep[fa[x][i]]>dep[g])
                    x=fa[x][i];
            add(st,x,0,0),add(en,g,1,dep[st]-dep[x]+1);
        }
    }
    sort(c[0]+1,c[0]+cnt[0]+1,cmp2),sort(c[1]+1,c[1]+cnt[1]+1,cmp2);
    for(int i=1;i<=n;i++)
    {
        while(a[i].q!=a[i-1].q && !q.empty()) {nod now=q.front();q.pop();ins(now.p,-1),ins(now.q,1);}
        for(;now1<=cnt[0] && c[0][now1].r<=a[i].q;now1++)
            if(a[i].q!=a[i-1].q && c[0][now1].r==a[i].q)
                ins(dfn[c[0][now1].p],1),ins(dfn[fa[c[0][now1].q][0]],-1),q.push((nod){dfn[c[0][now1].p],dfn[fa[c[0][now1].q][0]],0});
        ans[a[i].p]+=ques(dfn[a[i].p]+siz[a[i].p]-1)-ques(dfn[a[i].p]-1);
    }
    while(!q.empty()) {nod now=q.front();q.pop();ins(now.p,-1),ins(now.q,1);}
    for(int i=1;i<=n;i++)
    {
        while(b[i].q!=b[i-1].q && !q.empty()) {nod now=q.front();q.pop();ins(now.p,-1),ins(now.q,1);}
        for(;now2<=cnt[1] && c[1][now2].r<=b[i].q;now2++)
            if(b[i].q!=b[i-1].q && c[1][now2].r==b[i].q)
                ins(dfn[c[1][now2].p],1),ins(dfn[fa[c[1][now2].q][0]],-1),q.push((nod){dfn[c[1][now2].p],dfn[fa[c[1][now2].q][0]],0});
        ans[b[i].p]+=ques(dfn[b[i].p]+siz[b[i].p]-1)-ques(dfn[b[i].p]-1);
    }
    for(int i=1;i<=n;i++)
        cout<<ans[i]<<" ";
    return 0;
}
