#include<bits/stdc++.h>
using namespace std;
int read(){
	int a=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while('0'<=c&&c<='9'){
		a=a*10+c-48;
		c=getchar();
	}
	return a;
}
#define MN 500005
int n,q,deg[MN];

int siz[MN],fa[MN],dep[MN],id[MN],top[MN],w[MN],cnt,ID[MN];
int TOT;
vector<int>edge[MN];
void dfs1(int x){
	siz[x]=1;
	for(int i=0;i<edge[x].size();++i){
		int v=edge[x][i];
		if(fa[x]==v)continue;
		dep[v]=dep[x]+1;
		fa[v]=x;
		dfs1(v);
		siz[x]+=siz[v];
		if(siz[w[x]]<siz[v])w[x]=v;
	}
}
void dfs2(int x){
	id[x]=++cnt;ID[cnt]=x;
	if(w[x]){top[w[x]]=top[x];dfs2(w[x]);}
	for(int i=0;i<edge[x].size();++i){
		int v=edge[x][i];
		if(fa[x]==v||w[x]==v)continue;
		top[v]=v;
		dfs2(v);
	}
}
#define Ls (x<<1)
#define Rs (x<<1|1)
#define mid ((l+r)>>1)
struct data{
	int sum,Max,Min,tag;
}W[MN<<2];
void ptag(int x,const int &v){
	W[x].tag+=v;
	W[x].Max+=v;
	W[x].Min+=v;
}
void pd(int x){
	if(W[x].tag){
		if(W[Ls].sum){
			ptag(Ls,W[x].tag);
		//	tag[Ls]+=tmp;
		//	Max[Ls]+=tmp;
		//	Min[Ls]+=tmp;
		}
		if(W[Rs].sum){
			ptag(Rs,W[x].tag);
		//	tag[Rs]+=tmp;
		//	Max[Rs]+=tmp;
		//	Min[Rs]+=tmp;
		}
		W[x].tag=0;
	}
}
void pushup(int x){
	W[x].Max=max(W[Ls].Max,W[Rs].Max)+W[x].tag;
	W[x].Min=min(W[Ls].Min,W[Rs].Min)+W[x].tag;
//	W[x].sum=W[Ls].sum+W[Rs].sum;
}
int ask(int x,int l,int r,int b,int e){
	if(b<=l&&r<=e)return W[x].sum;
	if(l>e||r<b||!W[x].sum)return 0;
	pd(x);
	int res=0;
	if(b<=mid)res=ask(Ls,l,mid,b,e);
	if(e>mid)res+=ask(Rs,mid+1,r,b,e);
	return res;
}
int ned;
void Ins(int x,int l,int r,int loc,int v){
	W[x].sum+=v;
	if(l==r){
		if(v==1){
			W[x].Max=W[x].Min=ask(1,1,n,l,id[ID[l]]+siz[ID[l]]-1);
		}
		else{
			W[x].Max=-1e9;
			W[x].Min=1e9;
		}
		return;
	}
	pd(x);
	if(loc<=mid)Ins(Ls,l,mid,loc,v);
	else Ins(Rs,mid+1,r,loc,v);
	pushup(x);
}
void change(int x,int l,int r,int b,int e,int v){
	if(!W[x].sum)return;
	if(b<=l&&r<=e){
//		cerr<<"chg: "<<l<<" "<<r<<endl;
		ptag(x,v);
		return;
	}
//	pd(x);
	if(b<=mid&&W[Ls].sum)change(Ls,l,mid,b,e,v);
	if(e>mid&&W[Rs].sum)change(Rs,mid+1,r,b,e,v);
	pushup(x);
}
void search(int x,int l,int r,int v){
//	return;
	if(!W[x].sum||TOT>=ned||W[x].Max<v)return;
	if(W[x].Min>=v){TOT+=W[x].sum;return;}
	search(Ls,l,mid,v-W[x].tag);
	search(Rs,mid+1,r,v-W[x].tag);
}
int main(){
	freopen("3329.in","r",stdin);
	freopen("dog.out","w",stdout);
	n=read();
	for(int i=1;i<=n*4;++i)W[i].Max=-1e9;
	for(int i=1;i<=n*4;++i)W[i].Min=1e9;
	bool flag=1;
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		deg[x]++;deg[y]++;
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	q=read();
	dep[1]=1;dfs1(1);
	top[1]=1;dfs2(1);
	int res=0,upd=0;
	for(int i=1;i<=q;++i){
		int tp=read(),v=read();
		if(tp==1){
			Ins(1,1,n,id[v],1);
			v=fa[v];
			while(v){
				change(1,1,n,id[top[v]],id[v],1);
				v=fa[top[v]];
			}
			TOT=0;ned=res+1;
			search(1,1,n,res+1);
			if(TOT>res) res++;
		}
		else{
			Ins(1,1,n,id[v],-1);
			v=fa[v];
			while(v){
				change(1,1,n,id[top[v]],id[v],-1);
				v=fa[top[v]];
			}
			TOT=0;ned=res;
			search(1,1,n,res);
			if(TOT<=res-1)res--;
		}
		printf("%d\n",res);
	}
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
