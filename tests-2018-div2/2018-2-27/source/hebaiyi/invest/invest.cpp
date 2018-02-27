#include<bits/stdc++.h>
using namespace std;
int a[100001];
int main(){
	int i,j,k,n,m;
	char c[20];
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	cin>>n;
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	while(1){
		cin>>c;
		int fff=0;
		if(c[0]>='0'&&c[0]<='9'){
			for(j=0;j<strlen(c);j++)fff=fff*10+c[j]-'0';
			cin>>k;
			a[fff]+=k;
		}
		//	cout<<"fff";
		if(c[0]=='R'){
			int mx1=1,mx2=0;
			for(j=2;j<=n;j++){
				if(a[j]>a[mx1]){
					mx2=mx1;
					mx1=j;
				}
				else if(a[j]>a[mx2])mx2=j;
			}
			cout<<mx1<<" "<<mx2<<endl;
		}
		if(c[0]=='E')return 0;
	}
	return 0;
}
