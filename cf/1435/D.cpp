/*
	Problem:	D.cpp
	Time:		2020-10-25 20:08
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m;

int lst[maxn], a[maxn];

int ard = 0;
vector <int> str[maxn];

int main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();
	REP(i, 1, n << 1)
	{
		char c = getchar();
		while (c != '+' && c != '-') c = getchar();
		if (c == '+') ard++;
		if (c == '-')
		{
			if (!ard)
			{
				puts("NO");
				return 0;
			}
			ard--;
			a[++m] = read<int>();
			int x = 0;
			for (x = lst[m - 1]; x && a[x] <= a[m]; x = lst[x]);
			lst[m] = x;
			str[lst[m]].emplace_back(a[m]);
		}
	}
	puts("YES");
	REP(i, 0, m) for (auto j : str[i]) printf("%d ", j);
	return 0;
}
