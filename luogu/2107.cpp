/*
	Problem:	2107.cpp
	Time:		2020-11-16 19:53
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <queue>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long
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

int n, m;
pair <int, int> a[maxn];

signed main()
{
#ifdef CraZYali
	file("2107");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n)
	{
		int x = read<int>(), y = read<int>();
		a[i] = make_pair(x, y);
	}
	sort(a + 1, a + 1 + n);
	priority_queue <int> q;
	int ans = 0, tot = 0;
	REP(i, 1, n)
	{
		tot += a[i].second;
		q.emplace(a[i].second);
		while (!q.empty() && tot + a[i].first > m)
		{
			tot -= q.top();
			q.pop();
		}
		ans = max(ans, (int)q.size());
	}
	cout << ans << endl;
	return 0;
}
