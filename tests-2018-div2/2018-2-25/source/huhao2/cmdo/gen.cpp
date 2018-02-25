/**********************************************************
	File:gen.cpp
	Author:huhao
	Email:826538400@qq.com
	Created time:2018-2-25 16:22:02
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
#define N 70
int n=10,m=10,k=15,ap[N][N],t[4]={'^','v','<','>'};
int main()
{
	freopen("cmdo.in","w",stdout);
	srand((unsigned long long)new char);
	if(rand()%100==0)
	{
		printf("2 2\n>v\n^<");
		return 0;
	}
	printf("%d %d\n",n,m);
	fr(i,1,k)
	{
		int x=rand()%n+1,y=rand()%m+1;
		while(ap[x][y])x=rand()%n+1,y=rand()%m+1;
		ap[x][y]=1;
	}
	fr(i,1,n)
	{
		fr(j,1,m)
			if(ap[i][j])
				putchar(t[rand()%4]);
			else
				if(rand()%4)
					putchar('.');
				else
					putchar('#');
		putchar(10);
	}
	return 0;
}