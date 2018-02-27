#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<cstring>
const int maxn=100000+10;
using namespace std;
struct node{
	int x,y,sum;
}a[maxn];
int cmp(node x,node y){
	if(x.y == y.y)return x.sum<y.sum;
	else return x.y>y.y;
}
int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	int i,j,k,m,n;
	cin>>n;
	for(register int i=1;i<=n;i++){
		cin>>a[i].x;
		a[i].sum=i;
	}
	string s;
	cin>>s;
	while(s!="EndOfCurrentCase"){
		if(s=="Report"){
			sort(a+1,a+n+1,cmp);
			cout<<a[1].sum<<" "<<a[2].sum<<endl;
		}
		else {
			int u,v;
			cin>>v;
			u=s[0]-'0';
			for(register int i=1;i<=n;i++){
				if(a[i].sum==u){
					a[i].y=v-a[i].x;
					a[i].x=v;
				}
			}
		}
		cin>>s;
	}
	return 0;
}
