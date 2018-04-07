#include<bits/stdc++.h>
using namespace std;
typedef pair<long long,long long>pii;
pii a[102424];
#define x first
#define y second
int main(){
	long long n;
	scanf("%lld",&n);
	for(long long i=1;i<=n;++i){
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+n+1);
	long long tt=0,nt,ans=0;
	for(long long i=1;i<=n;++i){
		nt=max(tt,a[i].x);
		ans=max(ans,nt-tt);
		tt=nt+a[i].y;
	}
	printf("%lld\n",ans);
	return 0;
}
