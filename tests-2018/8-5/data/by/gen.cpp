#include<bits/stdc++.h>
using namespace std;
typedef int sign;
typedef long long ll;
#define For(i,a,b) for(register sign i=(sign)a;i<=(sign)b;++i)
#define Fordown(i,a,b) for(register sign i=(sign)a;i>=(sign)b;--i)
const int N=100+5;
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
	freopen("by11.in","w",stdout);
#endif
}
const int mo=1e6;
int main()
{
	srand(time(NULL));
	file();
	int n=2500;
	cout<<n<<endl;
	For(i,1,n*2)cout<<mo-rand()%(mo*2)<<' '<<mo-rand()%(mo*2)<<endl;
	return 0;
}
