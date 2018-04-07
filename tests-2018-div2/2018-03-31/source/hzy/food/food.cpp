#include<bits/stdc++.h>
using namespace std;
struct node
{
	long long s,t;
}a[1010];
inline bool cmp(node x,node y)
{
	if(x.s<y.s)
		return 1;
	return 0;
}
long long n,ans;
inline bool ok(long long x)
{
	for(register long long t=x,i=1;i<=n;i++)
		if(t>=a[i].s)
			t+=a[i].t+x;
		else
			return 0;
	return 1;
}
int main()
{
	freopen("food.in","r",stdin);
	freopen("food.out","w",stdout);
	scanf("%lld",&n);
	for(register long long i=1;i<=n;i++)
		scanf("%lld%lld",&a[i].s,&a[i].t);
	sort(a+1,a+n+1,cmp);
	long long l=a[1].s,r=a[n].s;
	while(l<=r)
	{
		long long mid=(l+r)/2;
		if(ok(mid))
		{
			ans=mid;
			r=mid-1;
		}
		else
			l=mid+1;
	}
	printf("%lld",ans);
	return 0;
}
