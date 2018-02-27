#include<set>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
struct edge{
	int dist;
	short to;
	edge(int t,int d):dist(d),to(t){}
};
struct factory{
	int b,c;
	set<edge> e;
	void read(){
		scanf("%d%d",&b,&c);
	}
};
inline bool operator<(const edge&,const edge&);
int main(){
	int n,m;
	long long *f;
	factory *fac;
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	scanf("%d",&n);
	f=new long long[n+1];
	fac=new factory[n+1];
	memset(f,127,sizeof(long long)*(n+1));
	for(int i=0;i<n;i++)
		fac[i].read();
	fac[n].b=fac[n].c=1000000000;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int x,y,dist;
		scanf("%d%d%d",&x,&y,&dist);
		fac[x].e.insert(edge(y,dist));
		fac[y].e.insert(edge(x,dist));
		if(!x)
			f[y]=min(f[y],/*(long long)dist*/(long long)(dist%(fac[y].b+fac[y].c)<fac[y].c?dist:(dist+(fac[y].b+fac[y].c-1))/(fac[y].b+fac[y].c)*(fac[y].b+fac[y].c)));
		if(!y)
			f[x]=min(f[x],/*(long long)dist*/(long long)(dist%(fac[x].b+fac[x].c)<fac[x].c?dist:(dist+(fac[x].b+fac[x].c-1))/(fac[x].b+fac[x].c)*(fac[x].b+fac[x].c)));
	}
	for(int k=1;k<n;k++)
		for(int i=1;i<=n;i++){
			set<edge>::iterator it;
			edge e(i,0);
			it=fac[k].e.find(e);
			if(it!=fac[k].e.end())
				f[i]=min(f[i],(f[k]+it->dist)%(fac[i].b+fac[i].c)<fac[i].c?f[k]+it->dist:(f[k]+it->dist+(fac[i].b+fac[i].c-1))/(fac[i].b+fac[i].c)*(fac[i].b+fac[i].c));
		}
	printf("%lld",f[n]);
	delete[] fac;
	delete[] f;
	return 0;
}
inline bool operator<(const edge &x,const edge &y){
	return x.to<y.to;
}
