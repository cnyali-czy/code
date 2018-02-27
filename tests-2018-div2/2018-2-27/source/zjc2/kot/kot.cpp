#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<cstring>
const int maxn=1000000+10;
using namespace std;
char s;
int main(){
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	int i,j,k,m,n;
	while(scanf("%c" ,&s)!=EOF){
		if((s>='0' && s<='9') || s=='`' || s=='-' || s=='=')cout<<1;
		else if(s=='Q' || s=='W' || s=='E' || s=='R' || s=='T' || s=='Y' || s=='U' || s=='I' || s=='O' || s=='P' || s=='[' || s==']' || s==92)cout<<2;
		else if(s=='A' || s=='S' || s=='D' || s=='F' || s=='G' || s=='H' || s=='J' || s=='K' || s=='L' || s==';' || s==39)cout<<3;
		else if(s=='Z' || s=='X' || s=='C' || s=='V' || s=='B' || s=='N' || s=='M' || s==',' || s=='.' || s=='/')cout<<4;
		else if(s==' ')cout<<5;
	}
	return 0;
}
