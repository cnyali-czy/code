#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	int i,j,k,n,m,l;
	string s;
	getline(cin,s);
	n=s.length();
	for (i=0;i<n;i++){
		if(s[i]=='`' || s[i]>='0' && s[i]<='9' || s[i]=='-' || s[i]=='=')cout<<1;
		if(s[i]=='Q' || s[i]=='W' || s[i]=='E' || s[i]=='R' || s[i]=='T' || s[i]=='Y' || s[i]=='U' || s[i]=='I' || s[i]=='O' || s[i]=='P' || s[i]=='[' || s[i]==']' || s[i]=='/92')cout<<2;
		if(s[i]=='A' || s[i]=='S' || s[i]=='D' || s[i]=='F' || s[i]=='G' || s[i]=='H' || s[i]=='J' || s[i]=='K' || s[i]=='L' || s[i]==';' || s[i]=='\39')cout<<3;
		if(s[i]=='Z' || s[i]=='X' || s[i]=='C' || s[i]=='V' || s[i]=='B' || s[i]=='N' || s[i]=='M' || s[i]==',' || s[i]=='.' || s[i]=='/')cout<<4;
		if(s[i]==' ')cout<<5;
	}
	cout<<endl;
	return 0;
}

