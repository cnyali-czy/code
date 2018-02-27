#include<bits/stdc++.h>
const int maxm=20+5,maxn=100000+10;
using namespace std;
int n,m;  
int t[maxn],k[maxn];
char f[maxm];
int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	int l,i,j,d,a,b,p,dt;
	k[0]=-2147483647;
	scanf("%d",&n);
		for(i=1;i<=n;i++)                
	scanf("%d",&t[i]);   
		while(1){
			cin>>f;
			if(f[0]>='0' && f[0]<='9'){
				d=f[0]-'0';p=1;
				while(f[p]>='0' && f[p]<='9'){
					d=d*10+f[p]-'0';p++;
				}
				scanf("%d",&dt); k[d]=dt-t[d]; t[d]=dt;
			}
			if(f[0]=='E') return 0;
			if(f[0]=='R'){
				a=b=0;
				for(i=1;i<=n;i++)
					if(k[i]>k[a]){ b=a; a=i; }
				else
					if(k[i]>k[b]){ b=i; }
					printf("%d %d\n",a,b);
			}
		}                                   	
	return 0;
}       
