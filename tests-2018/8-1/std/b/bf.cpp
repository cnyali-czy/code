#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
typedef long long ll;
typedef double dd;
#define For(i,j,k) for (int i=(int)j;i<=(int)k;++i)
#define Forr(i,j,k) for (int i=(int)j;i>=(int)k;--i)
#define Set(a,p) memset(a,p,sizeof(a))
using namespace std;

template<typename T>bool chkmax(T &a,T b) { return a<b?a=b,1:0; }
template<typename T>bool chkmin(T &a,T b) { return a>b?a=b,1:0; }

const int maxn=100000+100;
const int N=15;
struct node {
	int to,nxt;
}e[maxn<<1];
int n,m,tot;
int head[maxn],a[maxn],deep[maxn],f[maxn][N+1];
ll val[maxn];

inline void file() {
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
}

inline int read() {
	int x=0,p=1;
	char c=getchar();
	while (!isdigit(c)) { if (c=='-') p=-1; c=getchar();}
	while (isdigit(c)) { x=(x<<1)+(x<<3)+(c-'0'); c=getchar();}
	return x*p;
}

inline void add(int from,int to) {
	tot++;
	e[tot].to=to; e[tot].nxt=head[from]; head[from]=tot;
}

void dfs(int u) {
	for (int i=head[u];i!=0;i=e[i].nxt) {
		int v=e[i].to;
		if (v==f[u][0]) continue;
		f[v][0]=u; deep[v]=deep[u]+1;
		dfs(v);
	}
}

inline int Lca(int x,int y) {
	if (deep[x]<deep[y]) swap(x,y);
	Forr (i,N,0)
		if (deep[f[x][i]]>=deep[y]) x=f[x][i];
	if (x==y) return x;
	Forr (i,N,0)
		if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}

int main() {
	file();
	n=read(); m=read();
	For (i,1,n) a[i]=read();
	For (i,1,n-1) {
		int x=read(),y=read();
		add(x,y); add(y,x);
	}
	deep[1]=1; dfs(1);
	For (j,1,N)
		For (i,1,n)
			f[i][j]=f[f[i][j-1]][j-1];
	while (m--) {
		int w=read(),x=read(); 
		if (w==1) {
			For (i,1,n)
				if (a[i])
					val[Lca(i,x)]+=1ll*i;
		}
		else a[x]^=1;
	}
	For (i,1,n) printf("%lld\n",val[i]);
	return 0;
}
