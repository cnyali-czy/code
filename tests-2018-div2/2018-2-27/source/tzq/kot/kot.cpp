#include<bits/stdc++.h>
//const int maxn=500000+10; 
using namespace std;
//char ch[maxn];
string t;
int n,m;
int main(){
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	int i;
	getline(cin,t);
	//int n=sizeof(t);
	for(i=0;i<t.length();i++){
		if(t[i]=='`' || (t[i]>='0' && t[i]<='9') || t[i]=='-' || t[i]=='=')
		cout<<1;
		if(t[i]=='Q' || t[i]=='W' || t[i]=='E' || t[i]=='R' || t[i]=='T' || t[i]=='Y' || t[i]=='U' || t[i]=='I' || t[i]=='O' || t[i]=='P' || t[i]=='[' || t[i]==']' || t[i]==92)
		cout<<2;
		if(t[i]=='A' || t[i]=='S' || t[i]=='D' || t[i]=='F' || t[i]=='G' || t[i]=='H' || t[i]=='J' || t[i]=='K' || t[i]=='L' || t[i]==';' || t[i]==39)	
		cout<<3;
		if(t[i]=='Z' || t[i]=='X' || t[i]=='C' || t[i]=='V' || t[i]=='B' || t[i]=='N' || t[i]=='M' || t[i]==',' || t[i]=='.' || t[i]=='/')
		cout<<4;
		if(t[i]==' ')cout<<5;
	}
	return 0;
}
