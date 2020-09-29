/*
@Date    : 2020-09-23 19:11:57
@Author  : Adscn (adscn@qq.com)
@Link    : https://www.cnblogs.com/LLCSBlog
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define int long long
#define IL inline
#define RG register
#define gi geti<int>()
#define gl geti<ll>()
#define gc getchar()
#define File(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
template<typename T>IL bool chkmax(T &x,const T &y){return x<y?x=y,1:0;}
template<typename T>IL bool chkmin(T &x,const T &y){return x>y?x=y,1:0;}
template<typename T>
IL T geti()
{
	RG T xi=0;
	RG char ch=gc;
	bool f=0;
	while(!isdigit(ch))ch=='-'?f=1:f,ch=gc;
	while(isdigit(ch))xi=xi*10+ch-48,ch=gc;
	return f?-xi:xi;
}
template<typename T>
IL void pi(T k,char ch=0)
{
	if(k<0)k=-k,putchar('-');
	if(k>=10)pi(k/10);
	putchar(k%10+'0');
	if(ch)putchar(ch);
}
const int P=998244353,G=3,Gi=(P+1)/3;
typedef vector<int> Vec;
inline ll fpow(ll a,int b,ll Mod=P,ll c=1){
	for(;b;b>>=1,a=a*a%Mod)if(b&1)c=c*a%Mod;
	return c;
}
inline ll inv(int x,int Mod=P){return fpow(x,P-2);}
inline int extend(int x){
	int n=1;
	while(n<x)n<<=1;
	return n;
}
inline int add(int x){return x>=P?x-P:x;}
inline int sub(int x){return x<0?x+P:x;}
inline void add(int &x,int y){x+=y;if(x>=P)x-=P;}
inline void sub(int &x,int y){x-=y;if(x<0)x+=P;}
namespace Poly{
	#define lg(x) (31-__builtin_clz(x))
	inline void NTT(Vec &a,int opt)
	{
		int n=a.size(),L=lg(n);
		Vec R(n);
		vector<ull>t(n);
		copy(a.begin(),a.end(),t.begin());
		for(int i=0;i<n;++i)
		{
			R[i]=R[i>>1]>>1|(i&1)<<(L-1);
			if(i<R[i])swap(t[i],t[R[i]]);
		}
		for(int len=1;len<n;len<<=1)
		{
			ll O=fpow(opt==1?G:Gi,(P-1)/(len<<1));
			for(int i=0;i<n;i+=(len<<1))
			{
				ll o=1;
				for(int j=0;j<len;++j,o=o*O%P)
				{
					int tmp=o*t[i+j+len]%P;
					t[i+j+len]=t[i+j]-tmp+P;
					t[i+j]+=tmp;
				}
			}
		}
		for(int i=0;i<n;++i)a[i]=t[i]%P;
	}
	inline void DFT(Vec &a){NTT(a,1);};
	inline void IDFT(Vec &a){
		NTT(a,-1);
		int Inv=inv(a.size());
		for(auto&i:a)i=1ll*i*Inv%P;
	}
	Vec mul(Vec a,Vec b){
		int n=a.size()+b.size()-1,N=extend(n);
		a.resize(N),b.resize(N);
		DFT(a),DFT(b);
		for(int i=0;i<N;++i)a[i]=1ll*a[i]*b[i]%P;
		IDFT(a);
		return a.resize(n),a;
	}
}
using namespace Poly;
namespace Poly2D{
	typedef vector<Vec> vec;
	inline void fix(vec &a,int n,int m){
		a.resize(n);
		for(auto &i:a)i.resize(m);
	}
	inline void NTT2D(vec &a,int opt){
		int n=a.size(),m=a.begin()->size();
		for(int i=0;i<n;++i)NTT(a[i],opt);
		Vec b;
		vec c;
		fix(c,n,m);
		for(int i=0;i<m;++i){
			b.resize(n);
			for(int j=0;j<n;++j)b[j]=a[j][i];
			NTT(b,opt);
			for(int j=0;j<n;++j)c[j][i]=b[j];
		}
		a=c;
	}
	inline void DFT2D(vec &a){NTT2D(a,1);}
	inline void IDFT2D(vec &a){
		NTT2D(a,-1);
		int Inv=inv(1ll*a.size()*a.begin()->size()%P);
		for(auto &i:a)for(auto &j:i)j=1ll*j*Inv%P;
	}
	inline vec mul(vec a,vec b){
		int n=a.size()+b.size()-1,m=a.begin()->size()+b.begin()->size()-1;
		int N=extend(n),M=extend(m);
		fix(a,N,M),fix(b,N,M);
		DFT2D(a),DFT2D(b);
		for(int i=0;i<N;++i)
			for(int j=0;j<M;++j)
				a[i][j]=1ll*a[i][j]*b[i][j]%P;
		IDFT2D(a);
		return fix(a,n,m),a;
	}
};
using namespace Poly2D;

const int maxn = 110;
const int Mod = 998244353;
int fac[maxn], Inv[maxn], n, k, g[maxn], ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 

signed main(void)
{
	freopen("count.in", "r", stdin);
	freopen("std.out", "w", stdout);

    scanf("%lld%lld", &n, &k);
    fac[0] = Inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    Inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) Inv[i] = Inv[i + 1] * (i + 1) % Mod;
    g[1] = 1; g[2] = 1; g[3] = 4; g[4] = 38; g[5] = 728; g[6] = 26704; g[7] = 1866256;

    vec a, b; 
    fix(a, n + 1, n + 1);
    fix(b, n + 1, n + 1);
    a[1][0] = 1;  
    REP(x, 1, n) REP(y, 1, x) b[x][y] = (g[x] * Inv[y] % Mod) * Inv[x - y] % Mod;
    ans = 0;
    REP(o, 1, k)
    {
		cerr << o << endl;
        a = mul(a, b);
        REP(j, 1, k) ans = (ans + (a[n][j] * Inv[o] % Mod) * fac[n - 1]) % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
	/*
	vec tmp;
	fix(tmp, n, k);
	REP(i, 0, n - 1) REP(j, 0, k - 1) scanf("%d", &tmp[i][j]);
	DFT2D(tmp);
	REP(i, 0, n - 1) REP(j, 0, k - 1) printf("%d%c", tmp[i][j], j == k - 1 ? '\n' : ' ');
	srand(233);
	REP(i, 0, n - 1) REP(j, 0, k - 1)
	{
		int x = rand();
		tmp[i][j] = tmp[i][j] * 1ll * x% Mod;
		cerr<<x<<endl;
	}
	IDFT2D(tmp);
	REP(i, 0, n - 1) REP(j, 0, k - 1) printf("%d%c", tmp[i][j], j == k - 1 ? '\n' : ' ');
	*/
	return 0;
}
