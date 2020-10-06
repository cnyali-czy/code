#include <bits/stdc++.h>
typedef long long ll;

const int N=5e5+5,P=998244353;
int T,n,a[N],b[N],f[N],v[N],Ans;
ll Pow(ll a,ll b,ll s=1){for(b<0?b=0:0;b;b>>=1,a=a*a%P)if(b&1)s=s*a%P;return s;}

int main()
{
	freopen("A.in", "r", stdin);
	freopen("std.out", "w", stdout);
	for(scanf("%d",&T);T--;printf("%d\n",Ans))
	{
		scanf("%d",&n);
		for(int i=1;i<=n;++i)scanf("%d",a+i),v[i]=b[i]=f[i]=0;
		for(int i=1,j,c;i<=n;++i)if(!v[i])
			{for(j=a[i],c=0;!v[j];j=a[j])v[j]=1,++c;++b[c];}
		for(int i=1;i<=n;++i)for(int j=i<<1;j<=n;j+=i)f[j]+=b[i]*i;
		if(b[1])for(int i=(Ans=Pow(b[1],b[1]-2),2);i<=n;++i)
			b[i]?Ans=Ans*Pow(f[i]+b[i]*i,b[i]-1)%P*f[i]%P:0;
		else if(b[2])for(int i=(Ans=Pow(b[2]*2,b[2]-1),3);i<=n;++i)
			b[i]?Ans=Ans*Pow(f[i]+b[i]*i,b[i]-1)%P*f[i]%P:0;
		else Ans=0;
	}
	return 0;
}
