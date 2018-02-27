#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
using namespace std;
int a[10000010];
int main(){
	int i,j,k,m,n;
	char c;
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	scanf("%c",&c);
	a['`']=a['1']=a['2']=a['3']=a['4']=a['5']=a['6']=a['7']=a['8']=a['9']=a['0']=a['-']=a['=']=1;
	a['Q']=a['q']=a['W']=a['w']=a['E']=a['e']=a['R']=a['r']=a['T']=a['t']=a['Y']=a['y']=a['U']=a['u']=a['I']=a['i']=a['O']=a['o']=a['P']=a['p']=a['[']=a[']']=a[92]=2;
    a['A']=a['a']=a['S']=a['s']=a['D']=a['d']=a['F']=a['f']=a['G']=a['g']=a['H']=a['h']=a['J']=a['j']=a['K']=a['k']=a['L']=a['l']=a[';']=a[39]=3;
	a['Z']=a['z']=a['X']=a['x']=a['C']=a['c']=a['B']=a['b']=a['N']=a['n']=a['M']=a['m']=a[',']=a['.']=a['/']=4;
	a[' ']=5;	
	while(c!='\n'){
		printf("%d",a[c]);
		scanf("%c",&c);
	}
	puts("");
	return 0;
}/*
KOT-KTO-TOK KOD.
*/

