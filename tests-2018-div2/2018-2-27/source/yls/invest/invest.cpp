#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<set>
#define REP(i,a,b) for(register int i=a;i<=b;++i)
#define DREP(i,a,b) for(register int i=a;i>=b;--i)
using namespace std;
void File(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
}
const int maxn=1e5+10;
struct node{
	int p,va,id;
	bool operator < (const node & t) const {
		if(va!=t.va)return va>t.va;
		else return id<t.id;
	}
}b[maxn];
set<node>s;
int n;
int main(){
	File();
	scanf("%d",&n);
	REP(i,1,n){
		int tmp;
		scanf("%d",&tmp);
		b[i].p=tmp;b[i].va=0;b[i].id=i;
		s.insert(b[i]);
	}
	while(1){
		char c[20];
		int num=0,d;
		scanf("%s",c+1);
		if(isdigit(c[1])){
			int len=strlen(c+1);
			REP(i,1,len)num=(num<<1)+(num<<3)+(c[i]^'0');
			scanf("%d",&d);
			set<node>::iterator it=lower_bound(s.begin(),s.end(),b[num]);
			s.erase(it);
			b[num].va=d-b[num].p;
			b[num].p=d;
			s.insert(b[num]);
		}
		else{
			if(!strcmp("EndOfCurrentCase",c+1))break;
			set<node>::iterator it=s.begin();
			printf("%d ",it->id);
			++it;
			printf("%d\n",it->id);
		}
	}
	return 0;
}
