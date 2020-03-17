#include<stdio.h>
#include<vector>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#define i64 long long
#define int long long
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
const int N=510,mod=1e9+7;
i64 n,d[N][N],f[N],C[N][N],inv[N],go[N][N],lca[N][N],w[N],ans;
i64 vis[N][N],F[N][N];
int u,v;
std::vector<int> e[N];
i64 &Add(i64 &a,i64 b){ return a=(a+b)%mod; }
void dfs(int u)
{
	f[u]=1;
	for(auto v:e[u]) if(d[1][u]<d[1][v])
	{
		dfs(v); w[u]+=w[v]; f[u]=f[u]*f[v]%mod*C[w[u]][w[v]]%mod;
	}
	w[u]++;
}
i64 calc(int U,int V)
{
	if(!U) return 0;
	if(!V) return 1;
	if(vis[U][V]) return F[U][V];
	vis[U][V]=1; i64 p=w[V]*inv[w[U]+w[V]]%mod;
	return F[U][V]=(p*calc(U,go[V][v])+(mod+1-p)*calc(go[U][u],V))%mod;
}
i64 solve(int u,int v)
{
	::u=u; ::v=v;
	fr(i,1,n) fr(j,1,n) vis[i][j]=0;
	int l=lca[u][v];
	if(l==u) return 0;
	if(l==v) return 1;
	return calc(go[l][u],go[l][v]);
}
signed main()
{
	freopen("C.in", "r", stdin);freopen("hh.out", "w", stdout);
	n=read();
	fr(i,1,n) fr(j,1,n) d[i][j]=i==j?0:1ll<<50;
	fr(i,1,n-1){ int u=read(),v=read(); d[u][v]=d[v][u]=1; e[u].push_back(v); e[v].push_back(u); }
	fr(k,1,n) fr(i,1,n) fr(j,1,n) d[i][j]=std::min(d[i][j],d[i][k]+d[k][j]);
	fr(i,1,n) inv[i]=power(i,mod-2,mod);
	fr(i,0,n) C[i][0]=C[i][i]=1;
	fr(i,1,n) fr(j,1,n) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	fr(i,1,n) fr(j,1,n) if(i!=j) fr(k,1,n) if(d[i][k]==1&&d[k][j]==d[i][j]-1) go[i][j]=k;
	fr(i,1,n) fr(j,1,n)
	{
		int k=i;
		while(k!=j&&d[1][go[k][j]]<d[1][k]) k=go[k][j];
		lca[i][j]=k;
	}
	dfs(1);
	fr(i,1,n) fr(j,1,n) if(i>j) ans+=solve(i,j);
	printf("%d\n",(signed)(ans%mod*f[1]%mod));
	return 0;
}
