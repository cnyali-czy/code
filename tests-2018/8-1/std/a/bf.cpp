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
int n,m,modd;
int ans;
int a[maxn],s[maxn][maxn];

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

void dfs(int nn,int p) {
	if (nn==n+1) {
		++ans;
		return ;
	}
	For (i,1,m) {
		if (p>1 && s[nn][p-1]==i) continue;
		s[nn][p]=i;
		if (p==a[nn]) {
			if (nn==1) dfs(nn+1,1);
			else {
				int s1[10]={0},s2[10]={0};
				For (j,1,a[nn-1]) s1[s[nn-1][j]]=1;
				For (j,1,a[nn]) s2[s[nn][j]]=1;
				int flag=0;
				For (j,1,m)
					if ((s1[j] && !s2[j]) || (!s1[j] && s2[j])) {
						flag=1; break;
					}
				if (!flag) continue;
				dfs(nn+1,1);
			}
		}
		else dfs(nn,p+1);
	}
}

int main() {
	file();
	n=read(); m=read(); modd=read();
	For (i,1,n) a[i]=read();
	dfs(1,1);
	printf("%d",ans%modd);
	return 0;
}
