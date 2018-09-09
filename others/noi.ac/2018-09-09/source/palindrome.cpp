#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e6 + 10;

int m, n, k;
char S[maxn];

/*
int dfs(int s, int t)
{
	if (s > t) return 0;
	else if (s == t) return 1;
	else if (s == t - 1) return dp[s][t] = 1 + (S[s] == S[t]);
	else if (dp[s][t] != 1) return dp[s][t];
	else
	{
		register int l = s, r = t;
		while (l <= r)
		{
			bool flag = 1;
			REP(i, s, l)
				if (S[i] ^ S[r + i - s])
				{
					flag = 0;
					break;
				}
			l++;r--;
			if (!flag) continue;
			else chkmax(dp[s][t], 2 + dfs(l, r));
		}
		return dp[s][t];
	}
}
*/

unsigned long long Hash[maxn][2];
unsigned long long base[] = {29, 31};
unsigned long long MOD[] = {(unsigned long long)1e9 + 9, (unsigned long long)1e9 + 7};

unsigned long long sh[maxn][2];

inline unsigned long long calc1(int l, int r)
{
	return (sh[r][0] - sh[l-1][0] * Hash[r - l + 1][0] % MOD[0] + MOD[0]) % MOD[0];
}
inline unsigned long long calc2(int l, int r)
{
	return (sh[r][1] - sh[l-1][1] * Hash[r - l + 1][1] % MOD[1] + MOD[1]) % MOD[1];
}
inline bool chk(int l, int r, int x, int y)
{
	return calc1(l, r) == calc1(x, y) && calc2(l, r) == calc2(x, y);
}

int dfs(int x, int y)
{
	if (x > y) return 0;
	register int l = x, r = y - (l - x);
	while (l < r)
	{
		if (chk(x, l, r, y)) return dfs(l + 1, r - 1) + 2;
		l++;r--;
	}
	return 1;
}

int main()
{
#ifdef CraZYali
	freopen("palindrome.in", "r", stdin);
	freopen("palindrome.out", "w", stdout);
#endif
	Hash[0][0] = Hash[0][1] = 1;
	REP(i, 1, 1000000)
		REP(j, 0, 1)
			Hash[i][j] = Hash[i-1][j] * base[j] % MOD[j];
	cin >> m;
	while (m --> 0)
	{
		scanf("%s", S + 1);
		n = strlen(S + 1);
		REP(i, 1, n)
			REP(j, 0, 1)
				sh[i][j] = (sh[i-1][j] * base[j] + S[i] - 'a') % MOD[j];
		printf("%d\n", dfs(1, n));
	}	
	return 0;
}
