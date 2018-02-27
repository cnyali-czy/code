#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a ) 

char a[6][100];
char s[500010];
int sum[6];

int main()
{
	freopen("kot.in", "r", stdin);
	freopen("kot.out", "w", stdout);
	int len = 0;
	while ( scanf("%c", &s[len]) != EOF ) ++ len;
	REP(i, 0, len - 1)
	{
		if ( s[i] == '`' || (s[i] >= '0' && s[i] <= '9') || s[i] == '-' || s[i] == '=' ) 
			printf("1");
		else if ( s[i] == 'Q' || s[i] == 'W' || s[i] == 'E' || s[i] == 'R' || s[i] == 'T' || s[i] == 'Y' || s[i] == 'U' || s[i] == 'I' || s[i] == 'O' || s[i] == 'P' || s[i] == '[' || s[i] == ']' || s[i] == '\\')	
			printf("2");
		else if ( s[i] == 'A' || s[i] == 'S' || s[i] == 'D' || s[i] == 'F' || s[i] == 'G' || s[i] == 'H' || s[i] == 'J' || s[i] == 'K' || s[i] == 'L' || s[i] == ';' || s[i] == '\'')	
			printf("3");
		else if ( s[i] == 'Z' || s[i] == 'X' || s[i] == 'C' || s[i] == 'V' || s[i] == 'B' || s[i] == 'N' || s[i] == 'M' || s[i] == ',' || s[i] == '.' || s[i] == '/')
			printf("4");
		else if ( s[i] == ' ' )
			printf("5");
	}
	puts("");
	return 0;	
}
