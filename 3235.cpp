/*
	Problem:	3235.cpp
	Time:		2021-03-05 17:18
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
#include <algorithm>
#include <cassert>
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

int T, f;
int sg[maxn];

void init()
{
	const int N = 1e5;
	sg[1] = 0;
	REP(n, max(2, f), N)
	{
		static int c[maxn];int m = 0;
		for (int i = 1, j; i <= n; i = j + 1)
		{
			j = n / (n / i);
			int v1 = n / i, v2 = v1 + 1;
			REP(k, i, min(i + 1, j))
			{
				int res = 0;
				int p2 = n - k * v1, p1 = k - p2;
				assert(p1 * v1 + p2 * v2 == n);
				if (p1 & 1) res ^= sg[v1];
				if (p2 & 1) res ^= sg[v2];
				c[m++] = res;
			}
		}
		static bool vis[maxn];
		REP(i, 0, m - 1) vis[c[i]] = 1;
		REP(i, 0, n) if (!vis[i])
		{
			sg[n] = i;
			break;
		}
		REP(i, 0, m - 1) vis[c[i]] = 0;
	}
}

int main()
{
#ifdef CraZYali
	file("3235");
#endif
	cin >> T >> f;
	init();
	REP(Case, 1, T)
	{
		int ans = 0;
		REP(i, 1, read<int>()) ans ^= sg[read<int>()];
		printf("%d%c", !!ans, Case == end_Case ? '\n' : ' ' );
	}
	return 0;
}
