#include <bits/stdc++.h>
using namespace std;
const int N=410010;
struct tree{
	int l,r,father;
	long long w,tot,ex;
}t[N];
int n,m,rev[N],a[N],d[N],father[N],D[N];
long long ans,num0,num1,num2,num3,num4,num5,num6,num7,num8;
void reverse(int k){
	swap(t[k].l,t[k].r); rev[k]=0;
}
void pushdown(int k){
	if (rev[k]){
		reverse(t[k].r); reverse(t[k].l); rev[k]=0;
	}
}
inline void change(int k){
	t[k].tot=t[t[k].l].tot+t[t[k].r].tot+t[k].ex+t[k].w;
}
void zig(int k){
	int f=t[k].father; pushdown(f); pushdown(k);
	if (t[t[f].father].l==f) t[t[f].father].l=k; else if (t[t[f].father].r==f) t[t[f].father].r=k;
	t[k].father=t[f].father; t[f].l=t[k].r; t[t[f].l].father=f; t[k].r=f; t[f].father=k;
	change(f);
}
void zag(int k){
	int f=t[k].father; pushdown(f); pushdown(k);
	if (t[t[f].father].l==f) t[t[f].father].l=k; else if (t[t[f].father].r==f) t[t[f].father].r=k;
	t[k].father=t[f].father; t[f].r=t[k].l; t[t[f].r].father=f; t[k].l=f; t[f].father=k;
	change(f);
}
int splay_root(int k){
	return t[k].father&&(t[t[k].father].l==k||t[t[k].father].r==k);
}
void splay(int k){
	pushdown(k);
	while (splay_root(k)){
		int f=t[k].father;
		if (!splay_root(f)){
			if (k==t[f].l) zig(k); else zag(k);
			break;
		}
		int f2=t[f].father; pushdown(f2);
		if (t[f2].l==f){
			if (t[f].l==k) zig(f),zig(k); else zag(k),zig(k);
		} else if (t[f].l==k) zig(k),zag(k); else zag(f),zag(k);
	}
	change(k);
}
struct bian{
	int next,point;
}b[N<<1];
int p[N],len;
void ade(int k1,int k2){
	b[++len]=(bian){p[k1],k2}; p[k1]=len; D[k1]++;
}
void add(int k1,int k2){
	ade(k1,k2); ade(k2,k1);
}
void dfs(int k1,int k2){
	//cout<<"asd "<<k1<<" "<<k2<<endl;
	t[k1].father=k2; d[k1]=d[k2]+1;
	for (int i=p[k1];i;i=b[i].next){
		int j=b[i].point;
		if (j!=k2) dfs(j,k1);
	}
}
long long getans(long long a,long long b){
	if (a==0) return 0; else return min((a-b)*2,a-1);
}
void addin(int k1,int k2){
	num6+=d[k1]; int predis=d[k1];
	splay(k1); t[k1].w+=k2; change(k1); num0+=d[k1];
	if (t[k1].r){
		long long rsize=t[t[k1].r].tot,tot=t[k1].tot-t[t[k1].l].tot;
		ans-=getans(tot-k2,rsize); ans+=getans(tot,max(rsize,t[k1].w));
		if (rsize*2<tot+1){
			t[k1].ex+=rsize; t[k1].r=0; change(k1);
		}
		num1++;
	} else {
		long long tot=t[k1].tot-t[t[k1].l].tot;
		//cout<<"asd "<<tot<<" "<<t[k1].w<<" "<<ans<<" "<<endl;
		ans+=getans(tot,t[k1].w)-getans(tot-k2,t[k1].w-k2); //cout<<ans<<endl;
		num2++;
	}
	int now=k1; k1=t[k1].father; int flag=0,clo=d[k1];
	while (k1){
		//cout<<now<<" "<<k1<<endl;
		splay(k1); t[k1].ex+=k2; change(k1); num4++;
		if (t[k1].r){
			long long rsize=t[t[k1].r].tot;
			long long tot=t[k1].tot-t[t[k1].l].tot;
			long long cur=t[now].tot;
			//cout<<"update "<<now<<" "<<k1<<" "<<tot<<" "<<rsize<<" "<<cur<<" "<<ans<<" ";
			ans-=getans(tot-k2,rsize);
			ans+=getans(tot,max(rsize,cur)); //cout<<ans<<endl;
			int bo=0;
			if (rsize*2<tot+1){
				t[k1].ex+=rsize; t[k1].r=0; change(k1); bo++;
			}
			if (cur*2>=tot+1){
				t[k1].ex-=cur; t[k1].r=now; change(k1); bo++;
			}
			if (bo){
				num3++; num8+=D[k1];
				if (flag){
					num5++; flag=0;
				}
				clo=d[k1];
			} else flag=1;
		} else {
			long long tot=t[k1].tot-t[t[k1].l].tot;
			long long cur=t[now].tot; int bo=0;
			ans-=getans(tot-k2,t[k1].w);
			ans+=getans(tot,max(t[k1].w,cur));
			if (cur*2>=tot+1){
				t[k1].ex-=cur; t[k1].r=now; change(k1); bo++;
			}
			if (bo){
				num3++; num8+=D[k1];
				if (flag){
					num5++; flag=0;
				}
				clo=d[k1];
			} else flag=1;
		}
		now=k1; k1=t[k1].father;
	}
	num6-=clo; num7=max(num7,1ll*predis-clo);
}
int findfather(int k1){
	if (father[k1]==k1) return k1; return father[k1]=findfather(father[k1]);
}
int main(){
	scanf("%d%d",&n,&m); ans=0;
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),father[i]=i;
	for (int i=1;i<n;i++){
		int k1,k2; scanf("%d%d",&k1,&k2); add(k1,k2);
		assert(findfather(k1)!=findfather(k2));
		father[findfather(k1)]=findfather(k2);
	}
	dfs(1,0);
	for (int i=1;i<=n;i++){
		addin(i,a[i]); //cout<<ans<<endl;
	}
	printf("%lld\n",ans);
	for (;m;m--){
		int k1,k2; scanf("%d%d",&k1,&k2); addin(k1,k2);
		assert(1<=k1&&k1<=n);
		printf("%lld\n",ans);
	}
	cerr<<"totaldis "<<num0<<endl;
	cerr<<"changek10 "<<num1<<endl;
	cerr<<"changek11 "<<num2<<endl;
	cerr<<"changeimp "<<num3<<endl;
	cerr<<"totalimp "<<num4<<endl;
	cerr<<"interrupted "<<num5<<endl;
	cerr<<"changedis "<<num6<<endl;
	cerr<<"maxchangedis "<<num7<<endl;
	cerr<<"totD "<<num8<<endl;
}
