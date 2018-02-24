#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2010, MOD = 1000000007 ;

int m, n, k;
char s[maxn];

int ans = 0;

inline bool judge()
{
	REP(i, 1, n - 1)
	{
		REP(X, i, i + k - 1) if (X > n || s[X] ^ 'B') goto noway;
		REP(j, i + 1, n)
		{
			REP(X, j, j + k - 1) if (X > n || s[X] ^ 'W') goto noway1;
			return 1;
noway1:;
		}
noway:;
	}
	return 0;
}

inline void dfs(int x)
{
	if (x == n + 1)
	{
		if (judge()) ans = (ans + 1) % MOD;
		return;
	}
	if (s[x] ^ 'X') {dfs(x + 1);return;}
	s[x] = 'W';
	dfs(x + 1);
	s[x] = 'B';
	dfs(x + 1);
	s[x] = 'X';
}

int main()
{
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	scanf("%d %d\n%s", &n, &k, s + 1);
	dfs(0);
	cout << ans % MOD;
	return 0;
}
