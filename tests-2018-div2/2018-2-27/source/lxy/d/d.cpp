#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,t,pt,pl=0;
	int i;
	int a[800],b[800],f[800],c[40000],d[40000],e[40000];
	cin>>n;
	for(i=0;i<n;i++)
		{
			cin>>a[i]>>b[i];
			f[i]=a[i]+b[i];
		}
	cin>>m;
	for(i=0;i<m;i++)
		cin>>c[i]>>d[i]>>e[i];
	t=0;i=1;
	while(pl!=n){
		pt=t;
		if(f[pl]<a[pl]) t+=e[pl];
		else t+=b[pl]-f[pl]+a[pl];
		for(i=0;i<n;i++)
		{
			f[i]-=t-pt;
			if(f[i]<0) f[i]=-f[i];
		}
		pl++;
	}
	cout<<t;
	return 0;
}
