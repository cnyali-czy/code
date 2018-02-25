/**********************************************************
	File:gen.cpp
	Author:huhao
	Email:826538400@qq.com
	Created time:2018-2-25 15:58:08
**********************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
int read()
{
	int r=0,t=1,c=getchar();
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
#define N 30010
#define mod (1<<30)
int n=3,m=5,a[N];
char t[3];
int main()
{
	freopen("gen.in","w",stdout);
	srand((unsigned long long)new char);
	printf("%d\n",n);
	fr(i,1,n)a[i]=rand()%mod+1;
	fr(i,1,n)printf("%d%c",a[i],i==n?'\n':' ');
	printf("%d\n",m);
	t[0]='A';
	t[1]='C';
	t[2]='Q';
	fr(i,1,m)
	{
		int opt=rand()%3;
		if(opt!=2)
		{
			int pos=rand()%n+1;
			while(a[pos]<=0)pos=rand()%n+1;
			int w=rand()%mod+1;
			if(opt==1)while(a[pos]+w<=0)w=rand()%mod+1;
			if(opt)a[pos]+=w;
			else a[pos]-=w;
			printf("%c %d %d\n",t[opt],pos,w);
		}
		else printf("%c %d\n",t[opt],rand()%n+1);
	}
	return 0;
}