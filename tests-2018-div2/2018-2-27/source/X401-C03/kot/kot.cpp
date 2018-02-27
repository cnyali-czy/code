#include<bits/stdc++.h>
using namespace std;

map<char,int>mp;

void init(){
	mp['1'] = 1;
	mp['2'] = 1;
	mp['3'] = 1;
	mp['4'] = 1;
	mp['5'] = 1;
	mp['6'] = 1;
	mp['7'] = 1;
	mp['8'] = 1;
	mp['9'] = 1;
	mp['`'] = 1;
	mp['-'] = 1;
	mp['='] = 1;
	mp['Q'] = 2;
	mp['W'] = 2;
	mp['E'] = 2;
	mp['R'] = 2;
	mp['T'] = 2;
	mp['Y'] = 2;
	mp['U'] = 2;
	mp['I'] = 2;
	mp['O'] = 2;
	mp['P'] = 2;
	mp['['] = 2;
	mp[']'] = 2;
	mp['\\'] = 2;
	mp['A'] = 3;
	mp['S'] = 3;
	mp['D'] = 3;
	mp['F'] = 3;
	mp['G'] = 3;
	mp['H'] = 3;
	mp['J'] = 3;
	mp['K'] = 3;
	mp['L'] = 3;
	mp[';'] = 3;
	mp['\''] = 3;
	mp['Z'] = 4;
	mp['X'] = 4;
	mp['C'] = 4;
	mp['V'] = 4;
	mp['B'] = 4;
	mp['N'] = 4;
	mp['M'] = 4;
	mp[','] = 4;
	mp['.'] = 4;
	mp['/'] = 4;
	mp[' '] = 5;
}

string m;

int main(){
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	init();
	
	getline(cin,m);
	for(int i = 0;i ^ m.size();i ++){
		cout << mp[ m[i] ];
	}
	return 0;
}
