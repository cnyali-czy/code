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
#define lson l,mid
#define rson mid+1,r
using namespace std;

template<typename T>bool chkmax(T &a,T b) { return a<b?a=b,1:0; }
template<typename T>bool chkmin(T &a,T b) { return a>b?a=b,1:0; }

const int maxn=300000+1000;
const int maxN=12000000+1000;
struct node {
	int to,nxt;
}e[maxn<<1];
int n,m;
int tot;
int head[maxn],a[maxn];
int rt[maxN],ls[maxN],rs[maxN],s1[maxN];
ll Ans,val[maxn],s2[maxN];

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

inline void pushup(int h) {
	s1[h]=s1[ls[h]]+s1[rs[h]];
	s2[h]=s2[ls[h]]+s2[rs[h]];
}

void update(int &h,int l,int r,int p,int k1,int k2) {
	if (!h) h=++tot;
	if (l==r) {
		s1[h]+=k1; s2[h]+=1ll*k2;
		return ;
	}
	int mid=(l+r)/2;
	if (p<=mid) update(ls[h],lson,p,k1,k2);
	else update(rs[h],rson,p,k1,k2);
	pushup(h);
}

int merge(int x,int y,int l,int r) {
	if (!x) return y;
	if (!y) return x;
	if (l==r) {
		s1[x]+=s1[y]; s2[x]+=s2[y];
		return x;
	}
	int mid=(l+r)/2;
	Ans+=1ll*s1[rs[x]]*s2[ls[y]];
	Ans+=1ll*s1[rs[y]]*s2[ls[x]];
	ls[x]=merge(ls[x],ls[y],lson);
	rs[x]=merge(rs[x],rs[y],rson);
	pushup(x);
	return x;
}

void dfs(int u,int fa) {
	for (int i=head[u];i!=0;i=e[i].nxt) {
		int v=e[i].to;
		if (v==fa) continue;
		dfs(v,u);
		Ans=0;
		rt[u]=merge(rt[u],rt[v],0,m);
		val[u]+=Ans;
	}
}

int main() {
	file();
	n=read(); m=read();
	For (i,1,n) a[i]=read();
	For (i,1,n-1) {
		int x=read(),y=read();
		add(x,y); add(y,x);
	}
	tot=0;
	For (i,1,n)
		update(rt[i],0,m,0,0,a[i]*i);
	For (i,1,m) {
		int w=read(),x=read();
		if (w==1) {
			update(rt[x],0,m,i,1,0);
			if (a[x]) val[x]+=1ll*x;
		}
		else {
			a[x]^=1;
			if (a[x]) update(rt[x],0,m,i,0,x);
			else update(rt[x],0,m,i,0,-x);
		}
	}
	dfs(1,0);
	For (i,1,n) printf("%lld\n",val[i]);
	cerr << clock() << endl;
	return 0;
}
