#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn=1<<18,mod=998244353,g=3;
int n,m,len;
int a[maxn],b[maxn],c[maxn];
int no01[maxn],no0[maxn],no1[maxn],tot[maxn];
ll ans[4];

inline ll qpow(ll a,ll n){
	ll res=1;
	for(;n;n>>=1,a=a*a%mod)
		if(n&1ll)
			res=res*a%mod;
	return res;
}
inline int rev(int a,int n){
	int res=0;
	for(int i=1;i<n;i<<=1)
		if(a&i)
			res=res<<1|1;
		else
			res=res<<1;
	return res;
}
inline void fft(int*a,int n,int dft){
	for(int i=0;i<n;++i)
		if(i<rev(i,n))
			swap(a[i],a[rev(i,n)]);
	for(int i=2;i<=n;i<<=1){
		int w=qpow(g,(mod-1)/i);
		if(dft==-1)
			w=qpow(w,mod-2);
		for(int j=0;j<n;j+=i){
			int wn=1;
			for(int k=0;k<(i>>1);++k,wn=(ll)wn*w%mod){
				int x=a[j+k],y=(ll)a[j+k+(i>>1)]*wn%mod;
				a[j+k]=(x+y)%mod;
				a[j+k+(i>>1)]=(x-y+mod)%mod;
			}
		}
	}
	if(dft==-1){
		int invn=qpow(n,mod-2);
		for(int i=0;i<n;++i)
			a[i]=(ll)a[i]*invn%mod;
	}
}
inline void mul(int*a,int*b,int n){
	fft(a,n,1);
	fft(b,n,1);
	for(int i=0;i<n;++i)
		a[i]=(ll)a[i]*b[i]%mod;
	fft(a,n,-1);
}
inline void solve(int*res,int val){
	static int tmp1[maxn],tmp2[maxn];
	for(int i=0;i<len;++i)
		tmp1[i]=tmp2[i]=0;
	for(int i=0;i<n;++i)
		if((a[i]&val)==a[i])
			tmp1[i]=1;
	for(int i=0;i<n;++i)
		if((b[i]&val)==b[i])
			tmp2[i]=1;
	mul(tmp1,tmp2,len);
	for(int i=0;i<=2*n-2;++i)
		if((c[i]&val)==c[i])
			res[i]=tmp1[i];
		else
			res[i]=0;
}

int main(){
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d%d",&n,&m);
	len=1<<(int)ceil(log(2*n-1)/log(2));
	while(m--){
		int type,pos,color;
		scanf("%d%d%d",&type,&pos,&color);
		if(type==1)
			a[pos-1]|=1<<color;
		else if(type==2)
			b[pos-1]|=1<<color;
		else
			c[pos-2]|=1<<color;
	}
	solve(no01,0);
	solve(no1,1);
	solve(no0,2);
	solve(tot,3);
	for(int i=0;i<=2*n-2;++i){
		ans[0]+=no01[i];
		ans[1]+=no1[i]-no01[i];
		ans[2]+=no0[i]-no01[i];
		ans[3]+=tot[i]-no1[i]-no0[i]+no01[i];
	}
	printf("%lld %lld %lld %lld\n",ans[0],ans[1],ans[2],ans[3]);
	return 0;
}
