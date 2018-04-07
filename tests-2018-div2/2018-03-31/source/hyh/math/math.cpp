#include<bits/stdc++.h>
using namespace std;
int main( ){
	int k,n,m,ans=0;
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
	scanf("%d",&n);
	for(register int i=1;i*i<=n;i++)
		if(n%i==0)ans++;
	ans*=2;
	if(sqrt(n)*sqrt(n)==n)ans--;
	printf("%d\n",ans);
	return 0;
}

