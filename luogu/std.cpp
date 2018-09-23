#include<bits/stdc++.h>
#define maxn 1000010
#define EEE 1000000000000000000L
#define G c=getchar()
using namespace std;
typedef long long LL;
inline LL read()
{
	LL x=0,f=1;char G;
	while(c>57||c<48){if(c=='-')f=-1;G;}
	while(c>47&&c<58)x=x*10+c-48,G;
	return x*f;
}
LL A,B,C,D,k,t,n,m;
struct poi
{
	LL x;
	int d;
}Q[1000010];
inline bool cmp(const poi &a,const poi &b)
{
	return a.x<b.x;
}
int main()
{
	//	freopen("mdzz1.in","r",stdin);
	//	freopen("mdzz3.out","w",stdout);
	n=read(),m=read();
	int s=read(),q=read();
	A=m-1,B=0,C=0,D=m-1;
	int sz=0;
	//k-1<=A||B<=k-1   C<=k-1<=D
	for(int i=1;i<=s;i++)
	{
		LL a=read(),b=read(),X=(a-1)%m,Y=m-b+a-1;
		if(Y>=X)//[Y-X,m-X+1):GG
		{
			Q[sz++]=(poi){Y-X+1,1};
			Q[sz++]=(poi){m-X,-1};
			//	A=min(A,Y-X),B=max(B,m-X)
			//			printf("k-1<=%d||%d<=k-1\n",Y-X,m-X);
		}
		else
			C=max(C,m-X),D=min(D,m+Y-X);//,printf("%d<=k-1<=%d\n",m-X,m+Y-X);
	}
	Q[sz++]=(poi){-EEE,1};Q[sz++]=(poi){C,-1};Q[sz++]=(poi){D+1,1};Q[sz++]=(poi){EEE,-1};
	sort(Q,Q+sz,cmp);
	LL L=-EEE,R,sum=0,ans=0;
	for(int i=0;i<sz;)
	{
		//	printf("%lld %lld %d\n",L,Q[i].x,sum);
		if(sum<=0)ans+=Q[i].x-L,k=L;
		L=Q[i].x;
		for(;Q[i].x==L&&i<sz;i++)
			sum+=Q[i].d;
	}
	if(ans==0)return puts("Impossible!"),0;
	else if(ans>1)return puts("Uncertain!"),0;
	k++;
	LL anss=0;
	for(int i=1;i<=q;i++)
	{
		t=read();LL x=(k+t-2)/m+1,y=(k+t-2)%m+1;
		if(x<1||n<x||y<1||m<y)x=y=0;
		anss^=x^y;
		//		printf("%lld %lld\n",(k+t-2)/m+1,(k+t-2)%m+1);
	}
	printf("%lld",anss);
}
