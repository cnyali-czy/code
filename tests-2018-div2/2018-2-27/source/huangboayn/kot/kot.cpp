#include<bits/stdc++.h>
using namespace std;
const int maxn=500000+10;
char s[maxn];
map<char, int> c;
int main(){
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	int i,j,k,m,n;
	gets(s);
	c['`']=1;c['1']=1;c['2']=1;c['3']=1;c['4']=1;c['5']=1;c['6']=1;c['7']=1;c['8']=1;c['9']=1;c['-']=1;c['=']=1;
	c['Q']=2;c['W']=2;c['E']=2;c['R']=2;c['T']=2;c['Y']=2;c['U']=2;c['I']=2;c['O']=2;c['P']=2;c['[']=2;c[']']=2;c['|']=1;
	c['A']=3;c['S']=3;c['D']=3;c['F']=3;c['G']=3;c['H']=3;c['J']=3;c['K']=3;c['L']=3;c[';']=3;c[char(39)]=3;
	c['Z']=4;c['X']=4;c['C']=4;c['V']=4;c['B']=4;c['N']=4;c['M']=4;c[',']=4;c['.']=4;c['/']=4;
	c[' ']=5;
	for(register int i=0;i<strlen(s);i++)
	printf("%d",c[s[i]]);
	return 0;
}
