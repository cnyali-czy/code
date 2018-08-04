#include<bits/stdc++.h>
#define ui unsigned int
#define ll long long
#define db double
#define ld long double
#define ull unsigned long long
const int MAXN=20+2,Mod=998244353;
int n,m;
ll f[MAXN][1<<21];
std::vector<int> G[MAXN];
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
template<typename T> inline T min(T x,T y){return x<y?x:y;}
template<typename T> inline T max(T x,T y){return x>y?x:y;}
int main()
{
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	read(n);read(m);
	for(register int i=1;i<=m;++i)
	{
		int u,v;read(u);read(v);
		G[v].push_back(u);
	}
	f[0][0]=1;
	for(register int i=1;i<=n;++i)
		for(register int st=0;st<(1<<n);++st)
			if(__builtin_popcount(st)==i-1)
				for(register int j=0,lt=G[i].size();j<lt;++j)
					if(!(st&(1<<G[i][j]-1)))(f[i][st|(1<<G[i][j]-1)]+=f[i-1][st])%=Mod;
	write(f[n][(1<<n)-1],'\n');
	return 0;
}

