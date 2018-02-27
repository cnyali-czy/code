#include<algorithm>
#include<iostream>
#include<cstring>
#define GET gets
#include<cstdio>
#include<cmath>
using namespace std;
char C[500005];
int main( ){
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	GET(C);
	for(int I=0;I<strlen(C);I++){
		if(C[I]=='`'||C[I]=='1'||C[I]=='2'||C[I]=='3'||C[I]=='4'||C[I]=='5'||C[I]=='6'||C[I]=='7'||C[I]=='8'||C[I]=='9'||C[I]=='0'||C[I]=='-'||C[I]=='=')cout<<"1";
		else if(C[I]=='A'||C[I]=='S'||C[I]=='D'||C[I]=='F'||C[I]=='G'||C[I]=='H'||C[I]=='J'||C[I]=='K'||C[I]=='L'||C[I]==';'||C[I]==char(39))cout<<"3";
		else if(C[I]=='Z'||C[I]=='X'||C[I]=='C'||C[I]=='V'||C[I]=='B'||C[I]=='N'||C[I]=='M'||C[I]==','||C[I]=='.'||C[I]=='/')cout<<"4";
		else if(C[I]==' ')cout<<"5";
		else cout<<"2";
	}
	return 0;
}
