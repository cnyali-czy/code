#include<iostream>
#include<string>
#include<set>
#include<cstdio>
using namespace std;
struct stock{
	int id,last,now;
	void read(){
		scanf("%d",&last);
		now=last;
	}
	int receipts()const{
		return now-last;
	}
	void set(int money){
		last=now;
		now=money;
	}
};
inline bool operator<(const stock&,const stock&);
int main(){
	int n;
	set<stock> s;
	stock *sto;
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	scanf("%d",&n);
	sto=new stock[n+1];
	for(int i=1;i<=n;i++){
		sto[i].id=i;
		sto[i].read();
		s.insert(sto[i]);
	}
	while(1){
		string str;
		while(str.empty())
			getline(cin,str);
		if(str=="Report"){
			set<stock>::iterator i=s.begin(),j=i;
			j++;
			printf("%d %d\n",i->id,j->id);
		}
		else if(str=="EndOfCurrentCase")
			break;
		else{
			int id,money;
			sscanf(str.c_str(),"%d %d",&id,&money);
			s.erase(sto[id]);
			sto[id].set(money);
			s.insert(sto[id]);
		}
	}
	delete[] sto;
	return 0;
}
inline bool operator<(const stock &x,const stock &y){
	if(x.receipts()==y.receipts())
		return x.id<y.id;
	return x.receipts()>y.receipts();
}
