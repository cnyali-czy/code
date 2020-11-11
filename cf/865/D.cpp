/*
	Problem:	D.cpp
	Time:		2020-11-06 14:38
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
#include <queue>
#define int long long

using namespace std;
const int maxn = 3e5 + 10;

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

signed main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();
	priority_queue <int, vector <int>, greater <int> > q;
	int ans = 0;
	REP(i, 1, n)
	{
		int x = read<int>();
		if (q.size() && q.top() < x)
		{
			ans += x - q.top();
			q.pop();
			q.push(x);
		}
		q.push(x);
	}
	cout << ans << endl;
	return 0;
}
