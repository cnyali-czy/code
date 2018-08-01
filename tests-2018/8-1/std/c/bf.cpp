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
int n;
int a[maxn][maxn],s[maxn][maxn];
int d[4][2]={{0,1},{1,0},{0,-1},{-1,0}};

inline void file() {
	freopen("c.in","r",stdin);
	freopen("bf.out","w",stdout);
}

inline int read() {
	int x=0,p=1;
	char c=getchar();
	while (!isdigit(c)) { if (c=='-') p=-1; c=getchar();}
	while (isdigit(c)) { x=(x<<1)+(x<<3)+(c-'0'); c=getchar();}
	return x*p;
}

inline void init() {
	int cnt=0;
	For (i,1,n/4)
		For (j,1,4)
			s[i][j]=++cnt;
}

inline int Cnt() {
	int cnt=0;
	For (i,1,n/4)
		For (j,1,4)
			if (a[i][j]!=s[i][j]) ++cnt;
	return (cnt+1)/2;
}

bool dfs(int D) {
	int t=Cnt();
	if (t==0) return 1;
	if (D<t) return 0;
	int x=0,y=0;
	For (i,1,n/4)
		For (j,1,4)
			if (a[i][j]==1) {
				x=i; y=j; break;
			}
	For (i,0,3) {
		int xx=x+d[i][0],yy=y+d[i][1];
		if (xx==0 || xx==n/4+1) continue;
		if (yy==0) yy=4;
		if (yy==5) yy=1;
		swap(a[x][y],a[xx][yy]);
		if (dfs(D-1)) return 1;
		swap(a[x][y],a[xx][yy]);
	}
	return 0;
}

int main() {
	file();
	n=read(); n*=4;
	init();
	For (i,1,n/4)
		For (j,1,4)
			a[i][j]=read();
	int ans=-1;
	for (int i=0;i<=2*n;++i)
		if (dfs(i)) {
			ans=i; break;
		}
	printf("%d\n",ans);
	return 0;
}
