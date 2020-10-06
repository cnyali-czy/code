#include<cstdio>
#include<algorithm>
using namespace std;const int N=1e5+10;const int S=40;
typedef unsigned long long ll;const ll mod=998244353;
struct poly
{
	int a[S+10];
	inline int& operator [](const int & x){return a[x];}
	poly(){for(int i=0;i<S;i++)a[i]=0;}
	friend poly operator * (poly a,poly b)
	{
		poly c;for(int i=0;i<S;i++)
			for(int j=0;j<S&&i+j<S;j++)c[i+j]+=a[i]*b[j];return c;	
	} 
	friend poly operator +(poly a,poly b){poly c;for(int i=0;i<S;i++)c[i]=a[i]+b[i];return c;}
	friend poly operator -(poly a,poly b){poly c;for(int i=0;i<S;i++)c[i]=a[i]-b[i];return c;}
	poly operator <<(const int& x){poly c;for(int i=S-1;i>=x;i--)c[i]=a[i-x];return c;}
}a,b,c,q,fz,fm,fz1,fm1;int n;
ll f0[N];ll c0[N];ll f1[N];ll c1[N];ll f2[N];ll c2[N];ll g[N];ll sqr[N];
inline void calc(poly& fz,poly& fm,ll* f,ll* c)//暴力除法
{
	for(int i=0;i<S;i++)f[i]=(mod+fz[i])%mod;
	for(int i=0;i<S;i++)c[i]=(mod-fm[i])%mod;(c[0]+=1)%=mod;
	for(int i=0;i<=n;i++)
		for(int j=1;j<S&&j<=i;j++)(f[i]+=f[i-j]*c[j])%=mod;
}
int main()
{
	freopen("A.in","r",stdin);freopen("std.out","w",stdout);
	a[8]=16;a[6]=12;a[4]=20;a[2]=4;b[8]=9;b[6]=2;b[4]=23;b[2]=6;b[0]=1;
	c[8]=4;c[6]=-4;c[4]=24;c[2]=4;c[0]=4;q[12]=-1;q[10]=-3;q[6]=+5;q[2]=-3;q[0]=+1;
	scanf("%d",&n);//按照推出来的柿子计算f1,f2,f3
	fz=((b*b)<<3)-a*((c<<3)-q);fm=((c<<3)-q)*((a<<1)-q)-((b*b)<<4);calc(fz,fm,f0,c0);
	fz=b*q;fm=((c<<3)-q)*((a<<1)-q)-((b*b)<<4);calc(fz,fm,f1,c1);
	fz1=c*fm+((b*fz)<<1);fm1=fm*(q-(c<<3));calc(fz1,fm1,f2,c2);
	g[0]=1;g[2]=1;for(int i=4;i<=n;i++)g[i]=(g[i-2]+g[i-4])%mod;
	for(int i=1;i<=n;i++)sqr[i]=(ll)i*i%mod;
	ll ans=(g[n-1]+g[n-3])*sqr[n-1]%mod*n%mod;
	for(int i=0;i<=n;i++)printf("%d%c",g[i],i==n?'\n':' ');
	for(int i=0;i<=n;i++)printf("%d%c",f0[i],i==n?'\n':' ');
	for(int i=0;i<=n;i++)printf("%d%c",f1[i],i==n?'\n':' ');
	for(int i=0;i<=n;i++)printf("%d%c",f2[i],i==n?'\n':' ');
	for(int i=2;i<=n-2;i++)
	{
		ll ret=0;(ret+=g[i-1]*f0[n-i-1])%=mod;(ret+=g[i-2]*f1[n-i-2]*2)%=mod;
		if(3<=i&&i<=n-3)(ret+=g[i-3]*f2[n-i-3])%=mod;
		(ans+=ret*sqr[i-1]%mod*i)%=mod;
	}printf("%I64d",ans);//拜拜程序~
}
