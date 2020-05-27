#include <bits/stdc++.h>

const int N=1<<17;
std::mt19937 Rand(0721);
int n,k,Mat[N],Vis[N];
std::vector<int> v[20],G[N];
std::vector<std::pair<int,int> > Ans;

inline void Out(int x){for(int i=0;i<n;++i)if(x>>i&1)putchar('a'+i);}

bool DFS(int x)
{
	std::shuffle(G[x].begin(),G[x].end(),Rand),Vis[x]=1;
	for(int i=0,y,v;i<(int)G[x].size();++i)if(!Vis[Mat[y=G[x][i]]])
	{
		if(v=Mat[y],Mat[x]=y,Mat[y]=x,!v||DFS(v))return true;
		Mat[v]=y,Mat[y]=v,Mat[x]=0;
	}
	return false;
}

void Link(std::vector<int>& L,int v,int s,int c,int r){
	if(r>=0&&r+c<=n)c!=n?Link(L,v,s,c+1,r),s>>c&1?Link(L,v|1<<c,s,c+1,r-1):void():L.push_back(v);}

void Match(std::vector<int>& u,std::vector<int>& v)
{
	std::vector<int> s;
	s.reserve(u.size()+v.size());
	for(int i:u)s.push_back(i);
	for(int i:v)s.push_back(i);
	for(int i:s)Link(G[i],0,((1<<n)-1)^i,0,k-__builtin_popcount(i));
	for(int c;;)
	{
		std::shuffle(s.begin(),s.end(),Rand),c=0;
		for(int i:s)Vis[i]=0;
		for(int i:s)if(!Mat[i])DFS(i);
		for(int i:u)c+=!Mat[i];
		if(!c||(&u==&v&&c==int(u.size()&1)))break;
	}
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1,j;i<1<<n;++i)if((j=__builtin_popcount(i))<=k)v[j].push_back(i);
	for(int i=1;i<=k-i;++i)Match(v[i],v[k-i]);
	for(int i=1;i<1<<n;++i)if(__builtin_popcount(i)<=k)
		{if(Mat[i]>i)Ans.emplace_back(i,Mat[i]);
		else if(!Mat[i])Ans.emplace_back(i,0);}
	printf("%d\n",(int)Ans.size());
	for(auto i:Ans)
	{
		printf("%d ",1+(i.second>0)),Out(i.first),putchar(i.second?' ':'\n');
		if(i.second)Out(i.second),putchar('\n');
	}
	return 0;
}
