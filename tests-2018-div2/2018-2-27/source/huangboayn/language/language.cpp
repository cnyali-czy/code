#include<bits/stdc++.h>
using namespace std;
const int maxn=100+10;
string s[maxn];
map<string,int>c;
int a[maxn][maxn],b[maxn],ans,n,p[maxn];
bool cmp(string s1,string s2){
	if(s1.size()==s2.size())
	return s1<s2;
}
void dfs(int x,int sum){
	b[sum]=x;
	ans=max(ans,sum);
	if(ans==n)return;
	for(register int i=1;i<=n;i++){
		if(a[x][i]==1 && p[i]!=1 && b[sum+1]==0 ||a[x][i]==1 && p[i]!=1 && b[sum+1]!=0 && s[b[sum+1]]>s[b[i]]){
			p[i]=1;
			b[sum+1]=i;
			dfs(i,sum+1);
			p[i]=0;
		}
	}
}
int main(){
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
	int i,j,k,m;
	cin>>n>>m;
	for(register int i=1;i<=n;i++)
	cin>>s[i];
	sort(s+1,s+n+1,cmp);
	for(register int i=1;i<=n;i++)
	c[s[i]]=i;
	for(register int i=1;i<=m;i++){
		string s1,s2;
		cin>>s1>>s2;
		//cout<<c[s1]<<" "<<c[s2]<<endl;
		a[c[s1]][c[s2]]=1;
	}
	dfs(1,1);
	cout<<ans<<endl;
	for(register int i=1;i<=ans;i++)
	cout<<s[b[i]]<<" ";
	return 0;
}
