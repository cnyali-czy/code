/*
	Problem:	D.cpp
	Time:		2020-12-30 23:04
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <queue>
#include <set>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e5 + 10, inf = 1e16;

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

int n, a[maxn];

int deg[maxn];
set <int> G[maxn];
set <pair <int, int> > que;
priority_queue <pair <int, pair <int, int> > > de;

signed main()
{
#ifdef CraZYali
	file("D");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		REP(i, 1, n) G[i].clear(), deg[i] = 0;
		REP(i, 2, n)
		{
			int u = read<int>(), v = read<int>();
			deg[u]++;deg[v]++;
			G[u].emplace(v);G[v].emplace(u);
		}
				{
					for (int v : G[u])
					{
						G[v].erase(u);
						de.emplace(-(a[u] + (!deg[v]) * a[v]), make_pair(u, v));
					}
					G[u].clear();
					que.erase(que.begin());
				}
				else break;
			}
			if (que.size())
			{
				int u = (--que.end()) -> second;
				int v = *G[u].begin();
				que.erase(make_pair(deg[u], u));
				que.emplace(make_pair(--deg[u], u));
				que.erase(make_pair(deg[v], v));
				que.emplace(make_pair(--deg[v], v));
				G[u].erase(v);G[v].erase(u);
			}
			else
			{
				auto node = de.top();de.pop();
				sum += node.first;
				int u = node.second.first, v = node.second.second;
			}
		}
	}
	return 0;
}
