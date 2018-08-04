#include<bits/stdc++.h>
#define ui unsigned int
#define ll long long
#define db double
#define ld long double
#define ull unsigned long long
template<typename T> inline void read(T &x)
{
	T data=0,w=1;
	char ch=0;
	while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
	if(ch=='-')w=-1,ch=getchar();
	while(ch>='0'&&ch<='9')data=((T)data<<3)+((T)data<<1)+(ch^'0'),ch=getchar();
	x=data*w;
}
template<typename T> inline void write(T x,char ch='\0')
{
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
	if(ch!='\0')putchar(ch);
}
template<typename T> inline void chkmin(T &x,T y){x=(y<x?y:x);}
template<typename T> inline void chkmax(T &x,T y){x=(y>x?y:x);}
using namespace std;
vector<int> V[25];
int vis[25];
int main()
{
	freopen("match1.in","w",stdout);
	srand(time(0));
	int n=4,m=0;
	for(register int i=1;i<=n;++i)
	{
		int now=rand()%(n-1)+1;
		m+=now;memset(vis,0,sizeof(vis));
		for(register int j=1;j<=now;++j)
		{
			int k=rand()%n+1;
			if(k==i||vis[k]){--j;continue;}
			V[i].push_back(k);vis[k]=1;
		}
	}
	printf("%d %d\n",n,m);
	for(register int i=1;i<=n;++i)
		for(register int j=0,lt=V[i].size();j<lt;++j)printf("%d %d\n",V[i][j],i);
	return 0;
}

