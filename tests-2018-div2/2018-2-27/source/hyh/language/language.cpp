#include<bits/stdc++.h>
using namespace std;
string s,s1,s2;
map<string,int>a;
string p[10100];
int w[10100],d[110][110],ans=0,many[10010],go[110][110],ans1[10010];
void dfs(int now,int num){
	int qw=0;
	//printf("%d %d\n",now,num);
	w[num]=now;
	if(many[now]==0){
		if(num>ans){
			ans=num;
			for(register int i=1;i<=num;i++)ans1[i]=w[i];
		}
		return;
	}
	for(register int i=1;i<=many[now];i++){
		dfs(go[now][i],num+1);
	}
}
int main( ){
	int k,n,m;
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
	scanf("%d%d",&n,&m);
	k=0;
	for(register int i=1;i<=n;i++){
		cin>>s;
		a[s]=++k;
		p[k]=s;
	}
	for(register int i=1;i<=m;i++){
		cin>>s1>>s2;
		d[a[s1]][a[s2]]=1;
		many[a[s1]]++;
		go[a[s1]][many[a[s1]]]=a[s2];
	}
	for(register int i=1;i<=n;i++){
		dfs(i,1);
	}
	printf("%d\n",ans);
	for(register int i=1;i<=ans;i++)
		cout<<p[ans1[i]]<<' ';
	return 0;
}

