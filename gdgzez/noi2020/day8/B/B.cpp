#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e6 + 10;
#define i64 long long
template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;
int a[maxn], vis[maxn];
i64 dp[maxn];

namespace shit
{
	int st[maxn << 1][22], lg[maxn << 1], N;
	void init()
	{
		N = m + m - 1;
		REP(i, 2, N) lg[i] = lg[i >> 1] + 1;
		REP(i, 0, N) st[i][0] = a[i % m] + i;
		DEP(i, N, 0)
			REP(j, 1, 21) if (i + (1 << j) - 1 <= N)
			st[i][j] = min(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
		else break;
	}
	int query(int l, int r)
	{
		int k = lg[r - l + 1];
		return min(st[l][k], st[r - (1 << k) + 1][k]);
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();
	REP(i, 0, m - 1) a[i] = read<int>();
	shit :: init();
	REP(i, 1, n)
	{
		dp[i] = 1ll << 62;
		int l = dp[i - 1] % m, r = l + m - 1;
		dp[i] = dp[i - 1] + shit :: query(l, r) - l;
		/*
		   REP(j, 0, m - 1)
		   chkmin(dp[i], dp[i - 1] + a[(dp[i - 1] + j) % m] + j);
		   */
		if (i == n) break;
		if (vis[dp[i] % m] && 1)
		{
			//	REP(j, 0, i) printf("%lld%c", dp[j], j == end_j ? '\n' : ' ');
			//	REP(j, 0, i) printf("%lld%c", dp[j] % m, j == end_j ? '\n' : ' ');
			int stp = i - vis[dp[i] % m];
			i64 delta = dp[i] - dp[vis[dp[i] % m]];
			i64 ans = dp[i];
			n -= i;
			ans += n / stp * delta;
			n %= stp;
			//			cerr << ans << ' '<< n << endl;
			ans += dp[n + 1] - dp[1];
			cout << ans << endl;
			//			cout << stp << ' '<< ans << endl;
			return 0;
		}
		vis[dp[i] % m] = i;
	}
	//	REP(i, 0, n) printf("%lld%c", dp[i], i == n ? '\n' : ' ');
	//	REP(i, 0, n) printf("%lld%c", dp[i] % m, i == n ? '\n' : ' ');
	cout << dp[n] << endl;
	return 0;
}
