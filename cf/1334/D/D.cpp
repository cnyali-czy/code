/*
	Problem:	D.cpp
	Time:		2020-04-10 23:09
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

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

int n;
#define i64 long long
#define int i64
i64 l, r;
vector <int> ans;
bool vis[maxn];
signed main()
{
#ifdef CraZYali
	file("D");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		l = read<i64>();
		r = read<i64>();
		i64 s = 0;
		REP(i, 1, n - 1)
		{
			int delta = (n - i) * 2;
			if (s + delta >= l && s + 1 <= l)
			{
				REP(j, l - s, min(delta, r - s))
					printf("%lld ", (j & 1) ? i : i + j / 2);
				chkmax(l, s + delta + 1);
			}
			s += delta;
		}
		if (r == s + 1) putchar('1');
		puts("");
	}
	return 0;
}
