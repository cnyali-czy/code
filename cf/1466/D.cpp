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

#include <map>
#include <algorithm>
#include <vector>
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

int n, a[maxn], u[maxn], v[maxn], deg[maxn];
set <int> G[maxn];

priority_queue <pair <int, int> > que;

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
		REP(i, 1, n - 1)
		{
			u[i] = read<int>();v[i] = read<int>();
			G[u[i]].emplace(v[i]);
			G[v[i]].emplace(u[i]);
			deg[u[i]]++;deg[v[i]]++;
		}
		static int ans[maxn];
		int res = 0;
		REP(i, 1, n) res += a[i];
		ans[1] = res;
		while (!que.empty()) que.pop();
		REP(i, 1, n) if (deg[i] == 1)
		{
			int to = *G[i].begin();
			que.emplace(a[to], i);
		}
		REP(i, 2, n - 1) ans[i] = 0;
		REP(i, 2, n - 1)
		{
			if (que.empty()) break;
			int w = que.top().first, x = que.top().second;que.pop();
			res += w;
			ans[i] = res;
			if (G[x].empty()) continue;
			int to = *G[x].begin();
			deg[to]--;
			G[to].erase(x);
			if (deg[to] == 1)
				que.emplace(a[*G[to].begin()], to);
		}
		REP(i, 2, n - 1) ans[i] = max(ans[i], ans[i - 1]);
		REP(i, 1, n - 1) printf("%lld%c", ans[i], i == end_i ? '\n' : ' ');
	}
	while(!que.empty())que.pop();
	return 0;
}
