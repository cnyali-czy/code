#include<bits/stdc++.h>
using namespace std;
int a[50010];
int main(){
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	int i=1,j,k,m,n;
	char c;
	while(scanf("%c",&c)){
		if(c=='\n')
			break;
		else{
			if(c>='a' && c<='z')
				c=char(int(c-32));
			if(c=='`' || (c>='0' && c<='9') || c=='-' || c=='=')
				a[i]=1;
			if(c=='Q' || c=='W' || c=='E' || c=='R' || c=='T' || c=='Y' || c=='U' || c=='I' || c=='O' || c=='P' || c=='[' || c==']' || int(c)==92)   
				a[i]=2;
			if(c=='A' || c=='S' || c=='D' || c=='F' || c=='G' || c=='H' || c=='J' || c=='K' || c=='L' || c==';' || int(c)==39)
				a[i]=3;
			if(c=='Z' || c=='X' || c=='C' || c=='V' || c=='B' || c=='N' || c=='M' || c==',' || c=='.' || c=='/')
				a[i]=4;
			if(c==' ')
				a[i]=5;
			i++;
		}
	}
	for(j=1;j<=i-1;j++)
		cout<<a[j];
	return 0;
}
