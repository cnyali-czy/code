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
#define int long long

using namespace std;
const int maxn = 2e5 + 10;

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
char s[maxn];

int a[maxn], N, ans;

void bf(int x)
{
	while (x ^ 1)
	{
		ans++;
		if (x & 1) x = 3 * x + 1;
		else x >>= 1;
	}
}

pair <int, int> work(int x, int len)
{
	int a = 0, b = 1;
	while (x)
	{
		ans++;
		if (x & 1) x = x * 3 + 1, a *= 3, b *= 3;
		else x >>= 1, len--;

		if (x >> len)
		{
			a += (x >> len);
			x &= ((1ll << len) - 1);
		}
	}
	ans += len;
	return make_pair(a, b);
}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	reverse(s + 1, s + 1 + n);
	const int block = 24, U = (1ll << block) - 1;
	int times = block;
	REP(i, 1, n)
	{
		if (times == block)
		{
			times = 0;
			N++;
		}
		a[N] |= ((int)(s[i] - '0')) << times;
		times++;
	}
	for (int i = 1; i < N; i++)
	{
		auto qaq = work(a[i], block);
		int a = qaq.first, b = qaq.second;
		REP(j, i + 1, N)
		{
			int x = ::a[j];
			x *= b;x += a;
			::a[j] = x & U;a = x >> block;
		}
		while (a)
		{
			::a[++N] = a & U;
			a >>= block;
		}
	}
	bf(a[N]);
	cout << ans << endl;
	return 0;
}
