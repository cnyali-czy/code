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
const int maxn = 50 + 5, maxs = 70, maxx = 70, inf = 1e9;
#define int long long
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

int n, s, x;
int dp[maxn][maxs][maxx];
void mark(int &x, int y) {x |= (1ll << y);}
namespace three
{
	void work()
	{
		if (n == 1)
		{
			if (s == x) cout << s << '\n';
			else puts("-1");
		}
		if (n == 2)
		{
			int a = 0, b = 0;
			bool cur = 0;
			//a <= b
			DEP(i, 60, 0) if (x & (1ll << i))
			{
				if (cur) a |= (1ll << i);
				else b |= (1ll << i);
				cur ^= 1;
			}
			if (a + b > s) puts("-1");
			else if (a + b == s) cout << b << '\n';
			else
			{
				int qaq = s - a - b;
				REP(i, 0, 60) if (!(a >> i & 1) && !(b >> i & 1))
					if (qaq >= (1ll << i + 1)) qaq -= (1ll << i + 1), a |= (1ll << i), b |= (1ll << i);
				if (a + b == s && (a ^ b) == x) cout << b << '\n';
				else puts("-1");
			}
		}
		if (n == 3)
		{
			//a <= b <= c
			int a = 0, b = 0, c = 0;
			int cur = 0, cur2 = 0;
			DEP(i, 60, 0)
				if (x >> i & 1)
				{
					cur++;
					if (cur == 1) mark(c, i);
					if (cur == 2) mark(b, i);
					if (cur == 3) mark(a, i), cur = 0;
				}
			if (a + b + c > s) puts("-1");
			else if (a + b + c == s) cout << c << '\n';
			else
			{
				int qaq = s - a - b - c;
				cur = 0;
				REP(i, 0, 60) if (qaq >= (1ll << i + 1))
				{
					qaq -= (1ll << i + 1);
					mark(a, i);mark(b, i);mark(c, i);
				}
				if (a + b + c == s && (a ^ b ^ c) == x) cout << c << '\n';
				else puts("-1");
			}
		}
	}
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();s = read<int>();x = read<int>();
		if (n <= 50 && s <= 50 && x <= 50)
		{
			int lim = 1;
			while (lim <= s) lim <<= 1;
			memset(dp, 127, sizeof dp);
			int inf = dp[0][0][0];
			lim--;
			dp[0][0][0] = 0;
			REP(i, 0, n - 1)
				REP(j, 0, s)
				REP(k, 0, lim) if (dp[i][j][k] < inf)
				REP(u, 0, s - j) chkmin(dp[i + 1][j + u][k ^ u], max(dp[i][j][k], u));
			printf("%lld\n", dp[n][s][x] < inf ? dp[n][s][x] : -1);
		}
		else three::work();
	}
	return 0;
}
