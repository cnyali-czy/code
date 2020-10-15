#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 5000 + 10;
const i64 inf = 1e15;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

inline bool chkmax(i64 &x, i64 y)
{
	if (x <= y)
	{
		x = y;
		return 1;
	}
	return 0;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn];
i64 s[maxn], dp[maxn][maxn], g[maxn], f[maxn];
i64 sum(int l, int r) {return s[r] - s[l - 1];}

void solve(int i)
{
	REP(j, i, n) f[j] = -inf;
	int Max = 1, Min = 1;
	REP(k, 1, i - 1)
	{
		if (g[Max] - s[Max] < g[k] - s[k]) Max = k;
		if (g[Min] - s[Min] > g[k] - s[k]) Min = k;
	}
	
//	REP(k, 1, i - 1)
		REP(j, i, n)
		{
			i64 sj = s[j], si = s[i - 1], sk, k;
			if (sj > si) k = Max;
			else k = Min;
			sk = s[k - 1];
			chkmax(f[j], g[k] + (sj - si) * (si - sk));
//			chkmax(f[j], g[k] + (s[j] - s[i - 1]) * (s[i - 1] - s[k - 1]));
//			chkmax(f[j], g[k] + sum(k, i - 1) * sum(i, j));
		}
}

int main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();
	REP(i, 1, n) s[i] = s[i - 1] + (a[i] = read<int>());
	i64 ans = 0;
	REP(i, 2, n)
	{
		REP(j, 1, i - 1) g[j] = dp[j][i - 1];
		solve(i);
		REP(j, i, n) dp[i][j] = f[j];
		chkmax(ans, f[n]);
	}
	cout << ans << endl;
	return 0;
}
