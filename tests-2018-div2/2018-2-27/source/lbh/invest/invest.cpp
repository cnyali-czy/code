#include<bits/stdc++.h>
using namespace std;
int a[10000+10];
int b[10000+10];
char c[20];
int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	int i,j,k,m,n;
	int max1=0,max2=0;
	int max1id=0,max2id=0;
	cin>>n;
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	while(1){
		cin>>c;
		if(c[0]=='E')return 0;
		if(c[0]=='R'){
			max1=0,max2=0;
			max1id=0,max2id=0;
			for(i=1;i<=n;i++){
				//if(i==max1id||i==max2id)continue;
				if(b[i]>max1||(b[i]==max1&&i<max1id)){
					max2=max1;
					max2id=max1id;
					max1=b[i];
					max1id=i;
				}
				else if(b[i]>max2||(b[i]==max2&&i<max2id)){
					max2=b[i];
					max2id=i;
				}
			}
			cout<<max1id<<" "<<max2id<<endl;
		}
		else{
			int t=strlen(c),id=0;
			for(i=0;i<t;i++){
				id=id*10+c[i]-48;
			}
			cin>>m;
			//cout<<id<<" "<<m<<endl;
			b[id]=m-a[id];
			a[id]=m;
		}
	}
	
	return 0;
}
