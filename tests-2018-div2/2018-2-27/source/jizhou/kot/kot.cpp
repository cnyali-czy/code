#include<bits/stdc++.h>
using namespace std;
const int maxn = 500000 + 10;

char s[maxn];
map<char, short> a;

int main(){
	freopen("kot.in", "r", stdin);
	freopen("kot.out", "w", stdout);
	a['`'] = 1, a['1'] = 1, a['2'] = 1, a['3'] = 1, a['4'] = 1, a['5'] = 1, a['6'] = 1, a['7'] = 1, a['8'] = 1, a['9'] = 1, a['-'] = 1, a['='] = 1;
	a['Q'] = 2, a['W'] = 2, a['E'] = 2, a['R'] = 2, a['T'] = 2, a['Y'] = 2, a['U'] = 2, a['I'] = 2, a['O'] = 2, a['P'] = 2, a['['] = 2, a[']'] = 2, a['\\'] = 2;
	a['A'] = 3, a['S'] = 3, a['D'] = 3, a['F'] = 3, a['G'] = 3, a['H'] = 3, a['J'] = 3, a['K'] = 3, a['L'] = 3, a[';'] = 3, a['\''] = 3;
	a['Z'] = 4, a['X'] = 4, a['C'] = 4, a['V'] = 4, a['B'] = 4, a['N'] = 4, a['M'] = 4, a[','] = 4, a['.'] = 4, a['/'] = 4;
	a[' '] = 5;
	char c;
	while(scanf("%c", &c) && c != EOF){
		if(c >= 'a' && c <= 'z') c -= 'a' - 'A';
		if(!a[c]) continue;
		printf("%d", a[c]);
	}
	return 0;
}
