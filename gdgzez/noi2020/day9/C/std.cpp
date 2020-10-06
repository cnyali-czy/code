#include<bits/stdc++.h>
using namespace std;
template<typename T>inline T read(){
	T x=0,f=0;char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return f?-x:x;
}
namespace run{
	const int N=4e5+9,mod=998244353;
	inline int add(int x,int y){return x+y>=mod?x-mod+y:x+y;}
	inline int sub(int x,int y){return x>=y?x-y:x+mod-y;}
	inline int qpow(int x,int y){
		int ret=1;
		while(y){
			if(y&1) ret=1LL*ret*x%mod;
			x=1LL*x*x%mod;y>>=1;
		}
		return ret;
	}

	int head[N],nex[N],to[N],cnt=1;
	inline void adde(int u,int v){
		nex[++cnt]=head[u];
		head[u]=cnt,to[cnt]=v;
	}

	int rev[N<<2],limit,bit,Gi=(mod+1)/3;
	inline void prepare(int len){
		limit=1,bit=0;
		while(limit<len) limit<<=1,bit++;
		for(int i=1;i<limit;i++)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	}
	inline void NTT(int *a,int inv){
		for(int i=1;i<limit;i++)
			if(i<rev[i]) swap(a[i],a[rev[i]]);
		for(int mid=1;mid<limit;mid<<=1){
			int tmp=qpow(~inv?3:Gi,(mod-1)/(mid<<1));
			for(int i=0,R=mid<<1;i<limit;i+=R){
				for(int j=0,omega=1;j<mid;j++,omega=1LL*omega*tmp%mod){
					int x=a[i+j],y=1LL*omega*a[i+j+mid]%mod;
					a[i+j]=add(x,y),a[i+j+mid]=sub(x,y);
				}
			}
		}
		if(inv==-1){
			inv=qpow(limit,mod-2);
			for(int i=0;i<limit;i++) a[i]=1LL*a[i]*inv%mod;
		}
	}

	const int Log=23;
	int h[Log][N<<2],w[N],p[N],q[N],A[N<<2],B[N<<2];
#define mid ((l+r)>>1)
	inline void cdq(int l,int r,int dep){
		if(l==r) return h[dep][0]=w[l],h[dep][1]=p[l],h[dep][2]=q[l],void();

		int retL=1+2*(mid-l+1),retR=1+2*(r-mid);
		for(int i=0;i<retL+retR-1;i++) h[dep+1][i]=0;
		cdq(l,mid,dep+1);
		for(int i=0;i<retL;i++) h[dep][i]=h[dep+1][i];
		for(int i=0;i<retL+retR-1;i++) h[dep+1][i]=0;
		cdq(mid+1,r,dep+1);

		prepare(retL+retR-1);
		for(int i=0;i<limit;i++) A[i]=B[i]=0;
		for(int i=0;i<retL;i++) A[i]=h[dep][i];
		for(int i=0;i<retR;i++) B[i]=h[dep+1][i];
		NTT(A,1),NTT(B,1);
		for(int i=0;i<limit;i++) A[i]=1LL*A[i]*B[i]%mod;
		NTT(A,-1);

		for(int i=0;i<retL+retR-1;i++) h[dep][i]=A[i];
	}

	int n,m;
	int f[N][2][2],a[N],dfn[N],low[N],num,ok[N];
	vector<int> wt[N>>1];
	inline void dfs(int u,int pre){
		dfn[u]=low[u]=++num;
		int mn=n+1,pos=0;
		for(int i=head[u];i;i=nex[i]) if(i^(pre^1)){
			if(!dfn[to[i]]){
				dfs(to[i],i);
				low[u]=min(low[u],low[to[i]]);
				if(low[to[i]]<dfn[u]) pos=to[i];
				else wt[u].push_back(to[i]);
			}else low[u]=min(low[u],dfn[to[i]]),mn=min(mn,dfn[to[i]]);
		}

		int tot=0;
		for(int i=0;i<(int)wt[u].size();i++){
			int v=wt[u][i];++tot;
			w[tot]=f[v][0][0],p[tot]=f[v][1][0],q[tot]=0;
			if(low[v]==dfn[u]) p[tot]=add(p[tot],f[v][0][1]),q[tot]=f[v][1][1];
		}
		if(tot) cdq(1,tot,0);
		else h[0][0]=1;


		int tmp2=0,tmp1=0,tmp=0;
		for(int i=0;i<=min(a[u]-2,tot*2);i++) tmp2=add(tmp2,h[0][i]);
		tmp1=tmp2;
		if(a[u]>=1 && a[u]-1<=2*tot) tmp1=add(tmp1,h[0][a[u]-1]);
		tmp=tmp1;
		if(a[u]<=2*tot) tmp=add(tmp,h[0][a[u]]);
		printf("%d %d\n", u, tot + tot);
		if(!tot) printf("1 ");
		else for(int j=0;j<=tot+tot;j++)printf("%d ",h[0][j]);puts("");

		if(mn==low[u]){
			f[u][0][0]=tmp2,f[u][0][1]=tmp1,f[u][1][0]=tmp1,f[u][1][1]=tmp;
		}else{
			if(low[u]<dfn[u]){
				f[u][0][1]=(1LL*tmp2*f[pos][1][1]+1LL*tmp1*f[pos][0][1])%mod;
				f[u][1][1]=(1LL*tmp1*f[pos][1][1]+1LL*tmp*f[pos][0][1])%mod;
				f[u][0][0]=(1LL*tmp1*f[pos][0][0]+1LL*tmp2*f[pos][1][0])%mod;
				f[u][1][0]=(1LL*tmp1*f[pos][1][0]+1LL*tmp*f[pos][0][0])%mod;
			}else f[u][0][0]=tmp1,f[u][1][0]=tmp;
		}
	}

	int main(){
		n=read<int>(),m=read<int>();
		for(int i=1;i<=m;i++){
			int u=read<int>(),v=read<int>();
			adde(u,v),adde(v,u);
		}
		for(int i=1;i<=n;i++) a[i]=read<int>();

		dfs(1,0);
		printf("%d\n",f[1][1][0]);
		return 0;
	}
}
int main(){
	freopen("C.in","r",stdin);
	freopen("std.out","w",stdout);
	return run::main();
}
