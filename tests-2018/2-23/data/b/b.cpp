#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn=1e3+10,mod=1e9+7;
int n,k,p,limit,dp[maxn*maxn],sum[maxn*maxn];

inline int min_(int a,int b){return a<=b?a:b;}

int main(){
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d%d%d",&n,&k,&p);
	limit=1;
	for(int i=k+1;i<=n;++i)
		limit+=min_(i-k+1,k);
	if(p>limit){
		puts("0");
		return 0;
	}
	dp[1]=1;
	for(int i=1;i<=k;++i)
		dp[1]=(ll)dp[1]*i%mod;
	limit=1;
	for(int i=k+1;i<=n;++i){
		int maxdelta=min_(i-k+1,k);
		limit+=maxdelta;
		for(int j=1;j<=limit&&j<=p;++j)
			sum[j]=(sum[j-1]+dp[j])%mod;
		for(int j=min_(p,limit);j;--j){
			dp[j]=2ll*(sum[j-1]-sum[j>maxdelta?j-maxdelta:0]+mod)%mod;
			if(j>=maxdelta)
				dp[j]=(dp[j]+(ll)(i-2*(maxdelta-1))*dp[j-maxdelta])%mod;
		}
	}
	printf("%d\n",dp[p]);
	return 0;
}
