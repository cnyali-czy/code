#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
#define For(i,a,b) for(i=(a),i<=(b);++i)
#define Forward(i,a,b) for(i=(a),i>=(b);--i)
#define Chkmin(a,b) a=a<b?a:b
template<typename T>inline void read(T &x)
{
	T f=1;x=0;char c;
	for(c=getchar();!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar())x=x*10+(c^48);
	x*=f;
}

inline void write(int u)
{
	if(!u){putchar('0');putchar('\n');return;}
	static unsigned short st[31],t;
	for(t=0;u;u/=10)st[++t]=u%10;
	for(;t;putchar(st[t--]^48));
	putchar('\n');
}

using namespace std;
void file()
{
	freopen("road10.in","r",stdin);
	freopen("road10.out","w",stdout);
}

const int MAXN=1e5+7,MAXM=2e5+7;

static int n,m,w[MAXN<<1],Q;

static struct edge
{
	int v,nxt;
}p[MAXM<<1],q[MAXN<<1];

static int head[MAXN],hed[MAXN<<1],e;

inline void add(int u,int v){p[++e]=(edge){v,head[u]};head[u]=e;}
inline void Add(int u,int v){q[++e]=(edge){v,hed[u]};hed[u]=e;}

inline void init()
{
	read(n);read(m);read(Q);
	static int u,v;
	Rep(i,1,m)read(u),read(v),add(u,v),add(v,u);
	Rep(i,1,n)read(w[i]);
}

static int ans[MAXN],dfn[MAXN],low[MAXN],dfs_clock,sta[MAXN],tp,cnt;

void tarjan(int u,int fr)
{
	dfn[u]=low[u]=++dfs_clock;sta[++tp]=u;
	for(register int v=head[u];v;v=p[v].nxt)
	{
		if(!dfn[p[v].v])
		{
			tarjan(p[v].v,u);
			Chkmin(low[u],low[p[v].v]);
			if(low[p[v].v]>=dfn[u])
			{
				Add(u,++cnt);w[cnt]=w[u];
				do
				{
					Chkmin(w[cnt],w[sta[tp]]);
					Add(cnt,sta[tp--]);
				}while(sta[tp+1]^p[v].v);
			}
		}
		else if(p[v].v^fr)Chkmin(low[u],dfn[p[v].v]);
	}
}

void dfs(int u,int c)
{
	Chkmin(c,w[u]);
	if(u<=n)ans[u]=c;
	for(register int v=hed[u];v;v=q[v].nxt)dfs(q[v].v,c);
}

inline void solve()
{
	e=0;cnt=n;
	tarjan(1,0);
	dfs(1,1e9+7);
	static int u;
	Rep(i,1,Q)read(u),write(ans[u]);
}

int main()
{
	file();
	init();
	solve();
	cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
	return 0;
}

