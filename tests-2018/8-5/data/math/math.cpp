#include<bits/stdc++.h>
using namespace std;
typedef int sign;
typedef long long ll;
#define For(i,a,b) for(register sign i=(sign)a;i<=(sign)b;++i)
#define Fordown(i,a,b) for(register sign i=(sign)a;i>=(sign)b;--i)
const int N=1e5+5;
bool cmax(sign &a,sign b){return (a<b)?a=b,1:0;}
bool cmin(sign &a,sign b){return (a>b)?a=b,1:0;}
template<typename T>T read()
{
	T ans=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)&&ch!='-')ch=getchar();
	if(ch=='-')f=-1,ch=getchar();
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch-'0'),ch=getchar();
	return ans*f;
}
template<typename T>void write(T x,char y)
{
	if(x==0)
	{
		putchar('0'),putchar(y);
		return;
	}
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	static char wr[20];
	int top=0;
	for(;x;x/=10)wr[++top]=x%10+'0';
	while(top)putchar(wr[top--]);
	putchar(y);
}
void file()
{
#ifndef ONLINE_JUDGE
	freopen("math10.in","r",stdin);
	freopen("math10.out","w",stdout);
#endif
}
const int mo=1e9+7;
int n,m,a[N],sum[N<<2],lazy[N<<2];
ll power(ll x,int y)
{
	ll res=1;
	for(;y;x=x*x%mo,y>>=1)if(y&1)res=res*x%mo;
	return res;
}
int add(int x,int y)
{
	return x+y>=mo?x+y-mo:x+y;
}
#define mid ((l+r)>>1)
#define lson h<<1,l,mid
#define rson h<<1|1,mid+1,r
void push_up(int h)
{
	sum[h]=add(sum[h<<1],sum[h<<1|1]);
}
void push_down(int h)
{
	if(lazy[h]==1)return;
	int ls=h<<1,rs=ls|1;
	lazy[ls]=1ll*lazy[ls]*lazy[h]%mo;
	lazy[rs]=1ll*lazy[rs]*lazy[h]%mo;
	sum[ls]=1ll*sum[ls]*lazy[h]%mo;
	sum[rs]=1ll*sum[rs]*lazy[h]%mo;
	lazy[h]=1;
}
void update(int h,int l,int r,int s,int t,int v)
{
	if(s<=l&&r<=t)
	{
		sum[h]=1ll*sum[h]*v%mo;
		lazy[h]=1ll*lazy[h]*v%mo;
	}
	else
	{
		push_down(h);
		if(s<=mid)update(lson,s,t,v);
		if(mid<t)update(rson,s,t,v);
		push_up(h);
	}
}
void build(int h,int l,int r)
{
	lazy[h]=1;
	if(l==r)
	{
		int num=n-l;
		if(!num)sum[h]=1;
		else sum[h]=1ll*2*power(3,num-1)%mo;
		//cerr<<l<<' '<<sum[h]<<endl;
	}
	else
	{
		build(lson),build(rson);
		push_up(h);
	}
}
void input()
{
	n=read<int>();m=read<int>();
	For(i,1,n)a[i]=read<int>();
}
void work()
{
	int t=1;
	For(i,1,n)
	{
		t=1ll*t*a[i]%mo;
		update(1,1,n,i,i,t);
	}
	int pos,v;
	//cout<<sum[1]<<endl;
	while(m--)
	{
		pos=read<int>(),v=read<int>();
		update(1,1,n,pos,n,power(a[pos],mo-2));
		a[pos]=v;
		update(1,1,n,pos,n,a[pos]);
		write(sum[1],'\n');
	}
}
int main()
{
	file();
	input();
	build(1,1,n);
	work();
	return 0;
}
