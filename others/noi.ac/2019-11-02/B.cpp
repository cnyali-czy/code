#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : b)
#define chkmin(a, b) (a > (b) ? a = (b) : b)

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 100 + 5;

template <typename T>
inline T read()
{
	register char c(getchar());
	register T ans(0), flag(1);
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

int n, a[maxn];
bool dp[maxn][300000 + 10];
long long ans, m;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> m;
	REP(i, 1, n)
	{
		long long x = read<long long>();
		REP(j, 0, 60)
			if (x & (1ll << j)) a[j]++;
	}
	dp[0][0] = 1;
	REP(i, 0, 59)
	{
		int p = !!(m & (1ll << i));
		REP(j, 0, n)
			if (dp[i][j])
			{
				if ((j + a[i]) % 2 == p)	dp[i + 1][j + a[i] >> 1] = 1;
				if ((j - a[i] + n) % 2 == p)dp[i + 1][j + n - a[i] >> 1] = 1; 
			}
	}
	if (!dp[60][0]) return 0 * puts("-1");

	long long tmp = 0;
	DREP(i, 59, 0)
	{
		tmp = (tmp << 1) + !!(m & (1ll << i));
		ans <<= 1;
		if (tmp >= a[i] && dp[i][tmp - a[i]]) tmp -= a[i];
		else
		{
			ans++;
			tmp -= n - a[i];
		}
	}
	cout << ans << endl;
	return 0;
}
