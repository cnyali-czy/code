#include<bits/stdc++.h>
using namespace std;
string a;
int main(){
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	int i,j,k,l,m,n;
	getline(cin,a);
	n=a.length();
	for(i=0;i<n;i++){
	if(a[i]=='`' || a[i]=='1' || a[i]=='2' || a[i]=='3' || a[i]=='4' || a[i]=='5' || a[i]=='6' || a[i]=='7' || a[i]=='8' || a[i]=='9' || a[i]=='0' || a[i]=='-' || a[i]=='=')cout<<1;
	if(a[i]=='Q' || a[i]=='W' || a[i]=='E' || a[i]=='R' || a[i]=='T' || a[i]=='Y' || a[i]=='U' || a[i]=='I' || a[i]=='O' || a[i]=='P' || a[i]=='[' || a[i]==']')cout<<2;
	if(a[i]=='A' || a[i]=='S' || a[i]=='D' || a[i]=='F' || a[i]=='G' || a[i]=='H' || a[i]=='J' || a[i]=='K' || a[i]=='L' || a[i]==';')cout<<3;
	if(a[i]=='Z' || a[i]=='X' || a[i]=='C' || a[i]=='V' || a[i]=='B' || a[i]=='N' || a[i]=='M' || a[i]==',' || a[i]=='.' || a[i]=='/')cout<<4;
	if(a[i]==' ')cout<<5;
	if(a[i]==92)cout<<2;
	if(a[i]==39)cout<<3;
	}
	return 0;
}

