#include<bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(register int i(a),end_##i(b);i<=end_##i;i++)
#define i64 long long
i64 power(i64 a,i64 b,i64 p)//快速幂
{
	i64 r=1;
	while(b)
	{
		if(b&1)
			r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}
int check(i64 p)//判断质数
{
	fr(i,2,sqrt(p))
		if(p%i==0)
			return 0;
	return 1;
}
i64 getg(i64 n)//求原根
{
	i64 a[20],c=0;
	i64 k=n-1;
	fr(i,2,sqrt(k))
		if(k%i==0)
		{
			a[++c]=i;
			while(k%i==0)
				k/=i;
			end_i=sqrt(k);
		}
	if(k!=1)
		a[++c]=k;
	fr(g,2,n)
	{
		int flag=1;
		fr(i,1,c)
			if(power(g,(n-1)/a[i],n)==1)
			{
				flag=0;
				break;
			}
		if(flag)
			return g;
	}
	return -1;
}
void find_ntt_mod(i64 p,i64 cnt,i64 g)//2^p|mod-1 ~~g=g~~
{
	i64 i=1;
	while(cnt)
	{
		if(check((i<<p)+1)&&getg((i<<p)+1)==g)
		{
			printf("%lld*2^%lld=%lld,g=%lld\n",i,p,(i<<p)+1,getg((i<<p)+1));
			cnt--;
		}
		i++;
	}
}
int main()
{
	find_ntt_mod(21,30,7);
	return 0;
}
