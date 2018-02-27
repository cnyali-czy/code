#include<bits/stdc++.h>
using namespace std;
const int maxm=10000+10;
string s1[maxm],s2[maxm];
int vis[maxm];
int len,m,tot,n;
inline void dfs(int cur,int sum){
	tot=max(tot,sum);
	for(int i=1;i<=m;i++){
		if(i!=cur && s2[cur]==s1[i] && !used[i]){
			vis[i]=1; que[++len]=s2[cur];
			dfs(cur+1,sum+1);
			vis[i]=0; --len;
		}
	}
}
int main(){
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) cin>>s1[i];
	for(int i=1;i<=m;i++) cin>>s2[i];
	for(int i=1;i<=m;i++) dfs(i,1);
	return 0;
}
