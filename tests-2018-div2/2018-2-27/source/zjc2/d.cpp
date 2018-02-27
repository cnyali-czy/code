#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
const int maxn=10000+10,inf=1000000000;
using namespace std;
int f[maxn][maxn],a[maxn],b[maxn],c[maxn],d[maxn]; 
int n,m,w;
int pd(int k,int sum){
	if(k==n)return 0;
	int w=b[k]+c[k];
	int v=sum%w;
	if(v<=c[k]){
		return 0;
	}
	else return w-v;
}
int main(){
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	int i,j,k;
	cin>>n;
	for(i=0;i<n;i++){
		cin>>b[i]>>c[i];d[i]=1;
	}
	d[n]=1;
	cin>>m;
	for(i=1;i<=m;i++){
		int x,y,z;
		cin>>x>>y>>z;
		f[x][y]=z;f[y][x]=z;
	}
	for(i=0;i<=n;i++)a[i]=inf;a[0]=0;
	for(i=0;i<=n;i++){
		int x=inf,y,z;
		for(j=1;j<=n;j++){
			if(d[j]==1 && a[j]<x){
				y=j;x=a[j];
			}
		}
		if(x==inf)break;
		d[y]=0;
		for(j=0;j<=n;j++){
			if(d[j]!=0 && f[y][j]!=0 && a[j]>f[y][j]+a[k]+pd(y,f[y][j]+a[k])){
				a[j]=f[y][j]+a[k]+pd(y,f[y][j]+a[k]);
			}
		}
	}
	cout<<a[n]<<endl;
	return 0;
}
