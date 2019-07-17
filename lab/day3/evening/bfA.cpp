#define DEBUG
#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)

#include <bits/stdc++.h>
using namespace std;
const int maxn = 2000 + 5;

int bg[maxn], ne[maxn<<1],to[maxn<<1],e;
void add(int x,int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x,int y) {fa[find(x)] = find(y);}

int grand[maxn][30],depth[maxn],LOG;
void dfs(int x)
{
	for(int i = bg[x];i;i=ne[i])
		if(to[i]^grand[x][0])
		{
			grand[to[i]][0] = x;
			depth[to[i]]=depth[x]+1;
			dfs(to[i]);
		}
}
int lca(int x, int y)
{
	if(depth[x]<depth[y])swap(x,y);
	DREP(i,LOG,0)if(depth[grand[x][i]]>=depth[y])x=grand[x][i];
	if(x==y)return x;
		DREP(i,LOG,0)
			if(grand[x][i]^grand[y][i])x=grand[x][i],y=grand[y][i];
		return grand[x][0];
}
int cnt(int x, int y) {return depth[x]+depth[y]-2*depth[lca(x,y)]+1;}
int val[maxn],vv[maxn],p;
int main()
{
	freopen("A.in", "r", stdin);
	freopen("bf.out", "w", stdout);
	int n,m;
	cin>>n>>m;
	REP(i,1,n)scanf("%d",val+i);
	REP(i,2,n)
	{
		int x, y;
		scanf("%d %d\n",&x, &y);
		add(x,y);add(y,x);
	}
	depth[1]=1;
	dfs(1);
	LOG=log2(n);
	REP(j,1,LOG)REP(i,1,n)grand[i][j]=grand[grand[i][j-1]][j-1];
	while(m--)
	{
		p = 0;
		int x,y,k;
		scanf("%d %d %d",&x, &y,&k);
		int l = lca(x,y);
		while(x!=l&&grand[x][0]!=l)vv[++p]=val[x],x=grand[x][0];
		while(y!=l)vv[++p]=val[y],y=grand[y][0];
		sort(vv+1,vv+1+p);
		printf("%d\n",vv[k]);
	}
	return 0;
}

