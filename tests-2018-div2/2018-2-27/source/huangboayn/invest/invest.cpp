#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+10;
struct node{
	int num,s,l;
}a[maxn];
bool cmp(node x,node y){
	if(x.l-x.s==y.l-y.s)return x.num<y.num;
	return x.l-x.s>y.l-y.s;
}
int change(string c){
	int sum=0;
	for(register int i=0;i<c.size();i++)
		sum=sum*10+c[i]-'0';
		return sum;
}
int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	int i,j,k,m,n;
	cin>>n;
	for(register int i=1;i<=n;i++)
	scanf("%d",&a[i].s);
	for(register int i=1;i<=n;i++)
	a[i].num=i;
	string c;
	sort(a+1,a+n+1,cmp);
	while(cin>>c && c!="EndOfCurrentCase"){
		if(c[0]=='R'){
			sort(a+1,a+n+1,cmp);
			printf("%d %d\n",a[1].num,a[2].num);
		}
		else{
			int x=change(c),y;
			scanf("%d",&y);
			for(register int i=1;i<=n;i++)
				if(a[i].num==x){
				a[i].l=y;
				break;
			}
		}
	}
	return 0;
}
