#include<bits/stdc++.h>
using namespace std;

inline int read(){
	int x;char c;
	while((c=getchar())<'0'||c>'9');
	x=c-48;
	while((c=getchar())>='0'&&c<='9')x=x*10+c-48;
	return x;
}

const int maxn=4e5+10;
int n,q,a[maxn],ans[maxn];
int pre[maxn],last[maxn],bad[maxn];
struct quest{
	int l,r,id;
	bool operator< (quest o)const{
		return l>o.l;
	}
}query[maxn];
struct bit{
	int a[maxn];
	inline void modify(int pos,int val){
		while(pos<=n){
			a[pos]+=val;
			pos+=pos&-pos;
		}
	}
	inline int sum(int pos){
		int res=0;
		while(pos){
			res+=a[pos];
			pos-=pos&-pos;
		}
		return res;
	}
}bit1,bit2;

int main(){
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	n=read();
	for(int i=1;i<=n;++i)
		a[i]=read();
	q=read();
	for(int i=1;i<=q;++i)
		query[i].l=read(),query[i].r=read(),query[i].id=i;
	sort(query+1,query+q+1);
	for(int i=n,p=1;i;--i){
		int val=a[i];
		pre[i]=last[val];
		if(last[val])
			bit1.modify(last[val],-1);
		last[val]=i;
		bit1.modify(last[val],1);
		if(pre[i]&&pre[pre[i]]&&i+pre[pre[i]]!=pre[i]<<1){
			if(bad[val])
				bit2.modify(bad[val],-1);
			bad[val]=pre[pre[i]];
			bit2.modify(bad[val],1);
		}
		while(p<=q&&query[p].l==i){
			int cnt1=bit1.sum(query[p].r),cnt2=bit2.sum(query[p].r);
			ans[query[p].id]=cnt1+(cnt1==cnt2);
			++p;
		}
	}
	for(int i=1;i<=q;++i)
		printf("%d\n",ans[i]);
	return 0;
}
