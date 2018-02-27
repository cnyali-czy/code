#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )

const int maxn = 110;

int n, m, a[maxn][2], f[maxn], ans[maxn];
char s[maxn][30], c[maxn];
bool flag, vis[maxn];

void dfs(int x, int Max)
{
	if ( flag == true ) return ;
	if ( x == Max + 1 )
	{
		flag = true;
		REP(i, 1, Max) ans[i] = f[i];
		return ;
	}
	REP(i, 1, m)
	{
		if ( x == 1 ) 
		{
			f[x] = i;
			vis[i] = true;
			dfs(x + 1, Max);
			vis[i] = false;
			continue ;
		}
		if ( a[f[x - 1]][1] == a[i][0] && vis[i] == false ) 
		{
			f[x] = i;
			vis[i] = true;
			dfs(x + 1, Max);
			vis[i] = false;
		}
	}
}

int main()
{
	freopen("language.in", "r", stdin);
	freopen("language.out", "w", stdout);
	scanf("%d%d", &n, &m);
	REP(i, 1, n) 
	{
		getchar();
		scanf("%s", s[i]);
	}
	REP(i, 1, m)
	{
		getchar();
		scanf("%s", c);
		REP(j, 1, n)
		{
			if ( strcmp(c, s[j]) == 0 ) 
			{
				a[i][0] = j;
				break ;
			}
		}
		getchar();
		scanf("%s", c);
		REP(j, 1, n)
		{
			if ( strcmp(c, s[j]) == 0 ) 
			{
				a[i][1] = j;
				break ;
			}
		}
	}
	REP(i, 1, m + 1)
	{
		mem(vis);
		flag = false;
		dfs(1, i);
		if ( flag == false ) 
		{
			printf("%d\n", i);
			REP(j, 1, i - 1) printf("%s ", s[a[ans[j]][0]]);
			printf("%s\n", s[a[ans[i - 1]][1]]);
			return 0;
		}
	}
	printf("%d\n", m + 1);
	REP(j, 1, m) printf("%s ", s[a[ans[j]][0]]);
	printf("%s\n", s[a[ans[m]][1]]);
	return 0;
}

