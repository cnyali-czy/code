/*
	Problem:	E.cpp
	Time:		2020-10-11 21:51
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
#include <vector>
#include <algorithm>
#include <cstring>

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

int n;
char s[maxn];
vector <int> stk[26];

namespace fenwick
{
	int s[maxn];
	void add(int x, int y)
	{
		while (x > 0)
		{
			s[x] += y;
			x &= (x - 1);
		}
	}
	int sum(int x)
	{
		int y = 0;
		while (x <= n)
		{
			y += s[x];
			x += x & -x;
		}
		return y;
	}
}

int main()
{
#ifdef CraZYali
	file("E");
#endif
	n = read<int>();
	scanf("%s", s + 1);
	DEP(i, n, 1)
		stk[s[i] - 'a'].emplace_back(i);
	long long ans = 0;
	REP(i, 1, n)
	{
		int c = s[n - i + 1] - 'a';
		int x = stk[c].back();
		stk[c].pop_back();
		ans += fenwick :: sum(x);
		fenwick :: add(x, 1);
	}
	cout << ans << endl;
	return 0;
}
