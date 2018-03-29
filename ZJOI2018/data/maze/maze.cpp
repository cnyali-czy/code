#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;
long long m,K;
long long gcd(long long k1,long long k2){
	if (k2==0) return k1; return gcd(k2,k1%k2);
}
int num1,num2,num3;
long long getans(long long R,long long K,long long m,long long d){
	if (K%d){
		d=gcd(K,d); num3++;
	}
	if (R<=0||d==1) return max(0ll,R);
	long long lim=K/d,rem=m/d;
	long long dis=K-R;
	if (1.0*dis*rem>lim) dis=lim; else dis*=rem;
	long long L=max(1ll,lim-dis+1),ans=0;
	if (R>=lim) ans=lim-L+1,num1++; else ans+=R,num2++;
	return ans+getans(L-1,lim,m,d);
}
const long long lim=1000000000000000000ll;
void solve(){
	scanf("%lld%lld",&m,&K); long long d=gcd(m,K);
	assert(2<=m&&m<=lim&&1<=K&&K<=lim);
	printf("%lld\n",getans(K-1,K,m,gcd(m,K))+1);
}
int main(){
	int t; scanf("%d",&t);
	assert(1<=t&&t<=300000);
	for (;t;t--) solve();
	cerr<<num1<<" "<<num2<<" "<<num3<<endl;
	return 0;
}
