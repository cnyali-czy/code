/*
	Problem:	C.cpp
	Time:		2020-06-14 23:37
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;

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

namespace run
{
	const int maxn = 15000 + 10;
	int n, a[maxn], p[maxn], b[2][maxn];
	string s;

	void output(int t)
	{
		printf("%d %s\n", t, s.c_str());
		b[0][0]=b[1][0]=0;
		REP(i, 0, n - 1) if (s[i] & 1)
		{
			int j = (a[i] & 1) ^ t;
			b[j][++b[j][0]] = a[i];
		}
		REP(i, 1, b[1][0]) b[0][++b[0][0]] = b[1][i];
		int j = 0;
		REP(i, 0, n - 1) if (s[i] & 1) a[i] = b[0][++j];
	}

	int main()
	{
		register int T = read<int>();
		while (T--)
		{
			n = read<int>();read<int>();
			puts("29");
			REP(i, 0, n - 1) a[i] = read<int>();
			for (register int i = 0, j = (n + 3) / 4 * 2 ; i < n; i += 2)
				p[i] = i < j ? i : i - j + 1;
			for (register int i = 1, j = n + 1 >> 1, k = j & 1; i < n; i += 2)
				p[i] = j + (i + k <= (n >> 1) ? - i - k : j - i - 1);
			REP(i, 0, 13)
			{
				s = string(n, '1');output(0);
				REP(j, 0, n - 1) s[j] = '0' + (p[a[j]] >> i & 1) ;
				output(1);
			}
			REP(i, 0, n - 1) s[i] = 48 + (a[i] != i);
			output(1);
		}
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	return run :: main();
}
