/**********************************************************
	File:diablo.cpp
	Author:huhao
	Email:826538400@qq.com
	Created time:2018-2-25 15:44:14
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
#define N 110
#define M 510
int n,m,f[N][M],pre[N][M],ans[N],num[N][M];
int main()
{
	freopen("diablo.in","r",stdin);
	freopen("diablo.out","w",stdout);
	n=read();
	m=read();
	fr(i,1,n)
	{
		int c=read(),p=read();
		fr(j,0,m)
		{
			f[i][j]=f[i-1][j];
			pre[i][j]=j;
		}
		fr(_,1,p)
		{
			int v=read(),w=c*_;
			fr(j,w,m)
				if(f[i][j]<f[i-1][j-w]+v)
				{
					f[i][j]=f[i-1][j-w]+v;
					pre[i][j]=j-w;
					num[i][j]=_;
				}
//			fr(j,0,m)
//				printf("%d%c",f[i][j],j==m?'\n':' ');
		}
//		putchar(10);
	}
	int k=0;
	fr(i,1,m)
		if(f[n][i]>f[n][k])
			k=i;
	printf("%d\n",f[n][k]);
	fd(i,n,1)
	{
		ans[i]=num[i][k];
		k=pre[i][k];
	}
	fr(i,1,n)
		printf("%d\n",ans[i]);
	return 0;
}