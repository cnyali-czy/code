#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )

const int maxn = 100010;

int n, a[maxn], f[maxn], Max1, Max2, K1, K2;
char s[maxn];

int main()
{
	freopen("invest.in", "r", stdin);
	freopen("invest.out", "w", stdout);
	scanf("%d", &n);
	REP(i, 1, n) scanf("%d", &a[i]);
	while ( scanf("%s", s) )
	{
		getchar();
		if ( s[0] == 'E' ) break ;
		if ( s[0] == 'R' ) 
		{
			printf("%d %d\n", K1, K2);
			continue ;
		}
		int x = 0, p = 0, y = 0;
		while ( s[p] >= '0' && s[p] <= '9' ) 
		{
			x = x * 10 + s[p] - '0';
			++ p;
		}
		scanf("%d", &y);
		a[x] = f[x]; f[x] = y;
		if ( f[x] - a[x] <= Max2 && x != K2 && x != K1 ) continue ;
		Max1 = 0; Max2 = 0;
		REP(i, 1, n)
		{
			if ( f[i] - a[i] > Max1 ) 
			{
				Max2 = Max1;
				Max1 = f[i] - a[i];
				K2 = K1;
				K1 = i;
			}
			else if ( f[i] - a[i] > Max2 )
			{
				K2 = i;
				Max2 = f[i] - a[i];
			}
		}
	}
	return 0;	
}
