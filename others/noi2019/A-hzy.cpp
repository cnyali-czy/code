#include<cstdio>
#include<queue>
#include<map>
#include <iostream>
#define int long long
using namespace std;
const int maxm=2e5+10,maxn=1e5+10,inf=(-1ull)>>1;
int dis[maxm<<1],bg[maxn],s[maxm],nt[maxm],e,tot,n,m,A,B,C;
pair<int,int>to[maxm];
map<pair<int,int>,int>id;
priority_queue<pair<int,pair<int,int> > >q;
inline void add(int x,int p,int y,int z)
{
	to[++e]=make_pair(y,z);
	s[e]=p;
	nt[e]=bg[x];
	bg[x]=e;
}
inline int read()
{
	int x=0;
	char c=getchar();
	while(c<'0' || c>'9')
		c=getchar();
	while(c>='0' && c<='9')
	{
		x=x*10+c-48;
		c=getchar();
	}
	return x;
}
signed main()
{
	freopen("route.in","r",stdin);
	freopen("std.out","w",stdout);
	n=read();
	m=read();
	A=read();
	B=read();
	C=read();
	id[make_pair(1,0)]=++tot;
	for(register int i=1,x,y,p,q;i<=m;i++)
	{
		x=read();
		y=read();
		p=read();
		q=read();
		if(!id[make_pair(x,p)])
			id[make_pair(x,p)]=++tot;
		if(!id[make_pair(y,q)])
			id[make_pair(y,q)]=++tot;
		add(x,p,y,q);
	}
	for(register int i=2;i<=tot;i++)
		dis[i]=inf;
	q.push(make_pair(0,make_pair(1,0)));
	while(!q.empty())
	{
		int s=-q.top().first,x=q.top().second.first,t=q.top().second.second,ID=id[make_pair(x,t)];
		cout << s << ' ' << x << ' ' << t << ' ' << ID << endl;
		q.pop();
		if(x==n)
		{
			printf("%lld\n",s);
			return 0;
		}
		if(dis[ID]<s)
			continue;
		for(register int i=bg[x];i;i=nt[i])
		{
			pair<int,int>u=to[i];
			if(::s[i]<t)
				continue;
			int w=A*(::s[i]-t)*(::s[i]-t)+B*(::s[i]-t)+C;
			if(dis[id[u]]>s+w-t+u.second)
			{
				dis[id[u]]=s+w-t+u.second;
				cout << id[u]<< ' ' << dis[id[u]] << endl;
				q.push(make_pair(-dis[id[u]],u));
			}
		}
	}
	return 0;
}
