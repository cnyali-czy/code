#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
#define For(i,a,b) for(i=(a),i<=(b);++i)
#define Forward(i,a,b) for(i=(a),i>=(b);--i)
template<typename T>inline void read(T &x)
{
	T f=1;x=0;char c;
	for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+(c^48);
	x*=f;
}
using namespace std;
void file()
{
#ifndef ONLINE_JUDGE
	freopen("running9.in","r",stdin);
	freopen("running9.out","w",stdout);
#endif
}

const int MAXN=1e5+7;

static int n;

static struct edge
{
	int v,nxt;
}p[MAXN<<1];

static int head[MAXN],e,w[MAXN];

inline void add(int u,int v){p[++e]=(edge){v,head[u]};head[u]=e;}

inline void init()
{
	read(n);
	static int u,v;
	Rep(i,1,n-1)read(u),read(v),add(u,v),add(v,u);
	Rep(i,1,n)read(w[i]);
}

namespace Segment_Tree
{
	static int s[MAXN*40],cnt,son[MAXN*40][2],lashed;

	void Add(int &now,int las,int l,int r,int x)
	{
		s[now=++cnt]=s[las]+1;
		if(l==r)return;
		static int mid;mid=(l+r)>>1;
		if(x<=mid)Add(son[now][0],son[las][0],l,mid,x),son[now][1]=son[las][1];
		else Add(son[now][1],son[las][1],mid+1,r,x),son[now][0]=son[las][0];
	}

	int query(int now,int las,int l,int r,int x)
	{
		if(s[now]==s[las])return 0;
		if(l==r)return s[now]-s[las];
		static int mid;mid=(l+r)>>1;
		return x<=mid?query(son[now][0],son[las][0],l,mid,x):
			query(son[now][1],son[las][1],mid+1,r,x);
	}
}

using namespace Segment_Tree;

static int dep[MAXN],rt[MAXN][2],sz[MAXN];

void dfs(int u,int fr)
{
	dep[u]=dep[fr]+1;sz[u]=1;
	for(register int v=head[u];v;v=p[v].nxt)if(p[v].v^fr)
	{
		rt[p[v].v][0]=lashed;
		dfs(p[v].v,u);sz[u]+=sz[p[v].v];
	}
	Add(rt[u][1],lashed,1,n,dep[u]);
	lashed=rt[u][1];
}

const int mod=998244353;

typedef unsigned long long uint64;

inline int ad(int u,int v){return (u+=v)>=mod?u-mod:u;}

static int ans,fa[MAXN];

void getans(int u,int fr)
{
	fa[u]=fr;
	static int la;
	for(register int v=head[u];v;v=p[v].nxt)if(p[v].v^fr)
	{
		getans(p[v].v,u);
		if(!w[u])continue;
		la=dep[u]+w[u]<=n?query(rt[p[v].v][1],rt[p[v].v][0],1,n,dep[u]+w[u]):0;
		ans=ad(ans,(uint64)(n-sz[p[v].v])*la%mod);
	}
	if(!w[u])ans+=n;
	else
	{
		static int ff;
		ff=fa[u];
		if(ff&&dep[u]+w[u]-2>=1&&dep[u]+w[u]-2<=n)
			la=mod-query(rt[u][1],rt[u][0],1,n,dep[u]+w[u]-2);
		else la=0;
		while(ff)
		{
			la=ad(la,w[u]-dep[u]+2*dep[ff]<=n&&w[u]-dep[u]+2*dep[ff]>=1?
				query(rt[ff][1],rt[ff][0],1,n,w[u]-dep[u]+2*dep[ff]):0);
			if(fa[ff]&&w[u]-dep[u]+2*dep[ff]-2>=1&&w[u]-dep[u]+2*dep[ff]-2<=n)
				la=ad(la,mod-query(rt[ff][1],rt[ff][0],1,n,w[u]-dep[u]+2*dep[ff]-2));
			ff=fa[ff];
		}
		ans=ad(ans,(uint64)la*sz[u]%mod);
	}
}

inline int power(int u,int v)
{
	static int sm;
	for(sm=1;v;v>>=1,u=(uint64)u*u%mod)if(v&1)
		sm=(uint64)sm*u%mod;
	return sm;
}

inline void solve()
{
	dfs(1,0);
	getans(1,0);
	printf("%d",(uint64)ans*power((uint64)n*n%mod,mod-2)%mod);
	cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
}

int main()
{
	file();
	init();
	solve();
	return 0;
}

