#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define Chkmin(a,b) a=a<b?a:b
#define Chkmax(a,b) a=a>b?a:b
using namespace std;
template<typename T>inline void read(T &x)
{
    T s=0,f=1;char k=getchar();
    while(!isdigit(k)&&(k^'-'))k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}
const int MAXN=2e5+7,mod=20000909;

static int n;

static long long L;

static long long a[MAXN],b[MAXN<<2];

inline void init()
{
	read(n);read(L);
	Rep(i,1,n)read(a[i]);
	Rep(i,1,n)read(b[i]);
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	Rep(i,1,n)b[i+n]=b[i]+L,b[i+2*n]=b[i+n]+L;
}

static long long l,r;

static int Lb[MAXN],Rb[MAXN];

inline bool Judge(long long lim)
{
	Rep(i,1,n)
	{
		Lb[i]=lower_bound(b+1,b+3*n+1,a[i]+L-lim)-b;
		Rb[i]=upper_bound(b+1,b+3*n+1,a[i]+L+lim)-b;
		--Rb[i];
		if(Lb[i]>Rb[i])return false;
	}
	Rep(i,1,n-1)
	{
		Chkmax(Lb[i+1],Lb[i]+1),Chkmin(Rb[i+1],Rb[i]+1);
		if(Lb[i+1]>Rb[i+1])return false;
	}
	return true;
}

inline int power(int u,int v)
{
	static int sm;
	for(sm=1;v;v>>=1,u=(long long)u*u%mod)if(v&1)
		sm=(long long)sm*u%mod;
	return sm;
}

inline void solve()
{
	Rep(i,1,n)Chkmax(r,min(min(abs(a[i]-b[i]),abs(a[i]-b[i]+L)),abs(-b[i]-L+a[i])));
	l=0ll;
	static long long mid;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(Judge(mid))r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",power(2,l%(mod-1)));
}

inline void file()
{
	freopen("queue.in","r",stdin);
	freopen("queue.out","w",stdout);
}

int main()
{
	file();
    init();
    solve();
	cerr<<1.0*clock()/CLOCKS_PER_SEC<<endl;
    return 0;
}
