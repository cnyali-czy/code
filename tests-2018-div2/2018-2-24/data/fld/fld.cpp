#include<bits/stdc++.h>
using namespace std;
int main( ){
	double n,m,k;
	long long ans;
	freopen("fld1.in","r",stdin);
	freopen("fld1.out","w",stdout);
	scanf("%lf%lf",&n,&m);
	k=(n*n+m*m)* 3.1415926/2.0;
	ans=(long long)k/50;
	printf("%lld\n",ans);
	return 0;
}

