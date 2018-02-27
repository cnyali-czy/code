#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("invest.in","r",stdin);
	freopen("invest.out","w",stdout);
	int i,j,k,n,m,l,p[100010],py[100010];
	cin>>n;
	for (i=1;i<=n;i++)scanf("%d",&p[i]);
	while(1){
		string s;
		cin>>s;
		if(s[0]=='E')break;
		else if(s[0]>='0' && s[0]<='9'){
			int num=s[0]-'0',pp;
			m=1;
			while(s[m]>='0' && s[m]<='9')
				num=num*10+s[m]-'0',m++;
			scanf("%d",&pp);
			py[num]=pp-p[num];
			p[num]=pp;
		}else if(s[0]=='R'){
			int ma=-2147483647,ma1=-2147483647,f,f1;
			for (i=1;i<=n;i++)if(py[i]>ma)ma=py[i],f=i;
			for (i=1;i<=n;i++)if(py[i]<ma && py[i]>ma1)ma1=py[i],f1=i;
			cout<<f<<' '<<f1<<endl; 
		}
	}
	return 0;
}

