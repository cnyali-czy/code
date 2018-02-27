#include<bits/stdc++.h>
using namespace std;
inline void w(char c){
	if(c=='-'||c=='='||('0'<=c&&c<='9')||c=='`')
		cout<<1;
	if(c=='Q'||c=='W'||c=='E'||c=='R'||c=='T'||c=='Y'||c=='U'||c=='I'||c=='O'||c=='P'||c=='['||c==']'||c=='\\')
		cout<<2;
	if(c=='A'||c=='S'||c=='D'||c=='F'||c=='G'||c=='H'||c=='J'||c=='K'||c=='L'||c==';'||c=='\'')
		cout<<3;
	if(c=='Z'||c=='X'||c=='C'||c=='V'||c=='B'||c=='N'||c=='M'||c==','||c=='.'||c=='/')
		cout<<4;
	if(c==' ')cout<<5;
}
char a[500000+10];
int i=0,j;
int main(){
	ios::sync_with_stdio(0);
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	while(scanf("%c",&a[i])!=EOF)i++;
	for(j=0;j<i;j++){
		w(a[j]);
	}
	return 0;
}
