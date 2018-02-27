#include<bits/stdc++.h>
using namespace std;
const int maxn=777+10,inf=999999999;
int a[maxn][maxn];
int b[maxn],c[maxn],p[maxn],t[maxn],n;
int pd(int x,int sum){
	if(n==x)return 0;
	int s=b[x]+c[x];
	int k=sum%s;
	if(k<=c[x])return 0;
	else return s-k;
}
int main(){
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	int i,j,k,m;
	cin>>n;
	for(register int i=0;i<=n-1;i++)
		scanf("%d%d",&b[i],&c[i]);
	cin>>m;
	for(register int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		a[x][y]=a[y][x]=z;
	}
	for(register int i=0;i<=n;i++)t[i]=inf;
	t[0]=0;
	for(register int i=0;i<=n;i++){
	int zx=inf;
	for(register int j=0;j<=n;j++)
	if(p[j]!=1 && t[j]<zx){
		k=j;
		zx=t[j];
	}
	if(zx==inf)break;
	if(k==n)break;
	p[k]=1;
	for(register int j=0;j<=n;j++)
	if(p[j]!=1 && a[k][j]!=0 &&  t[j]>a[k][j]+t[k]+pd(j,a[k][j]+t[k]))
    t[j]=a[k][j]+t[k]+pd(j,a[k][j]+t[k]);
	}
	cout<<t[n]<<endl;
	return 0;
}
