/*
	Problem:	A.cpp
	Time:		2020-07-27 08:42
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 3000 + 10;

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

int n, m, id[maxn], cur, cnt[1 << 14];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();
	if (m > 14) m = 14;
	REP(i, 1, (1 << m) - 1)
	{
		cnt[i] = cnt[i >> 1] + (i & 1);
		if (cnt[i] == (m / 2))
		{
			id[++cur] = i;
			if (cur >= n) break;
		}
	}
	REP(i, 2, n)
	{
		REP(j, 1, i - 1)
		{
			int x = id[i], y = id[j], op;
			scanf("%1d", &op);
			if (!op) swap(x, y);
			REP(k, 1, m) if ((x >> (k - 1) & 1) && !(y >> (k - 1) & 1))
			{
				putchar('a' + k - 1);
				break;
			}
		}
		puts("");
	}
	return 0;
}
