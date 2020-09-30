#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9') {if(c=='-')flag=1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x+(x<<2)<<1)+ c-'0';c=getchar();}
    return flag?-x:x;
}
const int N=405,mod=1e9+7;
int n;
struct Matrix
{
	int a[N][N];
	void Swap(int x,int y) {for(int i=1;i<=n;++i) swap(a[x][i],a[y][i]);}
	void cg(int x,int k) {for(int i=1;i<=n;++i) a[x][i]=(1ll*a[x][i]*k%mod+mod)%mod;}
	void update(int x,int y,int k) {for(int i=1;i<=n;++i)a[x][i]=((a[x][i]+(1ll*a[y][i]*k%mod))%mod+mod)%mod;}
	void print() {for(int i=1;i<=n;++i) {for(int j=1;j<=n;++j) printf("%d ",a[i][j]);printf("\n");}}
}A,B;
inline int inv(int a)
{
    int res=1,b=mod-2;
    for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)res=1ll*res*a%mod;
    return res;
}
int main()
{
	freopen("matrix.in", "r", stdin);
	freopen("bf2.out", "w", stdout);
	cin>>n;
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j)
	{
		double x;scanf("%lf",&x);
		if(x>1e-9)A.a[i][j]=rand();
	}
	for(int i=1;i<=n;++i) B.a[i][i]=1;
	for(int i=1;i<=n;++i)
	{
		if(!A.a[i][i])
		{
			for(int j=i+1;j<=n;++j) if(A.a[j][i]) 
			{A.Swap(i,j),B.Swap(i,j);break;}
		}
		if(!A.a[i][i]) {printf("No Solution\n");return 0;}
		B.cg(i,inv(A.a[i][i])),A.cg(i,inv(A.a[i][i]));
		for(int j=i+1;j<=n;++j) B.update(j,i,-A.a[j][i]),A.update(j,i,-A.a[j][i]);
	}
	for(int i=n-1;i;--i) for(int j=i+1;j<=n;++j)
    B.update(i,j,-A.a[i][j]),A.update(i,j,-A.a[i][j]);
    B.print();
}
