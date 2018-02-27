#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>
#define REP(i,a,b) for(register int i=a;i<=b;++i)
#define DREP(i,a,b) for(register int i=a;i>=b;--i)
using namespace std;
void File(){
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
}
map<char,int>s;
const int maxn=5e5+10;
char a[maxn];
int len;
int main(){
	File();
	s['`']=1;
	s['1']=1;
	s['2']=1;
	s['3']=1;
	s['4']=1;
	s['5']=1;
	s['6']=1;
	s['7']=1;
	s['8']=1;
	s['9']=1;
	s['0']=1;
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
	s['\\']=2;
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
	int pos=1;
	while(scanf("%c",&a[pos])!=EOF)++pos;
	len=strlen(a+1);
	REP(i,1,len){
		if(a[i]==39)
			printf("%d",3);
		else if(s[a[i]])
			printf("%d",s[a[i]]);
	}
	return 0;
}
