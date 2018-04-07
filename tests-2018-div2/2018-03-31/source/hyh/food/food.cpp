#include<bits/stdc++.h>
using namespace std;
int a[1010],b[1010];
int main( ){
	int k,n,m;
	freopen("food.in","r",stdin);
	freopen("food.out","w",stdout);
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
			scanf("%d%d",&a[i],&b[i]);
	printf("%d\n",a[1]);
	return 0;
}

