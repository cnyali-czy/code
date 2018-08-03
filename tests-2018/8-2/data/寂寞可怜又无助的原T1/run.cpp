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
	for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+(c^48);
	x*=f;
}
using namespace std;
void file()
{
#ifndef ONLINE_JUDGE
	freopen("run10.in","r",stdin);
	freopen("run10.out","w",stdout);
#endif
}

const int MAXN=3e5+7;

static struct edge
{
	int v,nxt;
}p[MAXN<<1];

static int head[MAXN],e,s[3],n;

inline void add(int u,int v){p[++e]=(edge){v,head[u]};head[u]=e;}

inline void init()
{
	read(n);
	static int u,v;
	Rep(i,1,n-1)read(u),read(v),add(u,v),add(v,u);
	Rep(i,0,2)read(s[i]);
}

static int ans,dep[MAXN][3];

void dfs(int fr,int u,int s,int dp)
{
	dep[u][s]=dp;
	for(register int v=head[u];v;v=p[v].nxt)if(p[v].v^fr)
		dfs(u,p[v].v,s,dp+1);
}

inline void solve()
{
	Rep(i,0,2)dfs(0,s[i],i,0);
	ans=n;
	Rep(i,1,n)Chkmin(ans,max(dep[i][0],max(dep[i][1],dep[i][2])));
	printf("%d\n",ans);
}

int main()
{
	file();
	init();
	solve();
	cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
	return 0;
}

