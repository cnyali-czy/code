#include<bits/stdc++.h>
using namespace std;
int len,t;
char c;
int f[500]={0};
int main(){
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	f[96]=f[49]=f[50]=f[51]=f[52]=f[53]=f[54]=f[55]=f[56]=f[57]=f[48]=f[45]=f[61]=1;
	f[81]=f[87]=f[69]=f[82]=f[84]=f[89]=f[85]=f[73]=f[79]=f[80]=f[91]=f[92]=f[93]=2;
	f[65]=f[83]=f[68]=f[70]=f[71]=f[72]=f[74]=f[75]=f[76]=f[59]=f[39]=3;
	f[90]=f[88]=f[67]=f[86]=f[66]=f[78]=f[77]=f[44]=f[46]=f[47]=4;
	f[32]=5;
	while(1){
		scanf("%c",&c);
		if(c=='\n') break;
		t=c;
		cout<<f[t];
	}
	return 0;
}
