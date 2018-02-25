/**********************************************************
	File:cmdo.cpp
	Author:huhao
	Email:826538400@qq.com
	Created time:2018-2-25 15:24:11
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
#define N 20
#define K (1<<N)
#define M 100
int n,m,k,f[K],l[N],ap[M][M];
char s[M][M];
int main()
{
	freopen("cmdo.in","r",stdin);
	freopen("cmdo.out","w",stdout);
	n=read();
	m=read();
	fr(i,1,n)
		scanf("%s",s[i]+1);
	fr(i,1,n)
		fr(j,1,m)
			if(s[i][j]=='>'||s[i][j]=='^'||s[i][j]=='<'||s[i][j]=='v')
				ap[i][j]=++k;
	fr(i,1,n)
		fr(j,1,m)
		{
			if(s[i][j]=='>')
				fr(k,j+1,m)
				{
					if(s[i][k]=='#')
						break;
					else if(ap[i][k])
						l[ap[i][k]]|=1<<(ap[i][j]-1);
				}
			if(s[i][j]=='<')
				fd(k,j-1,1)
				{
					if(s[i][k]=='#')
						break;
					else if(ap[i][k])
						l[ap[i][k]]|=1<<(ap[i][j]-1);
				}
			if(s[i][j]=='^')
				fd(k,i-1,1)
				{
					if(s[k][j]=='#')
						break;
					else if(ap[k][j])
					{
//						printf("%d %d %d %d\n",i,j,k,j);
						l[ap[k][j]]|=1<<(ap[i][j]-1);
					}
				}
			if(s[i][j]=='v')
				fr(k,i+1,n)
				{
					if(s[k][j]=='#')
						break;
					else if(ap[k][j])
					{
//						printf("%d %d %d %d\n",i,j,k,j);
						l[ap[k][j]]|=1<<(ap[i][j]-1);
					}
				}
		}
//	fr(i,1,k)printf("%d%c",l[i],i==k?'\n':' ');
	f[0]=1;
	fr(i,1,(1<<k)-1)
		fr(j,1,k)
			if((i&(1<<(j-1)))&&(!((((1<<k)-1)^i)&l[j])))
				f[i]+=f[i^(1<<(j-1))];
	if(f[(1<<k)-1])
		printf("%d\n",f[(1<<k)-1]);
	else
		printf("Impossible\n");
	return 0;
}