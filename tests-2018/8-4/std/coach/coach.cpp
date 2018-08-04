#include<bits/stdc++.h>
#define ui unsigned int
#define ll long long
#define db double
#define ld long double
#define ull unsigned long long
const int MAXN=500000+10,inf=0x3f3f3f3f;
int n,m,k,a[MAXN],cnt,mx=-inf,mn=inf;
std::pair<int,int> stk[MAXN];
#define Mid ((l+r)>>1)
#define ls rt<<1
#define rs rt<<1|1
#define lson ls,l,Mid
#define rson rs,Mid+1,r
struct Segment_Tree{
	int sum[MAXN<<2],let[MAXN<<2];
	inline void PushUp(int rt)
	{
		sum[rt]=sum[ls]+sum[rs];
	}
	inline void PushDown(int rt,int len)
	{
		sum[ls]=let[rt]*(len-(len>>1));
		sum[rs]=let[rt]*(len>>1);
		let[ls]=let[rs]=let[rt];
		let[rt]=-1;
	}
	inline void Build(int rt,int l,int r,int k)
	{
		let[rt]=-1;
		if(l==r)sum[rt]=(a[l]>k?1:0);
		else Build(lson,k),Build(rson,k),PushUp(rt);
	}
	inline void Update(int rt,int l,int r,int L,int R,int k)
	{
		if(L<=l&&r<=R)sum[rt]=k*(r-l+1),let[rt]=k;
		else
		{
			if(let[rt]!=-1)PushDown(rt,r-l+1);
			if(L<=Mid)Update(lson,L,R,k);
			if(R>Mid)Update(rson,L,R,k);
			PushUp(rt);
		}
	}
	inline int Query(int rt,int l,int r,int L,int R)
	{
		if(L<=l&&r<=R)return sum[rt];
		else
		{
			if(let[rt]!=-1)PushDown(rt,r-l+1);
			int res=0;
			if(L<=Mid)res+=Query(lson,L,R);
			if(R>Mid)res+=Query(rson,L,R);
			return res;
		}
	}
};
Segment_Tree T;
#undef Mid
#undef ls
#undef rs
#undef lson
#undef rson
template<typename T> inline void read(T &x)
{
	T data=0,w=1;
	char ch=0;
	while(ch!='-'&&(ch<'0'||ch>'9'))ch=getchar();
	if(ch=='-')w=-1,ch=getchar();
	while(ch>='0'&&ch<='9')data=((T)data<<3)+((T)data<<1)+(ch^'0'),ch=getchar();
	x=data*w;
}
template<typename T> inline void write(T x,char ch='\0')
{
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
	if(ch!='\0')putchar(ch);
}
template<typename T> inline void chkmin(T &x,T y){x=(y<x?y:x);}
template<typename T> inline void chkmax(T &x,T y){x=(y>x?y:x);}
template<typename T> inline T min(T x,T y){return x<y?x:y;}
template<typename T> inline T max(T x,T y){return x>y?x:y;}
#define ft first
#define sd second
inline bool check(int num)
{
	T.Build(1,1,n,num);
	for(register int i=1,l,r,tot,nl,nr;i<=cnt;++i)
	{
		l=stk[i].ft,r=stk[i].sd;
		tot=T.Query(1,1,n,l,r);
		nl=(tot+1)>>1,nr=tot-nl;
		if(nl)T.Update(1,1,n,l,l+nl-1,1);
		if(nr)T.Update(1,1,n,r-nr+1,r,1);
		if(tot!=r-l+1)T.Update(1,1,n,l+nl,r-nr,0);
	}
	return T.Query(1,1,n,k,k)==0;
}
#undef ft
#undef sd
int main()
{
	freopen("coach.in","r",stdin);
	freopen("coach.out","w",stdout);
	read(n);read(m);read(k);
	for(register int i=1;i<=n;++i)read(a[i]),chkmin(mn,a[i]),chkmax(mx,a[i]);
	for(register int i=1;i<=m;++i)
	{
		int opt;read(opt);
		if(opt==1)
		{
			int l,r;read(l);read(r);
			stk[++cnt]=std::make_pair(l,r);
		}
		if(opt==2)
		{
			int x;read(x);
			cnt=max(0,cnt-x);
		}
	}
	int l=mn,r=mx,ans=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	write(ans,'\n');
	return 0;
}

