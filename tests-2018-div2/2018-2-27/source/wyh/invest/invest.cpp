#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int N=100000+10;
struct node{
	int id,mon,pri;
}a[N];
string s;

int cmp(node x,node y){
	return ((x.pri>y.pri) || (x.pri==y.pri && x.id<y.id));
}

int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	int i,j,k,m,n;
	cin>>n;
	for(i=1;i<=n;i++){
		scanf("%d",&a[i].mon);
		a[i].id=i;
	}
	cin>>s;
	while(s!="EndOfCurrentCase"){
		if(s=="Report"){
			sort(a+1,a+n+1,cmp);
			cout<<a[1].id<<" "<<a[2].id<<endl;
		}
		else{
			cin>>k;m=s[0]-'0';
			for(i=1;i<=n;i++)
				if(a[i].id==m){
					a[i].pri=k-a[i].mon;
					a[i].mon=k;
					break;
				}
		}
		cin>>s;
	}
	return 0;
}
/*
4
10
20
30
40
1 100
3 80
4 70
Report
Report
2 60
Report
EndOfCurrentCase
*/
