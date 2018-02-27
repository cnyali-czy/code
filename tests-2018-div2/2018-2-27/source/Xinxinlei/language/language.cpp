#include<bits/stdc++.h>
using namespace std;
char s[110][30],s1[30];
int n,m,sum,ans,a[100010],b[100010],p[100010],l[100010],f[100010];
void dfs(int x) {
	if(sum+1>ans) {
		ans=sum;
		for(register int i=1; i<=sum; i++)
			b[i]=a[i];
		b[++ans]=l[x];
	}
	p[x]=1;
	for(register int i=1; i<=m; i++)
		if(l[x]==f[i]) {
			a[++sum]=f[i];
			dfs(i);
			sum--;
		}
}
int main() {
	freopen("language.in","r",stdin);
	freopen("language.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(register int i=1; i<=n; i++)
		scanf("%s",s[i]);
	for(register int i=1; i<=m; i++) {
		scanf("%s",s1);
		for(register int j=1; j<=n; j++)
			if(!strcmp(s1,s[j])) {
				f[i]=j;
				break;
			}
		scanf("%s",s1);
		for(register int j=1; j<=n; j++)
			if(!strcmp(s1,s[j])) {
				l[i]=j;
				break;
			}
	}
	for(register int i=1; i<=m; i++)
		if(!p[i]) {
			sum=1;
			a[1]=f[i];
			dfs(i);
		}
	printf("%d\n",ans);
	for(register int i=1; i<=ans; i++)
		printf("%s ",s[b[i]]);
	return 0;
}
