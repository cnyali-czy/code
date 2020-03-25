/*
	Problem:	B.cpp
	Time:		2020-03-23 22:45
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_set>
#include <vector>
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, match[maxn], can[maxn];
bool vis[maxn];
unordered_set <int> S[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) vis[i] = 0, can[i] = n;
		int gg = 0;
		REP(i, 1, n)
		{
			match[i] = 0;
			int k = read<int>();
			S[i].clear();
			while (k--)
			{
				int x = read<int>();
				S[i].insert(x);
				can[x]--;
				if (!vis[x] && !match[i])
					vis[match[i] = x] = 1;
			}
			if (!match[i]) gg = i;
		}
		if (!gg) puts("OPTIMAL");
		else
		{
			bool flag = 0;
			REP(i, 1, n) if (!vis[i] && can[i])
			{
				REP(j, 1, n) if (!match[j] && S[j].find(i) == S[j].end())
				{
					flag = 1;
					printf("IMPROVE\n%d %d\n", j, i);
					break;
				}
				break;
			}
			if (!flag) puts("OPTIMAL");
		}
	}
	return 0;
}
