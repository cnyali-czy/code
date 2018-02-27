#include<bits/stdc++.h>
using namespace std;
string str;
inline int val(int x){
	char ch=str[x];
	if(isdigit(ch)||ch=='`'||ch=='-'||ch=='=')return 1;
	if(ch=='Q'||ch=='W'||ch=='E'||ch=='R'||ch=='T'||ch=='Y'||ch=='U'||ch=='I'||ch=='O'||ch=='P'||ch=='['||ch==']'||ch==92)return 2;
	if(ch=='A'||ch=='S'||ch=='D'||ch=='F'||ch=='G'||ch=='H'||ch=='J'||ch=='K'||ch=='L'||ch==';'||ch==39)return 3;
	if(ch=='Z'||ch=='X'||ch=='C'||ch=='V'||ch=='B'||ch=='N'||ch=='M'||ch==','||ch=='.'||ch=='/')return 4;
	if(ch==' ')return 5;
	return 0;
}
int main(){
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	getline(cin,str);
	int len=str.length();
	for(register int i=0;i<len;++i)printf("%d",val(i));
	putchar('\n');
	return 0;
}
