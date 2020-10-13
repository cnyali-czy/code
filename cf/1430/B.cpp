/*
	Problem:	B.cpp
	Time:		2020-10-11 19:24
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <queue>
#include <iostream>
#include <cstdio>
#include <set>
#define int long long
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

int n, k;
priority_queue <int> q;

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();k = read<int>();
		REP(i, 1, n) q.emplace(read<int>());
		REP(i, 1, k)
		{
			int x = q.top();q.pop();
			int y = q.top();q.pop();
			q.emplace(x + y);
			q.emplace(0);
		}
		int Max = q.top(), Min = Max;
		while (!q.empty())
		{
			Min = min(Min, q.top());
			q.pop();
		}
		cout << Max - Min << '\n';
	}
	return 0;
}
