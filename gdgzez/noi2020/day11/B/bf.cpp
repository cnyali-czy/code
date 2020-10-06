/*
	Problem:	B.cpp
	Time:		2020-06-11 08:18
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
#define i64 long long
using namespace std;
const int maxn = 5e5 + 10, maxm = 5e5 + 10;

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

int n, m, a[maxn], k[maxm];

namespace bf
{
	priority_queue <int> q, tmp;
	void work()
	{
		while (!q.empty()) q.pop();
		sort(a + 1, a + 1 + n, greater <int>());
		REP(i, 1, n) q.push(a[i]);
		i64 ans = 0;
		REP(i, 1, m)
		{
			i64 res = 0;
			REP(j, 1, k[i])
			{
				a[j]--;
				int x = q.top();q.pop();
				res += x;
				ans += x;tmp.push(--x);
			}
			while (!tmp.empty()) q.push(tmp.top()), tmp.pop();
		sort(a + 1, a + 1 + n, greater <int>());
//			REP(i, 1, n) printf("%d ", a[i]);puts("");
		//	printf("%lld\n", res);
		}
		printf("%lld\n", ans);
	}
}

int main()
{
	freopen("B.in", "r", stdin);
	freopen("bf.out", "w", stdout);
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	m = read<int>();
	REP(i, 1, m) k[i] = read<int>();
	bf :: work();
	return 0;
}
