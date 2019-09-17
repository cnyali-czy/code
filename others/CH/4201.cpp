/*
 * File Name:	4201.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.16 20:29
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 200000 + 10;

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, a[maxn];

struct fenwick
{
	int s[maxn];
	inline void clear()
	{
		REP(i, 1, n) s[i] = 0;
	}
	inline void add(int x, int val = 1)
	{
		while (x <= n)
		{
			s[x] += val;
			x += x & -x;
		}
	}
	inline int sum(int x)
	{
		int res(0);
		while (x > 0)
		{
			res += s[x];
			x -= x & -x;
		}
		return res;
	}
}A, B;

inline long long solve()
{
	long long ans(0);
	A.clear(); B.clear();
	REP(i, 1, n) B.add(a[i]);
	REP(i, 1, n)
	{
		B.add(a[i], -1);
		ans += 1ll * A.sum(a[i]) * B.sum(a[i]);
		A.add(a[i]);
	}
	return ans;
}

int main()
{
#ifdef CraZYali
	file("4201");
#endif
	cin >> n;
	REP(i, 1, n) a[i] = -read<int>() + n + 1;
	printf("%lld ", solve());
	REP(i, 1, n) a[i] = -a[i] + n + 1;
	printf("%lld\n", solve());
	return 0;
}
