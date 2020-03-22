/*
	Problem:	4059.cpp
	Time:		2020-03-22 23:08
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

using namespace std;
const int maxn = 2e5 + 10;

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

int n, m, pre[maxn], nxt[maxn], a[maxn], b[maxn], lst[maxn];

bool check(int l, int r)
{
	if (l > r) return 1;
	int L = l, R = r, pos = -1;
	int flag = 0;
	while (L <= R)
	{
		flag = !flag;
		int i = (flag ? R-- : L++);
		if (pre[i] < l && nxt[i] > r)
		{
			pos = i;
			break;
		}
	}
	if (pos == -1) return 0;
	if (!check(l, pos - 1)) return 0;
	if (!check(pos + 1, r)) return 0;
	return 1;
}

int main()
{
#ifdef CraZYali
	file("4059");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) b[i] = a[i] = read<int>();
		sort(b + 1, b + 1 + n);
		m = unique(b + 1, b + 1 + n) - b - 1;
		REP(i, 1, n)
		{
			a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b;
			lst[a[i]] = 0;
		}
		REP(i, 1, n)
		{
			pre[i] = lst[a[i]];
			lst[a[i]] = i;
		}
		REP(i, 1, n) lst[a[i]] = n + 1;
		DEP(i, n, 1)
		{
			nxt[i] = lst[a[i]];
			lst[a[i]] = i;
		}
		if (check(1, n)) printf("non-");
		puts("boring");
	}
	return 0;
}
