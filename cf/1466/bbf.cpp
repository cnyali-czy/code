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
vector <int> G[maxn];

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
		vector <int> v1, v2;
		map <pair <int, int> , int> id;
		REP(i, 1, n - 1)
		{
			u[i] = read<int>();v[i] = read<int>();
			deg[u[i]]++;deg[v[i]]++;
			G[u[i]].emplace_back(v[i]);
			G[v[i]].emplace_back(u[i]);
			id[make_pair(u[i], v[i])] = i;
			id[make_pair(v[i], u[i])] = i;
		}
		int res = 0;
		REP(i, 1, n) res += a[i];
		static int ans[maxn];
		ans[1] = res;
		set <pair <int, int> > s1, s2;
		REP(i, 1, n - 1)
		{
			int u = ::u[i], v = ::v[i];
			if (deg[u] == 1 && deg[v] == 1) continue;
			if (deg[u] == 1 || deg[v] == 1)
				s2.emplace(-(a[u] * (deg[u] != 1) + a[v] * (deg[v] != 1)), i);
			else
				s1.emplace(-(a[u] + a[v]), i);
		}
		cerr << s1.begin() -> first << endl;
		REP(i, 2, n - 1)
		{
			if (!s1.size() && !s2.size()) break;
			int pick = 1, u, v, e;
			if (!s1.size()) pick = 2;
			else if (s2.size() && s1.begin() -> second > s2.begin() -> second) pick = 2;
			if (pick == 1)
			{
				e = s1.begin() -> second;
				res -= s1.begin() -> first;
				s1.erase(s1.begin());
			}
			else
			{
				res -= s2.begin() -> first;
				e = s2.begin() -> second;
				s2.erase(s2.begin());
			}
			cout << pick << ' ' << e << endl;
			u = ::u[e];v = ::v[e];
			deg[u]--;deg[v]--;
			if (deg[u] == 1)
				for (int V : G[u])
				{
					int e = id[make_pair(u, V)];
					auto it = s1.find(make_pair(-(a[u] + a[V]), e));
					if (it != s1.end()) s1.erase(it);
					if (deg[V] == 1) continue;
					s2.emplace(-a[V], e);
				}
			u = v;
			if (deg[u] == 1)
				for (int V : G[u])
				{
					int e = id[make_pair(u, V)];
					auto it = s1.find(make_pair(-(a[u] + a[V]), e));
					if (it != s1.end()) s1.erase(it);
					if (deg[V] == 1) continue;
					s2.emplace(-a[V], e);
				}
			ans[i] = res;
		}
		REP(i, 1, n - 1) ans[i] = max(ans[i], ans[i - 1]);
		REP(i, 1, n - 1) printf("%lld%c", ans[i], i == end_i ? '\n' : ' ');
	}
	return 0;
}
