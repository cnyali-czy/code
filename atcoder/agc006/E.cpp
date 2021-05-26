/*
	Problem:	2166.cpp
	Time:		2021-05-06 15:15
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

inline void fuck()
{
	puts("No");
	exit(0);
}
int n, a[3][maxn], b[maxn];
bool vis[maxn];

struct fenwick
{
	int s[maxn];
	fenwick()
	{
		memset(s, 0, sizeof s);
	}
	void add(int x, int y)
	{
		while (x <= n)
		{
			s[x] += y;
			x += x & -x;
		}
	}
	int sum(int x)
	{
		int y = 0;
		while (x > 0)
		{
			y += s[x];
			x &= (x - 1);
		}
		return y;
	}
}f[2];

int main()
{
#ifdef CraZYali
	file("2166");
#endif
	n = read<int>();
	REP(i, 0, 2) REP(j, 1, n) a[i][j] = read<int>();
	REP(i, 1, n)
	{
		int id[] = {(a[0][i] + 2) / 3, (a[1][i] + 2) / 3, (a[2][i] + 2) / 3};
		if (id[0] != id[1] || id[0] != id[2] || id[1] != id[2]) fuck();
		if (a[0][i] == a[1][i] - 1)
		{
			if (a[2][i] != a[1][i] + 1) fuck();
			b[i] =  id[0];
		}
		else
		{
			if (a[2][i] != a[1][i] - 1) fuck();
			b[i] = -id[0];
		}
	}
	int c[] = {0, 0};
	long long r[] = {0, 0};
	DEP(i, n, 1)
	{
		int x = i & 1, y = b[i];
		if (y < 0) c[x]++, y = -y;
		if ((y & 1) ^ x) fuck();

		r[x] += f[x].sum(y - 1);
		f[x].add(y, 1);
	}
	if ((r[0] & 1) ^ (c[1] & 1)) fuck();
	if ((r[1] & 1) ^ (c[0] & 1)) fuck();
	puts("Yes");
	return 0;
}
