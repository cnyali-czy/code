#include<bits/stdc++.h>
using namespace std;
struct node{
    int f,x,h,y;
}a[100010];
char s[21],c[21];
int i,j,k,l,n,m,sum,tmp;
int cmp(node a,node b){
    if(a.x==b.x)return a.h<b.h;
    return a.x>b.x;
}
int cl(){
	int k=0,pj=0;
    for(int i=0;i<strlen(s);i++)
    k=k*10+(s[i]-48);
    return k;
}
int main()
{
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	scanf("%d",&n);
	for(i=1;i<=n;i++){scanf("%d\n",&a[i].y);a[i].h=i;a[i].f=1;}
    while(1){
	scanf("%s",&s);	
	if(s[0]=='E')return 0;
	if(s[0]=='R'){
	sort(1+a,1+a+n,cmp);
	printf("%d %d\n",a[1].h,a[2].h);
	}
	else {
	 tmp=cl();
	 scanf("%s",&s);
	 sum=cl();
	 for(j=1;j<=n;j++)
	    if(a[j].h==tmp){
	    if(a[j].f==0){a[j].x=0;a[j].f=1;}
	    else {a[j].x=sum-a[j].y;a[j].y=sum;}
        }
	}
	}
   return 0;
}
