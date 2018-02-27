#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
int b[1000010],p[1000010],u[1000010],a[1000010],n;
int add(int x,int y){
	b[p[x]]=y;
	while(((y<b[p[x]*2] || (u[p[x]*2]<x && y==b[p[x]*2]))&&p[x]*2<=n) || ((y<b[p[x]*2+1] ||(u[p[x]*2+1]<x && y==b[p[x]*2+1]))&&p[x]*2+1<=n)){
		int i=p[x]*2;
		int j=p[x]*2+1;
		if(b[i]<b[j] ||(u[i]>u[j] && b[i]==b[j]) &&j<=n)i=j;
		swap(b[i],b[p[x]]);
		swap(u[i],u[p[x]]);
		swap(p[u[i]],p[u[p[x]]]);
	}
	while(y>b[p[x]/2] &&p[x]/2>0){
		swap(b[p[x]],b[p[x]/2]);
		swap(u[p[x]/2],u[p[x]]);
		swap(p[u[p[x]]],p[u[p[x]/2]]);
	}		
}
int main(){
	int i,j,k,m;
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	char c;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
	    scanf("%d",&a[i]);
	    p[i]=i;
	    u[i]=i;
	}
	while(1){
		scanf("%c",&c);
		while(c=='\n')scanf("%c",&c);
		if('0'<=c && c<='9'){
			int sum1=0,sum2=0;
		    while('0'<=c && c<='9'){
			    sum1=sum1*10+c-'0';
			    scanf("%c",&c);
			}
			scanf("%c",&c);
		    while('0'<=c && c<='9'){
			    sum2=sum2*10+c-'0';
			    scanf("%c",&c);
			}
			add(sum1,sum2-a[sum1]);
			a[sum1]=sum2;
		}else 
		if(c=='R'){
		    printf("%d",u[1]);
		    int o=2;
			if((b[3]>b[2]) ||(b[3]==b[2] && u[3]<=u[2]))o++;
			printf(" %d\n",u[o]);
			scanf("%c",&c);
			while('a'<=c && c<='z')scanf("%c",&c);
		}else break;
	}
		
	return 0;
}/*
6
10
9
100
700
5
99
Report
1 80
2 800
3 400
Report
6 200
2 60
Report
6 700
Report
E
*/

