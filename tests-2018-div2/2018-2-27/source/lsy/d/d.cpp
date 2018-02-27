#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
long long f[1000010],v[1000010],a[1010][1010],b[1000010],c[1000010],n;
long long dfs(long long x){
	long long i;
	if(v[x])return f[x];
	v[x]=1;
	if(x==0)return f[x]=0;
	f[x]=1000000000000010;
	for(i=0;i<=n;i++)
	    if(a[x][i]){
	    	long long h=dfs(i);
	    	h+=a[x][i];
	    	if(n==x)f[x]=min(f[x],h);
	    	else{
	    	    if(h%(b[x]+c[x]+1)<=c[x])
	    	         f[x]=min(f[x],h);
	    	         else f[x]=min(f[x],h/(b[x]+c[x])*(b[x]+c[x])+c[i]+1);
	    	}
	    }
	return f[x];
}
int main(){
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	long long i,j,k,m,x,y,t;
	scanf("%lld",&n);
	for(i=0;i<n;i++){
	     scanf("%lld%lld",&b[i],&c[i]);
	     b[i]-=1;
	     c[i]-=1;
	 }
	scanf("%lld",&m);
	for(i=1;i<=m;i++){
	    scanf("%lld%lld%lld",&x,&y,&t);
	    a[x][y]=t;
	    a[y][x]=t;
    }
	printf("%lld\n",dfs(n));
	return 0;
}

