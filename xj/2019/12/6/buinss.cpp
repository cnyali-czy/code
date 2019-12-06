#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNTION__, __LINE__)

#include <iostream>
#include <cstdio>
#include <set>
#include <queue>
#include <algorithm>
#define int long long

using namespace std;
const int maxn = 1e5 + 10, maxm = 1e5 + 10;

template <typename T>
inline T read()
{
	register T ans(0), flag(1);
	char c(getchar());
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
struct path
{
	int u, v, c, w;
	inline bool operator < (const path &B) const {return w > B.w;}
}e[maxm];
struct cmp
{
	inline bool operator () (pair <int, int> B, pair <int, int> A) {return e[A.first].u < e[B.first].u;}
};
priority_queue <pair <int, int>, vector <pair <int, int> >, cmp> q[maxn];

int n, m, a[maxn];

int calc(int x, int i, int c)
{
	if (x < e[i].u || !c) return 0;
	int res(0);
	if (a[x])
	{
		int y = min(a[x], c);
		c -= y;
		a[x] -= y;
		res += y;
		q[x].emplace(i, y);
		if (!c) return res;
	}
	while (c)
	{
		auto it = q[x].top();
		if (e[it.first].u < e[i].u)
		{
			q[x].pop();
			int y = min(c, calc(x >> 1, it.first, min(c, it.second)));
			if (y)
				q[x].emplace(i, y);
			res += y;
			c -= y;
			if (y < it.second)
			{
				q[x].emplace(it.first, it.second - y);
				break;
			}
		}
		else break;

	}
	return res + calc(x >> 1, i, c);
}

signed main()
{
#ifdef CraZYali
	freopen("buinss.in", "r", stdin);
	freopen("buinss.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		m = read<int>();
		REP(i, 1, n)
		{
			a[i] = read<int>();
			while (!q[i].empty()) q[i].pop();
		}
		REP(i, 1, m)
		{
			int u(read<int>()), v(read<int>()), c(read<int>()), w(read<int>());
			e[i] = path{u, v, c, w};
		}
		sort(e + 1, e + 1 + m);
		int ans(0);
		REP(i, 1, m)
			ans += e[i].w * calc(e[i].v, i, e[i].c);
		printf("%lld\n", ans);
	}
	return 0;
}
