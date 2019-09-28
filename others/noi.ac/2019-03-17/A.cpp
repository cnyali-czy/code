#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, k;

int dp[22][256][2520];
int digit[22];

int get(int pos, int s)
{
	if (pos < 2) return s;
	else return s | (1 << pos - 2);
}

int dfs(int l, int s, int sum, bool flag)
{
	if (!l)
	{
		REP(i, 0, 7)
			if (s & (1 << i) && sum % (i + 2)) return 0;
		return 1;
	}
	if (!flag && ~dp[l][s][sum]) return dp[l][s][sum];
	int pos = flag ? digit[l] : 9;
	int ret = 0;
	REP(i, 0, pos) ret += dfs(l - 1, get(i, s), (sum * 10ll + i) % 2520, flag && (i == pos));
	if (!flag) dp[l][s][sum] = ret;
	return ret;
}
int f(int x)
{
	int pos = 0;
	while (x)
	{
		digit[++pos] = x % 10;
		x /= 10;
	}
	return dfs(pos, 0, 0, 1);
}

signed main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	memset(dp, -1, sizeof(dp));
	int T = read<int>();
	while (T --> 0)
	{
		int l(read<int>()), r(read<int>());
		printf("%lld\n", f(r) - f(l-1));
	}
	return 0;
}
