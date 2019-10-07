#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <iostream>
#include <cstdio>
#define int long long 

using namespace std;
const int maxn = 500000 + 10;

int n, a[maxn], dp[maxn][2];

int bit[maxn];
int sta[maxn][2], p1, p2;

namespace cheat
{
	inline void work()
	{
		register int last1, last2, res(0), ans(0);
		last1 = last2 = 0;
		REP(i, 1, n)
			if (a[i] >= i)
			{
				chkmax(last1, a[i]);
				res += last1;
			}
			else
			{
				chkmax(last2, a[i]);
				res += last2;
			}
		last1 = last2 = 0;
		REP(i, 1, n)
			if (a[i] >= last1)
			{
				chkmax(last1, a[i]);
				ans += last1;
			}
			else
			{
				chkmax(last2, a[i]);
				ans += last2;
			}
		cout << min(res, ans) << endl;
	}
}
namespace bf
{
	void work()
	{
		REP(i, 1, n) bit[i] = bit[i >> 1] + (i & 1);
		const int lim = (1 << n) - 1;
		int ans(1e9);
		REP(S, 0, lim)
		{
			p1 = p2 = 0;
			REP(i, 1, n)
				if (S & (1 << i - 1)) sta[++p1][0] = a[i];
				else sta[++p2][1] = a[i];
			REP(i, 1, p1) chkmax(sta[i][0], sta[i-1][0]);
			REP(i, 1, p2) chkmax(sta[i][1], sta[i-1][1]);
			int res(0);
			REP(i, 1, p1) res += sta[i][0];
			REP(i, 1, p2) res += sta[i][1];
			chkmin(ans, res);
		}
		cout << ans << endl;
	}
}


signed main()
{
#ifdef CraZYali
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%lld", a + i);
	if (n <= 20) bf::work();
	else cheat::work();
	return 0;
}
