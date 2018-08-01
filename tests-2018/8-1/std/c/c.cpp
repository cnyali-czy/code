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

const int maxn=100;
const int N=50;
const int inf=0x3f3f3f3f;
const int maxd=50;
int n;
int a[maxn],dis[maxn][maxn];
int d[4][4]={{-4,-3,-1,4},{-4,1,3,4},{-4,-1,1,4},{-4,-1,1,4}};

inline void file() {
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
}

inline int read() {
	int x=0,p=1;
	char c=getchar();
	while (!isdigit(c)) { if (c=='-') p=-1; c=getchar();}
	while (isdigit(c)) { x=(x<<1)+(x<<3)+(c-'0'); c=getchar();}
	return x*p;
}

inline void init() {
	Set(dis,inf);
	For (i,1,N)
		For (j,0,3) {
			int k=i%4;
			if (i+d[k][j]>=0) dis[i][i+d[k][j]]=1;
		}
	For (i,1,N) dis[i][i]=0;
	For (k,1,N)
		For (i,1,N) if (dis[i][k]!=inf)
			For (j,1,N) if (dis[k][j]!=inf)
				chkmin(dis[i][j],dis[i][k]+dis[k][j]);
}

bool dfs(int D,int sum,int pos,int lst) {
	if (sum<=0) return 1;
	if (sum>D) return 0;
	int k=pos%4;
	For (i,0,3) {
		int p=pos+d[k][i];
		if (p<1 || p>n || p==lst) continue;
		int P=a[p];
		swap(a[p],a[pos]);
		if (dfs(D-1,sum-dis[p][P]+dis[pos][P],p,pos)) return 1;
		swap(a[p],a[pos]);
	}
	return 0;
}

int main() {
	file();
	init();
	n=read(); n*=4;
	int sum=0,pos=0,ans=-1;
	For (i,1,n) a[i]=read(),sum+=dis[i][a[i]];
	For (i,1,n) if (a[i]==1) {
		pos=i; break;
	}
	sum-=dis[pos][1];
	for (int i=sum;;++i)
		if (dfs(i,sum,pos,0)) {
			ans=i; break;
		}
	printf("%d",ans);
	return 0;
}
