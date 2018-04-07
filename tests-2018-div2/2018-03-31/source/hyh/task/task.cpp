#include<bits/stdc++.h>
using namespace std;
int a[110],w[110];
string s1,s2;
int main( ){
	int k,n,m,ans=0;
	freopen("task.in","r",stdin);
	freopen("task.out","w",stdout);
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	cin>>s1;
	cin>>s2;
	for(register int i=1;i<=n;i++)
		if(s1[i-1]==s2[i-1]){
			ans+=a[i];
			w[i]=1;
		}
	printf("%d\n",ans);
	for(register int i=1;i<=n;i++)
		if(w[i]==1)printf("Accepted\n");
		else printf("Wrong Answer\n");
		
	return 0;
}

