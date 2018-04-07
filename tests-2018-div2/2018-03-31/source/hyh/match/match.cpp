#include<bits/stdc++.h>
using namespace std;
string s1,s2,s3,s4;
int main( ){
	int k,n,m,l1,l2;
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	scanf("%d",&n);
	for(register int z=1;z<=n;z++){
		int flag=1;
		cin>>s1>>s2;
		l1=s1.size( );l2=s2.size( );
		int i=0;
		if(s2[0]=='*'){
			s3=s1.substr(1,l1-1);
			s1=s3;
			i++;
			l1--;
		}
		if(s2[l2-1]=='*'){
			s3=s1.substr(0,l1-1);
			s1=s3;
			l1--;
		}
		else{
			s2+='*';l2++;
		}
		s4="";
		while(i<l2){
			if(s2[i]!='*')s4+=s2[i];
			else{
				k=s1.find(s4);
				if(k==-1){
					flag=0;
					break;
				}
				
				m=k+s4.size( );
				s3=s1.substr(m,l1-m);
				if(s3.size( )!=0){
					s1=s3.substr(1,s3.size( )-1);
				}
				else s1=s3;
				l1=s1.size( );
				s4="";
			}
			i++;
		}
		if(flag==0)printf("Impossible\n");
		else printf("Maybe\n");
	}
	return 0;
}

