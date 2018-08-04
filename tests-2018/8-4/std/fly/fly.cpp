#include<bits/stdc++.h>
#define ui unsigned int
#define ll long long
#define db double
#define ld long double
#define ull unsigned long long
const int MAXN=200000+10,MAXM=40+10,MAXS=(MAXN<<1)+(MAXM<<1);
const ll inf=1e18;
int n,m,Q,e,beg[MAXN],nex[MAXS],to[MAXS],w[MAXS],cnt,hole[MAXM],p[MAXN];
ll sum[MAXN],d[MAXM][MAXN],ans;
std::deque<int> q;
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
inline void insert(int x,int y,int z)
{
	to[++e]=y;
	nex[e]=beg[x];
	beg[x]=e;
	w[e]=z;
}
inline void SPFA(int s)
{
	for(register int i=1;i<=n;++i)d[s][i]=inf;
	d[s][hole[s]]=0;
	p[hole[s]]=1;
	q.push_back(hole[s]);
	while(!q.empty())
	{
		int x=q.front();
		q.pop_front();
		p[x]=0;
		for(register int i=beg[x];i;i=nex[i])
			if(d[s][to[i]]>d[s][x]+w[i])
			{
				d[s][to[i]]=d[s][x]+w[i];
				if(q.empty()||d[to[i]]<d[q.front()])q.push_front(to[i]);
				else q.push_back(to[i]);
			}
	}
}
int main()
{
	freopen("fly.in","r",stdin);
	freopen("fly.out","w",stdout);
	read(n);read(m);
	for(register int i=1;i<=n;++i)
	{
		int d;read(d);
		insert(i,i+1>n?1:i+1,d);insert(i+1>n?1:i+1,i,d);
		sum[i+1]=sum[i]+d;
	}
	for(register int i=1;i<=m;++i)
	{
		int u,v,k;read(u);read(v);read(k);
		hole[++cnt]=u;hole[++cnt]=v;
		insert(u,v,k);insert(v,u,k);
	}
	std::sort(hole+1,hole+cnt+1);
	cnt=std::unique(hole+1,hole+cnt+1)-hole-1;
	for(register int i=1;i<=cnt;++i)SPFA(i);
	read(Q);
	while(Q--)
	{
		ans=inf;
		int s,t;read(s);read(t);
		if(s>t)std::swap(s,t);
		chkmin(ans,sum[t]-sum[s]);
		chkmin(ans,sum[n+1]-sum[t]+sum[s]);
		for(register int i=1;i<=cnt;++i)chkmin(ans,d[i][s]+d[i][t]);
		write(ans,'\n');
	}
	return 0;
}

