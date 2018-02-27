#include<bits/stdc++.h>
using namespace std;
inline void read(int &x)
{
	x=0;
	static int p;p=1;
	static char c;c=getchar();
	while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
	while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
	x*=p;
}
map<char,int>ma;
string s;
int main()
{
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	ma['`']=ma['-']=ma['=']=1;
	for(int i=0;i<=9;i++)ma[i+48]=1;
	ma['Q']=ma['W']=ma['E']=ma['R']=ma['T']=ma['Y']=ma['U']=ma['I']=ma['O']=ma['P']=ma['[']=ma[']']=ma['\\']=2;
	ma['A']=ma['S']=ma['D']=ma['F']=ma['G']=ma['H']=ma['J']=ma['K']=ma['L']=ma[';']=ma[39]=3;
	ma['Z']=ma['X']=ma['C']=ma['V']=ma['B']=ma['N']=ma['M']=ma[',']=ma['.']=ma['/']=4;
	ma[' ']=5;
	char c=getchar();
	while(ma.count(c)){printf("%d",ma[c]);c=getchar();}
	return 0;
}
