#include<bits/stdc++.h>
using namespace std;
const int maxn=120,inf=0x3f3f3f3f;
int n,m;
int f[maxn][maxn],pre[maxn][maxn],dis[maxn][maxn],stp[maxn];
int in[maxn];
int Max;
string str[maxn];
int find(string s){
	for(register int i=1;i<=n;++i)if(s==str[i])return i;
	return 0;
}
void init(){
	for(register int i=1;i<=n;++i){
		for(register int j=1;j<=n;++j){
			pre[i][j]=i;
		}
	}
}
void bfs(int x){
	queue<int>q;
	q.push(x);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(register int i=1;i<=n;++i){
			if(!f[u][i])continue;
			int tmp=dis[x][i];
			if(dis[x][i]<dis[x][u]+1){
				dis[x][i]=dis[x][u]+1;
				pre[x][i]=u;
				q.push(i);
			}
		}
	}
}
int main(){
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
	cin>>n>>m;
	init();
	for(register int i=1;i<=n;++i)cin>>str[i];
	string x,y;
	int u,v;
	if(m==0){
		cout<<0<<endl;
		return 0;
	}
	for(register int i=1;i<=m;++i){
		cin>>x>>y;
		u=find(x),v=find(y);
		f[u][v]=1;
		++in[v];
	}int maxx=-inf;
	for(register int i=1;i<=n;++i)if(!in[i])bfs(i);
	for(register int i=1;i<=n;++i)for(register int j=1;j<=n;++j){
		if(dis[i][j]>maxx)maxx=dis[i][j],u=i,v=j;
	}int now=pre[u][v];
	printf("%d\n",pre[u][v]+1);
	stack<int>st;
	st.push(v);
	while(1){
		st.push(now);
		if(now==u)break;
		now=pre[u][now];
	}
	while(!st.empty()){
		cout<<str[st.top()]<<" ";
		st.pop();
	}
	return 0;
}
