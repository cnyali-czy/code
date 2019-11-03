#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 3e5 + 10;

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

int n, p[maxn], r[maxn], pre[maxn], suf[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n) p[i] = read<int>(), r[i] = read<int>();
	pre[1] = p[1] + r[1];
	REP(i, 2, n) pre[i] = max(pre[i-1], p[i] + r[i]);
	suf[n] = p[n] - r[n];
	DREP(i, n - 1, 1) suf[i] = min(suf[i+1], p[i] - r[i]);
	REP(i, 2, n)
		if (p[i-1] < suf[i]) return 0 * puts("-1");
	REP(i, 1, n - 1)
		if (pre[i] < p[i+1]) return 0 * puts("-1");
	cout << 3ll * (p[n] - p[1]);putchar(10);
	return 0;
}
