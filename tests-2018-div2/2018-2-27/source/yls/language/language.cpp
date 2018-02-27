#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
#include<vector>
#define REP(i,a,b) for(register int i=a;i<=b;++i)
#define DREP(i,a,b) for(register int i=a;i>=b;--i)
#define MREP(i,x) for(register int i=beg[x];i;i=E[i].last)
using namespace std;
void File(){
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
}
const int maxn=100+10;
int n,m,f[maxn],len,beg[maxn],ans;
map<string,int>s;
map<int,string>a;
vector<int>Ans[maxn];
struct edge{
	int to;
	int last;
}E[maxn];
void add(int u,int v){
	++len;
	E[len].to=v;
	E[len].last=beg[u];
	beg[u]=len;
}
bool vis[maxn];
void dfs(int u){
	int tt=0;
	MREP(i,u){
		int v=E[i].to;
		if(!f[v])dfs(v);
		if(f[v]>f[tt])
			tt=v;
	}
	f[u]=f[tt]+1;
	int siz=Ans[tt].size()-1;
	REP(i,0,siz)Ans[u].push_back(Ans[tt][i]);
	Ans[u].push_back(u);
	if(f[u]>f[ans])ans=u;
}
int main(){
	File();
	scanf("%d%d",&n,&m);
	REP(i,1,n){
		string t;
		cin>>t;
		s[t]=i;
		a[(int)i]=t;
	}
	REP(i,1,m){
		string t,b;
		int u,v;
		cin>>t>>b;
		u=s[t];
		v=s[b];
		add(u,v);
	}
	REP(i,1,n)if(!f[i])
		dfs(i);
	printf("%d\n",f[ans]);
	int siz=Ans[ans].size()-1;
	DREP(i,siz,0)cout<<a[Ans[ans][i]]<<" ";
	return 0;
}
