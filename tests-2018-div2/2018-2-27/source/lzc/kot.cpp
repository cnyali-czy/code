#include<bits/stdc++.h>
using namespace std;
map<char,int>a;
int main( ){
	int k,n,m;
	char c;
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	a['`']=1;a['-']=1;a['=']=1;
	for(int i=0;i<=9;i++)
		a[i+'0']=1;
	a['Q']=a['W']=a['E']=a['R']=a['T']=a['Y']=a['U']=a['I']=a['O']=a['P']=a['[']=a[']']=2;
	a['A']=a['S']=a['D']=a['F']=a['G']=a['H']=a['J']=a['K']=a['L']=a[';']=3;
	a['Z']=a['X']=a['C']=a['V']=a['B']=a['N']=a['M']=a[',']=a['.']=a['/']=4;
	a[' ']=5;
	while(scanf("%c",&c)!=EOF){
		if(a[c]!=0)printf("%d",a[c]);
		else if(c==92)printf("2");
		else if(c==39)printf("3");
	}
	return 0;
}

