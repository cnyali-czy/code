/*
Author: CNYALI_LK
LANG: C++
PROG: OvercookedDiv2.cpp
Mail: cnyalilk@vip.qq.com
*/

#include<bits/stdc++.h>
#define debug(...) fprllf(stderr,__VA_ARGS__)
#define all(x) x.begin(),x.end()
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
template<class Ta,class Tb>ll chkmin(Ta &a,Tb b){return a>b?a=b,1:0;}
template<class Ta,class Tb>ll chkmax(Ta &a,Tb b){return a<b?a=b,1:0;}

class OvercookedDiv2 {
    public:
	ll check(ll t,vector<ll> start,vector<ll> time){
		ll s=0;
		ll n=start.size();
		for(ll i=0;i<n;++i){
			s+=t;
			if(s<start[i])return 0;
			s+=time[i];
		}
		return 1;
	}
    ll minStale(vector<ll> start, vector<ll> time) {
		ll l=0,r=1e14,mid;
		while(l<=r){
			mid=(l+r)>>1;	
			if(check(mid,start,time)){
				r=mid-1;
			}
			else l=mid+1;
		}
        return r+1;
    }
};
OvercookedDiv2 a;
int main(){
	ll n,s,t;
	vector<ll> start,time;
	vector<pii> h;
	scanf("%lld",&n);
	for(ll i=1;i<=n;++i){
		scanf("%lld%lld",&s,&t);
		h.push_back(make_pair(s,t));
	}
	sort(all(h));
	for(int i=0;i<n;++i){
		start.push_back(h[i].first);
		time.push_back(h[i].second);
	}
	printf("%lld\n",a.minStale(start,time));
	return 0;
}
