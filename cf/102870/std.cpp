#include<bits/stdc++.h>
using namespace std;
template<typename T>inline T read(){
	T f=0,x=0;char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return f?-x:x;
}
namespace run{
	typedef unsigned long long ull;
	const int N=2e5+9,mod=998244353;
	inline int add(int x,int y){return x+y>=mod?x-mod+y:x+y;}
	inline int sub(int x,int y){return x>=y?x-y:x+mod-y;}
	inline int qpow(int x,int y){
		int ret=1;
		while(y){
			if(y&1) ret=1LL*x*ret%mod;
			x=1LL*x*x%mod,y>>=1;
		}
		return ret;
	}

	int a[N],b[N],n,m,fac[N],ifac[N];
	inline int C(int _n,int _m){
		if(_n<0 || _m<0 || _n<_m) return 0;
		return 1LL*fac[_n]*ifac[_m]%mod*ifac[_n-_m]%mod;
	}

	int main(){
		n=read<int>(),m=read<int>();
		for(int i=1;i<=n;i++) a[i]=read<int>();
		for(int i=1;i<=m;i++) b[i]=read<int>();
		sort(a+1,a+n+1),sort(b+1,b+m+1);

		int lim=min(n,m);
		fac[0]=1;
		for(int i=1;i<=lim;i++) fac[i]=1LL*fac[i-1]*i%mod;
		ifac[lim]=qpow(fac[lim],mod-2);
		for(int i=lim-1;~i;i--) ifac[i]=1LL*ifac[i+1]*(i+1)%mod;
		a[n+1]=b[m+1]=1e9+1;
		//    for(int i=1;i<=n;i++) cout<<a[i]<<" ";cout<<endl;
		//    for(int i=1;i<=n;i++) cout<<b[i]<<" ";cout<<endl;

		int ans=1;
		for(int i=1,j=1;i<=n || j<=m;i++,j++){
			int _mn=min(a[i],b[j]),_i=i-1,_j=j-1;
			while(_i+1<=n && a[_i+1]==_mn) _i++;
			while(_j+1<=m && b[_j+1]==_mn) _j++;

			int x=_i-i+1,_n=n-i+1,y=_j-j+1,_m=m-j+1,ret=0;
			//    cerr<<i<<" "<<_i<<" "<<j<<" "<<_j<<" "<<x<<" "<<y<<endl;
			if(x>y) swap(x,y),swap(_n,_m);
			int _inv=qpow(_mn,mod-2);
			int b1=qpow(1LL*(_mn-1)*_inv%mod,_m);
			int b2=1LL*_mn*qpow(_mn-1,mod-2)%mod;
			int pw1=1;
			int pw2=qpow(1LL*(_mn-1)*_inv%mod,_n);

			for(int k=0;k<=x;k++){
				int tmp=1LL*C(x,k)*pw1%mod*qpow(sub(1,pw2),y)%mod;
				pw1=1LL*pw1*b1%mod,pw2=1LL*pw2*b2%mod;
				if(k&1) ret=sub(ret,tmp);
				else ret=add(ret,tmp);
			}
			//    cout<<ret<<endl;
			ret=1LL*ret*qpow(_mn,(1LL*_m*x+1LL*_n*y-1LL*x*y)%(mod-1))%mod;
			ans=1LL*ans*ret%mod;
			i=_i,j=_j;
		}
		printf("%d\n",ans);
		return 0;
	}
}
int main(){
#ifdef my
	freopen("delta.in","r",stdin);
	freopen(".out","w",stdout);
#endif
	return run::main();
}
