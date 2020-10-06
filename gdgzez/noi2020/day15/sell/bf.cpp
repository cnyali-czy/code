/*
	Problem:	sell.cpp
	Time:		2020-06-16 07:53
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#ifdef CraZYali
#include <ctime>
#endif
#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10, MOD = 998244353;
#define i64 long long
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a, p[maxn];
i64 ans;
namespace bf
{
	int vis[maxn];
	void dfs(int x)
	{
		if (x == n)
		{
			REP(i, 1, n) printf("%d%c",p[i],i==n?'\n':' ');
			ans++;
		}
		else
		{
			x++;
			REP(i, 1, n) if (!vis[i])
				if (i < x && x - i >= n - a)	continue;
				else if (i > x && i - x >= a)	continue;
				else
				{
					vis[i] = 1;
					p[x] = i;
					dfs(x);
					vis[i] = 0;
				}
		}
	}
}
int l[maxn], r[maxn];

namespace peach
{
	int t[maxn];
	int calc()
	{
		/*
		sort(p + n - a + 1, p + 1 + n);
		int i = 1, j = n - a + 1, N = 0;
		i64 ans = 1;
		while (i <= n - a && j <= n)
		{
			int x;
			if (p[i] < p[j])	x = p[i++];
			else				x = p[j++];
			(ans *= (x - (++N) + 1)) %= MOD;
			if (!ans) return 0;
		}
		while (i <= n - a)
		{
			int x = p[i++];
			(ans *= (x - (++N) + 1)) %= MOD;
			if (!ans) return 0;
		}
		while (j <= n)
		{
			int x = p[j++];
			(ans *= (x - (++N) + 1)) %= MOD;
			if (!ans) return 0;
		}
		*/
		i64 ans = 1;
		int N = 0;
		REP(i, n - a + 1, n) if (p[i] <= a)
		{
			N++;
			(ans *= p[i] - N + 1) %= MOD;
			if (!ans) return 0;
		}
		N++;
		(ans *= a - N + 1) %= MOD;
		if (!ans) return 0;
		REP(i, 1, n - 1) if (p[i] > a)
		{
			N++;
			(ans *= p[i] - N + 1) %= MOD;
			if (!ans) return 0;
		}
		return ans;
	}
	void work()
	{
		REP(i, 1, n - a) p[i] = r[i];
		REP(S, 0, (1 << a) - 1)
		{
			int cnt = 0;
			REP(i, 1, a)
				if (S >> (i - 1) & 1)	p[n - a + i] = l[n - a + i] - 1, cnt++;
				else					p[n - a + i] = r[n - a + i];
			ans += calc() * (cnt & 1 ? MOD - 1ll : 1ll) % MOD;
		}
		ans = (ans % MOD + MOD) % MOD;
	}
}

int main()
{
#ifdef CraZYali
	freopen("sell.in", "r", stdin);
	freopen("bf.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();a = read<int>();
		if (a >= n || !a)
		{
			puts("0");
			continue;
		}
		REP(i, 1, n)
		{
			l[i] = max(1, i + a - n + 1);
			r[i] = min(n, i + a - 1);
		}
		ans = 0;
//		peach :: work();
		bf :: dfs(0);
		cout << ans << endl;
	}
	return 0;
}

