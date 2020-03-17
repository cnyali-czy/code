/*
	Problem:	A.cpp
	Time:		2020-03-12 09:23
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
#define i64 long long
using namespace std;
const int maxn = 1e6 + 10;

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

int n, k, a[maxn], b[maxn];
namespace run
{
	i64 f[maxn], g[maxn], ans, sum, x, y;
	priority_queue <i64, vector <i64>, greater <i64> > Q;
	i64 sig(int l, int r) {return (r - l + 1ll) * (l + r) >> 1;}
	void work(int tot, int a[], i64 dp[])
	{
		i64 s = 0, tmp;
		REP(i, 1, n)
		{
			dp[i] = 1e18;
			if (i > 1)
			{
				Q.emplace(tmp = ((i - 1ll) * x + a[i - 1]));
				s += tmp;
			}
			while (Q.size() > tot)
			{
				s -= Q.top();
				Q.pop();
			}
			if (Q.size() == tot) dp[i] = sig(i - tot, i - 1) * x - s;
		}
	}
	int main()
	{
		REP(i, 1, n)
		{
			b[n - i + 1] = a[i] = read<int>();
			sum += a[i];
		}
		cin >> x >> y;
		work(k >> 1, a, f);
		while (!Q.empty()) Q.pop();
		work(k - (k >> 1) - 1, b, g);
		i64 ans = 1e18;
		REP(i, 1, n) if (f[i] < 1e18 && g[n - i + 1] < 1e18)
			chkmin(ans, f[i] + g[n - i + 1] - a[i] + y);
		cout << ans + sum << '\n';
		return 0;
	}

}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();k = read<int>();
	return run::main();
}
