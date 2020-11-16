/*
	Problem:	4053.cpp
	Time:		2020-11-16 19:25
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <queue>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 1.5e5 + 10;

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
pair <int, int> a[maxn];

signed main()
{
#ifdef CraZYali
	file("4053");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		int t1 = read<int>(), t2 = read<int>();
		a[i] = make_pair(t2, t1);
	}
	sort(a + 1, a + 1 + n);
	priority_queue <int> q;
	int t = 0;
	REP(i, 1, n)
		if (t + a[i].second > a[i].first)
		{
			if (q.size())
			{
				int qaq = q.top();
				if (qaq > a[i].second)
				{
					q.pop();
					q.emplace(a[i].second);
					t -= qaq;t += a[i].second;
				}
			}
		}
		else
		{
			t += a[i].second;
			q.emplace(a[i].second);
		}
	cout << q.size() << endl;
	return 0;
}
