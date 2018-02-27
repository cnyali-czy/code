#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cstdio>
#define REP(i,a,b) for(register int i=a;i<=b;++i)
#define DREP(i,a,b) for(register int i=a;i>=b;--i)
#define MREP(i,x) for(register int i=beg[x];i;i=E[i].last)
using namespace std;
void File(){
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
}
const int maxn=777+10;
const int maxm=33333+10;
const int inf=0x3f3f3f3f;
int n,m,len,beg[maxn],t1[maxn],t2[maxn];
struct edge{
	int to;
	int last;
	int w;
}E[maxm*2];
void add(int u,int v,int w){
	++len;
	E[len].to=v;
	E[len].last=beg[u];
	beg[u]=len;
	E[len].w=w;
}
int f[maxn];
bool vis[maxn];
int main(){
	File();
	scanf("%d",&n);
	REP(i,0,n-1)scanf("%d%d",&t2[i],&t1[i]);
	scanf("%d",&m);
	REP(i,1,m){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	REP(i,0,n)f[i]=inf;
	f[0]=1;
	REP(i,1,n){
		int b=-1,minx=inf;
		REP(j,0,n)if(!vis[j] && f[j]<minx){
			minx=f[j];
			b=j;
		}
		if(b==-1)break;
		vis[b]=1;
		MREP(j,b){
			int v=E[j].to;
			if(v==n){f[n]=min(f[n],f[b]+E[j].w);continue;}
			int t=(f[b]+E[j].w-1)%(t1[v]+t2[v])+1;
			if(t>=1 && t<t1[v] && (f[b]+E[j].w)<f[v])
				f[v]=f[b]+E[j].w;
			else{
				int p=f[b]+E[j].w-t+t1[v]+t2[v];
				if(p<f[v])f[v]=p;
			}
		}
	}
	printf("%d\n",f[n]);
	return 0;
}
