#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
const int N=500000+10;
int main(){
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	int i,j,k,m,n;
	char c;
	while(scanf("%c",&c)!=EOF){
		if((c>='0' && c<='9') || c=='`' || c=='-' || c=='=')cout<<1;
		else if(c=='Q' || c=='W' || c=='E' || c=='R' || c=='T' || c=='Y' || c=='U' || c=='I' || c=='O' || c=='P' || c=='[' || c==']' || c==92)cout<<2;
		else if(c=='A' || c=='S' || c=='D' || c=='F' || c=='G' || c=='H' || c=='J' || c=='K' || c=='L' || c==';' || c==39)cout<<3;
		else if(c=='Z' || c=='X' || c=='C' || c=='V' || c=='B' || c=='N' || c=='M' || c==',' || c=='.' || c=='/')cout<<4;
		else if(c==' ')cout<<5;
	}
	return 0;
}
