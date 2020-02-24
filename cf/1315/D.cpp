/*
	Problem:	D.cpp
	Time:		2020-02-24 10:33
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
#include <queue>
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

priority_queue <int> q;
int n, ans, sum;

pair <int, int> a[maxn];

inline void solve(int x)
{
	REP(i, 1, x)
	{
		if (q.empty()) break;
		sum -= q.top();q.pop();
		ans += sum;
	}
}
inline void ins(int x)
{
	sum += a[x].second;
	q.emplace(a[x].second);
}

signed main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();
	REP(i, 1, n) a[i].first = read<int>();
	REP(i, 1, n) a[i].second = read<int>();
	sort(a + 1, a + 1 + n);
	REP(i, 1, n)
	{
		solve(a[i].first - a[i-1].first);
		ins(i);
	}
	solve(n);
	cout << ans << endl;
	return 0;
}
