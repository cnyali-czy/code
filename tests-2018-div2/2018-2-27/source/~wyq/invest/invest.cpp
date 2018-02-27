#include<bits/stdc++.h>
using namespace std;
const int inf=1000000;
struct node{
	int cs,sy,f,zz;
}a[100010];
int cmp(node a,node b){
	return a.zz>b.zz;
}
int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	int i,j,k,m,n;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>a[i].cs;
	}
	string s;
	char c;
	int l;
	while(1){
		cin>>s;
		l=s.size();
		if(s[0]>='0' && s[0]<='9'){
			cin>>k;
			j=int(s[0])-48;
			a[j].sy=k-a[j].cs;
		}
		if(s[0]=='R'){
			for(i=1;i<=n;i++){
				a[i].zz=a[i].sy;
				a[i].f=i;
			}
			sort(a+1,a+n+1,cmp);
			if(a[1].f<a[2].f)
				cout<<a[1].f<<" "<<a[2].f<<endl;
			else
				cout<<a[2].f<<" "<<a[1].f<<endl;
		}
		if(s[0]=='E')
			break;
	}
	return 0;
}
