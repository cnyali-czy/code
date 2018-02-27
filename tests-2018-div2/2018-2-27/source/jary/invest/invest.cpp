#include<bits/stdc++.h>
using namespace std;
int n,len,sum1,sum2,f1,f2,t1,t2;
char s[100],s1[100]="EndOfCurrentCase",s2[100]="Report";
struct node{
	int money,lucre;
}num[200000];
int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	scanf("%d",&n);
	for(register int i=1;i<=n;i++){
		scanf("%d",&num[i].money);
		num[i].lucre=0;
	}
	while(1){
		cin>>s;
		t1=t2=0;
		if(strcmp(s,s1)==0) break;
		if(strcmp(s,s2)==0){
			sum1=0; sum2=0; f1=0; f2=0;
			for(register int i=1;i<=n;i++){
				if(num[i].lucre>sum1){
					sum1=num[i].lucre; f1=i; continue;
				}
				if(num[i].lucre>sum2){
					sum2=num[i].lucre; f2=i; continue;
				}
			}
			cout<<f1<<" "<<f2<<endl;
		}
		else{
			len=strlen(s);
			for(register int i=0;i<len;i++) t1=t1*10+s[i]-'0';
			cin>>t2;
			num[t1].lucre=t2-num[t1].money;
			num[t1].money=t2;
		}
	}
	return 0;
}

