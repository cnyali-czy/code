#include<bits/stdc++.h>
using namespace std;
inline bool zs(int x)
{
	for(register int i=2;i*i<=x;i++)
		if(x%i==0)
			return 0;
	if(x>1)
		return 1;
	return 0;
}
int main()
{
	int x;
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
	scanf("%d",&x);
	if(zs(x))
	{
		puts("2");
		return 0;
	}
	int i=2,ans=1;
	while(i<=x)
	{
		int s=0;
		while(x%i==0)
		{
			x/=i;
			s++;
		}
		ans*=s+1;
		i++;
	}
	printf("%d",ans);
	return 0;
}
