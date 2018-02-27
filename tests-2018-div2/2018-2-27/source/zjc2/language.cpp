#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
const int maxn=10000+10;
using namespace std;
int a[maxn],ans=0,n,m,tot=2,tot2;
string s1[maxn],s2[maxn],p[maxn],q[maxn];
void dfs(int x,int sum){
	if(sum>ans){
		ans=sum;
		for(int i=1;i<=tot;i++){
			q[i]=p[i];
		}
		tot2=tot;
	}
	if(ans==m)return;
	for(int i=1;i<=m;i++){
		if(s2[x]==s1[i] && a[i]==0){
			tot++;p[tot]=s2[i];sum++;
			dfs(i,sum);
			sum--;tot--;
		}
	}
	return;
}	
int main(){
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
	int i,j,k;
	string s[maxn];
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>s[i];
	}
	for(i=1;i<=m;i++){
		cin>>s1[i]>>s2[i];
		//cout<<s1[i]<<" "<<s2[i]<<endl;
	}
	for(i=1;i<=m;i++){
		a[i]=1;p[1]=s1[i];p[2]=s2[i];
		dfs(i,1);
		a[i]=0;
	}
	cout<<ans+1<<endl;
	for(i=1;i<=tot2;i++)cout<<q[i]<<" ";
	cout<<endl;
	return 0;
}
