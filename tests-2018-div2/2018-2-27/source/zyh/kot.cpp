#include<bits/stdc++.h>
using namespace std;
int main(){
	int i,j,k,n,m;
	char c;
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	c=getchar();
	while(c!=EOF){
		if((c>='0'&&c<='9')||c=='`'||c=='-'||c=='=')cout<<'1';
		if(c=='Q'||c=='W'||c=='E'||c=='R'||c=='T'||c=='Y'||c=='U'||c=='I'||c=='O'||c=='P'||c=='['||c==']'||c=='\\')cout<<2;
		if(c=='A'||c=='S'||c=='D'||c=='F'||c=='G'||c=='H'||c=='J'||c=='K'||c=='L'||c==';'||c=='\'')cout<<3;
		if(c=='Z'||c=='X'||c=='C'||c=='V'||c=='B'||c=='N'||c=='M'||c==','||c=='.'||c=='/')cout<<4;
		if(c==' ')cout<<5;
		c=getchar();
	}
	return 0;
}

