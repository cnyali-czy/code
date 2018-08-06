#include<bits/stdc++.h>
using namespace std;
typedef int sign;
typedef long long ll;
#define For(i,a,b) for(register sign i=(sign)a;i<=(sign)b;++i)
#define Fordown(i,a,b) for(register sign i=(sign)a;i>=(sign)b;--i)
const int N=5e3+5;
template<typename T>bool cmax(T &a,T b){return (a<b)?a=b,1:0;}
template<typename T>bool cmin(T &a,T b){return (a>b)?a=b,1:0;}
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
	freopen("by.in","r",stdin);
	freopen("by.out","w",stdout);
#endif
}
int n;
double x[N],y[N],v[N];
void input()
{	
	n<<=1;
	For(i,1,n)scanf("%lf%lf",&x[i],&y[i]);
}
double dis(int i,int j)
{
	return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}
double ans;
void work()
{
	ans=0;
	memset(v,0,sizeof v);
	For(i,1,n)
	{
		For(j,1,n)v[i]+=dis(i,j);	
		//ans+=v[i];
	}
	//ans/=2.0;
	sort(v+1,v+n+1);
	For(i,1,n)
		if(i&1)ans-=v[i];
		else ans+=v[i];
	printf("%.3lf\n",ans/2.0);
}
int main()
{
	file();
	while(~scanf("%d",&n))
	{
		input();
		work();
	}
	return 0;
}
