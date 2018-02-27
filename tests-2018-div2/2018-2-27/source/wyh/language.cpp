#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int N=10000+10;
string q[N],t[N];
int vis[N];
int ans,m,tot,tot2;
struct node{
	string s1,s2;
}s[N];

int cmp(node x,node y){
	return ((x.s1<y.s1) || (x.s1==y.s1 && x.s2<y.s2));
}

void dfs(int x,int sum){
	if(sum>ans){
		ans=sum;
		for(int i=1;i<=tot;i++)
			t[i]=q[i];
		tot2=tot;
	}
	if(ans==m)return;
	for(int i=1;i<=m;i++)
		if(i!=x && s[i].s1==s[x].s2 && !vis[i]){
			vis[i]=1;q[++tot]=s[i].s2;
			dfs(i,sum+1);
			vis[i]=0;tot--;
		}
}

int main(){
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
	int i,j,k,n;
	cin>>n>>m;
	for(i=1;i<=n;i++)
		cin>>s[0].s1;
	for(i=1;i<=m;i++)
		cin>>s[i].s1>>s[i].s2;
	sort(s+1,s+m+1,cmp);
	for(i=1;i<=m;i++){
		vis[i]=1;q[++tot]=s[i].s1;q[++tot]=s[i].s2;
		dfs(i,1);
		vis[i]=0;
	}
	cout<<ans+1<<endl;
	for(i=1;i<=tot2;i++)
		cout<<t[i]<<" ";
	return 0;
}
