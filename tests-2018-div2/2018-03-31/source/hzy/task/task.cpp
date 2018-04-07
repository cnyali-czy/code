#include<bits/stdc++.h>
using namespace std;
int n,a[100],ans;
bool p[100];
char s[100],s1[100];
int main()
{
	freopen("task.in","r",stdin);
	freopen("task.out","w",stdout);
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	scanf("%s%s",s+1,s1+1);
	for(register int i=1;i<=n;i++)
		if(s[i]==s1[i])
		{
			ans+=a[i];
			p[i]=1;
		}
	printf("%d\n",ans);
	for(register int i=1;i<=n;i++)
		if(p[i])
			puts("Accepted");
		else
			puts("Wrong Answer");
	return 0;
}
