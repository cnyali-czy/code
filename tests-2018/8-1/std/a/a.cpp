#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
typedef long long ll;
typedef double dd;
#define For(i,j,k) for (int i=j;i<=k;++i)
#define Forr(i,j,k) for (int i=j;i>=k;--i)
#define Set(a,p) memset(a,p,sizeof(a))
using namespace std;

template<typename T>bool chkmax(T &a,T b) { return a<b?a=b,1:0; }
template<typename T>bool chkmin(T &a,T b) { return a>b?a=b,1:0; }

const int maxn=5000+10;
const int maxN=1000000+100;
const int N=5000;
int n,m,modd;
int p[maxn],pm[maxn],sum[maxN],dp[maxn][maxn],Dp[2][maxn];

inline void file() {
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
}

inline int read() {
	int x=0,p=1;
	char c=getchar();
	while (!isdigit(c)) { if (c=='-') p=-1; c=getchar();}
	while (isdigit(c)) { x=(x<<1)+(x<<3)+(c-'0'); c=getchar();}
	return x*p;
}

inline void Add(int &a,int b) {
	a+=b;
	if (a>=modd) a-=modd;
	if (a<0) a+=modd;
}

inline void init() {
	dp[0][0]=1;
	For (i,1,N)
		For (j,1,i)
			Add(dp[i][j],(dp[i-1][j-1]+1ll*dp[i-1][j]*(j-1)%modd)%modd);
	p[0]=1;
	For (i,1,N) p[i]=1ll*p[i-1]*i%modd;
	pm[0]=1;
	For (i,1,min(m,N)) pm[i]=1ll*pm[i-1]*(m-i+1)%modd;
}

int main() {
	file();
	n=read(); m=read(); modd=read();
	init();
	sum[0]=1;
	int pos=0,l=0,lst=0;
	For (i,1,n) {
		Set(Dp[pos],0);
		l=read();
		For (j,1,l) {
			Dp[pos][j]=1ll*sum[i-1]*dp[l][j]%modd*pm[j]%modd;
			if (i>1 && j<=lst)
				Add(Dp[pos][j],-1ll*dp[l][j]*Dp[pos^1][j]%modd*p[j]%modd);
			Add(sum[i],Dp[pos][j]);
		}
		pos^=1; lst=l;
	}
	printf("%d",sum[n]);
	cerr << clock() << endl;
	return 0;
}
