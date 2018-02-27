#include<bits/stdc++.h>
using namespace std;
int main()
{
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	char a;
	while(scanf("%c",&a))
	{
		if(a=='\n')
			return 0;
		if(a>='a'&&a<='z')
			a=char(a-32);
		if(a=='`'||(a>='0'&&a<='9')||a=='-'||a=='=')
			cout<<1;
		else if(a=='Q'||a=='W'||a=='E'||a=='R'||a=='T'||a=='Y'||a=='U'||a=='I'||a=='O'||a=='P'||a=='['||a==']'||a==92)
			cout<<2;
		else if(a=='A'||a=='S'||a=='D'||a=='F'||a=='G'||a=='H'||a=='J'||a=='K'||a=='L'||a==';'||a==39)
			cout<<3;
		else if(a=='Z'||a=='X'||a=='C'||a=='V'||a=='B'||a=='N'||a=='M'||a==','||a=='.'||a=='/')
			cout<<4;
		else
			cout<<5;
	}
	return 0;
}

