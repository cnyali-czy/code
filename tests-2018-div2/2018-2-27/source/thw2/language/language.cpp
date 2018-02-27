#include<bits/stdc++.h>
using namespace std;
struct node{
	int o,e;
}a[1010];
int i,j,b[1010],n,m,ans,g[1010]; char s[1010][1010],tmp[1010];
void dfs(int x,int s){
	if (s>ans) {
		ans=s; //printf("%d\n",s);
		for (int i=1;i<=s;i++) {
			g[i]=b[i]; //printf("%d ",g[i]);
		}
		//printf("\n");
	}
	for (int i=1;i<=m;i++) 
		if (a[i].o==a[x].e) {
			b[s+1]=i;
			dfs(i,s+1);
		}
}
int main(){
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
	cin>>n>>m;
	for (i=1;i<=n;i++) cin>>s[i];
	for (i=1;i<=m;i++) {
		cin>>tmp;
		for (j=1;j<=n;j++) 
			if (strcmp(tmp,s[j])==0) 
				a[i].o=j;
		cin>>tmp;
		for (j=1;j<=n;j++) 
			if (strcmp(tmp,s[j])==0) 
				a[i].e=j;
	}
	for (i=1;i<=m;i++) {
		b[1]=i;
		dfs(i,1);
	}
	printf("%d\n",ans+1);
	for (i=1;i<=ans;i++) printf("%s ",s[a[g[i]].o]);
	printf("%s\n",s[a[g[ans]].e]);
	return 0;
}
