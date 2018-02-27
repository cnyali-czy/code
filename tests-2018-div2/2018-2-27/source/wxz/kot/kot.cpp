#include<bits/stdc++.h>
using namespace std;
map<char,int>map1;
void init(){
	map1['1']=1;map1['2']=1;map1['3']=1;map1['4']=1;map1['5']=1;map1['6']=1;map1['7']=1;map1['8']=1;map1['9']=1;map1['`']=1;map1['-']=1;map1['=']=1;
	map1['Q']=2;
	map1['W']=2;
	map1['E']=2;
	map1['R']=2;
	map1['T']=2;
	map1['Y']=2;
	map1['U']=2;
	map1['I']=2;
	map1['O']=2;
	map1['P']=2;
	map1['[']=2;
	map1[']']=2;
	map1['\\']=2;
	map1['A']=3;
	map1['S']=3;
	map1['D']=3;
	map1['F']=3;
	map1['G']=3;
	map1['H']=3;
	map1['J']=3;
	map1['K']=3;
	map1['L']=3;
	map1[';']=3;
	map1['\'']=3;
	map1['Z']=4;
	map1['X']=4;
	map1['C']=4;
	map1['V']=4;
	map1['B']=4;
	map1['N']=4;
	map1['M']=4;
	map1[',']=4;
	map1['.']=4;
	map1['/']=4;
	map1[' ']=5;
}
string m;
int main(){
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	init();
	getline(cin,m);
	for(int i=0;i^m.size();i++)cout<<map1[m[i]];
	return 0;
}
