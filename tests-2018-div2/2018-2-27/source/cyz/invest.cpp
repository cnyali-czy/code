#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+10;
struct node{
	int id,prize,money;
}a[maxn];
inline bool cmp(node a,node b){
	if(a.money==b.money) return a.id<b.id;
	else return a.money>b.money;
}
inline int zh(string l){
	int sum=1,ret=0;
	for(int i=1;i<=l.length();i++) sum*=10;
	sum/=10;
	for(int i=0;i<=l.length()-1;i++){
		ret+=(l[i]-'0')*sum;
		sum/=10;
	}
	return ret;
}
int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i].prize);
		a[i].id=i;
	}
	string s;
	while(cin>>s){
		if(s=="EndOfCurrentCase") return 0;
		else if(s=="Report"){
			sort(a+1,a+n+1,cmp);
			printf("%d %d\n",a[1].id,a[2].id);
		}
		else{
			int id=zh(s),prize;
			scanf("%d",&prize);
			for(int i=1;i<=n;i++){
				if(a[i].id==id){
					a[i].money=max(prize-a[i].prize,0);
					a[i].prize=prize;
					break;
				}
			}

		}
	}
	return 0;
}
