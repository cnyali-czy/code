/**********************************************************
	File:exercise.cpp
	Author:huhao
	Email:826538400@qq.com
	Created time:2018-2-25 14:05:36
**********************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(long long i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(long long i=(a),_end_=(b);i>=_end_;i--)
long long read()
{
	long long r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#define N 1500
long long a,f[N],n=1440,k;
char s[100010];
int main()
{
	freopen("exercise.in","r",stdin);
	freopen("exercise.out","w",stdout);
	a=read();
	f[1]=-1;
	fr(i,1,read())
	{
		scanf("%s",s);
		long long l=read(),r=read(),w=read();
		f[l]+=w;
		f[r+1]-=w;
	}
//	fr(i,1,n)if(f[i])printf("%d %d\n",i,f[i]);
	fr(i,1,n)
	{
		k+=f[i];
		a-=k;
		if(a<=0)
		{
			printf("Runtime Error\n%lld\n",i);
			return 0;
		}
	}
	printf("Accepted\n%lld\n",a);
	return 0;
}
