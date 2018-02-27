#include<bits/stdc++.h>
using namespace std;
int a[100010],s[100010];
string s1;
int main( ){
	int k,n,m1,m2,p1,p2,q;
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	while(1){
		cin>>s1;
		if(s1[0]=='E')break;
		else if(s1[0]=='R'){
			m1=max(s[1],s[2]);m2=min(s[1],s[2]);
			if(s[2]>s[1]){p1=2;p2=1;}else{p1=1;p2=2;}
			for(register int i=3;i<=n;i++){
				if(s[i]>m1){m1=s[i];p1=i;}
				else if(s[i]<=m1){
					if(s[i]>m2){m2=s[i];p2=i;}
				}
			}
			printf("%d %d\n",p1,p2);
		}
		else{
			k=0;
			for(register int i=0;i<s1.size( );i++)k=k*10+s1[i]-'0';
			scanf("%d",&q);
			s[k]=q-a[k];
			a[k]=q;
		}
	}
	return 0;
}

