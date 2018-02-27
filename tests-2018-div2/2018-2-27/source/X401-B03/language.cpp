#include<bits/stdc++.h>
#define N 21000
#define M 200
using namespace std;
inline void read(int &x)
{
	x=0;
	static int p;p=1;
	static char c;c=getchar();
	while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
	while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
	x*=p;
}
int n,m;
map<string,int>mapp;
map<int,string>bh;
string s,ss;
int to[N],beg[M],nex[N];
int e;
void add(int x,int y)
{
	to[++e]=y;
	nex[e]=beg[x];
	beg[x]=e;
}
int dp[N],rd[N],ans;
int pre[N];
int Ans[N];
void dfs(int dep,int x)
{
	if(dep)
	{
		Ans[dep]=x;
		dfs(dep-1,pre[x]);
	}
	else return ;
}
void topsort()
{
	queue<int>q;
	for(int i=1;i<=n;i++)if(!rd[i])q.push(i),dp[i]=1,pre[i]=0;
	ans=1;
	while(!q.empty())
	{
		int k=q.front();
		q.pop();
		for(int i=beg[k];i;i=nex[i])
		{
			int y=to[i];
			if(dp[k]+1>dp[y])
			{
				dp[y]=dp[k]+1;
				pre[y]=k;
			}
			rd[y]--;
			if(!rd[y])q.push(y);
		}
	}
	int now=0;
	for(int i=1;i<=n;i++)
		if(ans<dp[i])ans=dp[i],now=i;
	dfs(ans,now);
}
int main()
{
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
	read(n);read(m);
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		mapp[s]=i;
		bh[i]=s;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>s>>ss;
		add(mapp[s],mapp[ss]);
		rd[mapp[ss]]++;
	}
	topsort();
	printf("%d\n",ans);
	printf("%s",bh[Ans[1]].c_str());
	for(int i=2;i<=ans;i++)
		printf(" %s",bh[Ans[i]].c_str());
	printf("\n");
	return 0;
}
