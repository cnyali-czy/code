#include<bits/stdc++.h>
using namespace std;
int s[300];
void init()
{
	s['`']=1;
	for(register int i='0';i<='9';i++)
		s[i]=1;
	s['-']=1;
	s['=']=1;
	s['Q']=2;
	s['W']=2;
	s['E']=2;
	s['R']=2;
	s['T']=2;
	s['Y']=2;
	s['U']=2;
	s['I']=2;
	s['O']=2;
	s['P']=2;
	s['[']=2;
	s[']']=2;
	s[92]=2;
	s['A']=3;
	s['S']=3;
	s['D']=3;
	s['F']=3;
	s['G']=3;
	s['H']=3;
	s['J']=3;
	s['K']=3;
	s['L']=3;
	s[';']=3;
	s[39]=3;
	s['Z']=4;
	s['X']=4;
	s['C']=4;
	s['V']=4;
	s['B']=4;
	s['N']=4;
	s['M']=4;
	s[',']=4;
	s['.']=4;
	s['/']=4;
	s[' ']=5;
}
int main()
{
	char c;
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	init();
	while(!feof(stdin))
	{
		c=getchar();
		if(c>='a' && c<='z')
			c-=32;
		if(s[c])
			printf("%d",s[c]);
	}
	return 0;
}
