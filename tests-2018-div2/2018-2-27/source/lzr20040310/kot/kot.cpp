#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
int main(){
	string str;
	freopen("kot.in","r",stdin);
	freopen("kot.out","w",stdout);
	getline(cin,str);
	for(int i=0;i<str.size();i++)
		switch(str[i]){
			case '`':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '0':
			case '-':
			case '=':
				putchar('1');
				break;
			case 'Q':
			case 'W':
			case 'E':
			case 'R':
			case 'T':
			case 'Y':
			case 'U':
			case 'I':
			case 'O':
			case 'P':
			case '[':
			case ']':
			case '\\':
				putchar('2');
				break;
			case 'A':
			case 'S':
			case 'D':
			case 'F':
			case 'G':
			case 'H':
			case 'J':
			case 'K':
			case 'L':
			case ';':
			case '\'':
				putchar('3');
				break;
			case 'Z':
			case 'X':
			case 'C':
			case 'V':
			case 'B':
			case 'N':
			case 'M':
			case ',':
			case '.':
			case '/':
				putchar('4');
				break;
			case ' ':
				putchar('5');
		}
	return 0;
}
