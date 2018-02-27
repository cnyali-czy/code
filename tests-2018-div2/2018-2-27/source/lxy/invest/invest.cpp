#include<bits/stdc++.h>
using namespace std;
struct node{
	int m,num;
}a[100001];
bool congdadaoxiao(node a,node b){
	return a.m>b.m;
}
int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	char b[1];
	int n;
	int i,q;
	char p[20];
	cin>>n;
	for(i=1;i<=n;i++)
		a[i].num=i;
	for(i=1;i<=n;i++)
		cin>>a[i].m;
	while(1){
		cin>>p;
		if(p[0]=='E') return 0;
		if(p[0]=='R') {
			sort(a+1,a+n+1,congdadaoxiao);
			if(a[1].m==a[2].m){
				if(a[1].num<a[2].num) cout<<a[1].num<<" "<<a[2].num<<endl;
				else cout<<a[2].num<<" "<<a[1].num;
			}
			else cout<<a[1].num<<" "<<a[2].num<<endl;
		}
		else {
			cin>>q;
			a[p[0]-'0'].m=q;
		}
	}
	return 0;
}
