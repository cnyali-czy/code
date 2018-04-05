#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 10000 + 10, maxm = 10000 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;
int cnt[maxn], dis[maxn];
bool vis[maxn];
/*
inline int spfa()
{
	queue <int> q;
	REP(i, 1, n) q.push(i);
	while (!q.empty())
	{
		register int x = q.front();
		vis[x] = 0;
		q.pop();
		for (register int i = bg[x]; i ; i = ne[i])
			if (dis[to[i]] > dis[x] + w[i])
			{
				dis[to[i]] = dis[x] + w[i];
				if (!vis[to[i]])
				{
					q.push(to[i]);
					vis[to[i]] = 1;
					cnt[to[i]]++;
					if (cnt[to[i]] >= n) return -1;
				}
			}
	}
	return 19260817;
}
*/
inline bool spfa(int x)
{
	vis[x] = 1;
	for (register int i = bg[x]; i ; i = ne[i])
		if (dis[to[i]] > dis[x] + w[i])
		{
			dis[to[i]] = dis[x] + w[i];
			if (vis[to[i]]) return 1;
			if (spfa(to[i])) return 1;
		}
	vis[x] = 0;
	return 0;
}

int main()
{
#ifdef CraZYali
	freopen("1993.in", "r", stdin);
	freopen("1993.out", "w", stdout);
#endif
	n = read<int>();
	m = read<int>();
	while (m--)
	{
		int a, b, opt = read<int>();
		a = read<int>();b = read<int>();
		if (opt == 1)
			add(a, b, -read<int>());
		if (opt == 2)
			add(b, a, read<int>());
		if (opt == 3)
		{
			add(a, b, 0);
			add(b, a, 0);
		}
	}
	REP(i, 1, n)
		if (spfa(i))
		{
			cout << "No";
			return 0;
		}
	cout << "Yes";
	return 0;
}
