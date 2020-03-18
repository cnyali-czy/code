/*
	Problem:	B.cpp
	Time:		2020-02-15 16:48
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <queue>
#include <deque>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e6 + 10, maxm = maxn, MOD = 1e9 + 7;

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

namespace run
{
	int n, m, ans;
	bool vis[maxn];
	deque <pair <int, int> > q;
	queue <pair <int, int> > tmp;

	int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
	bool w[maxm << 1];
	void add(int x, int y, bool z)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
	}

	int main()
	{
		cin >> n >> m;
		while (m--)
		{
			int k(read<int>()), type(read<int>()), xk(read<int>()), xb(read<int>()), xm(read<int>()), xl(read<int>()), yk(read<int>()), yb(read<int>()), ym(read<int>()), yl(read<int>());
			REP(j, 0, k - 1)
			{
				int u = (1ll * j * xk + xb) % xm + xl;
				int v = (1ll * j * yk + yb) % ym + yl;
				add(u, v, type);add(v, u, type);
			}
		}
		q.emplace_back(1, 1);
		while (!q.empty())
		{
			auto p = q.front();q.pop_front();
			int x = p.second;
			if (!vis[x])
			{
				vis[x] = 1;
				ans ^= p.first;
				for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
					if (!w[i]) tmp.emplace((p.first + 1) % MOD, to[i]);
					else q.emplace_back(p.first * 2 % MOD, to[i]);
			}
			if (q.empty() || q.front().first ^ p.first)
				while (!tmp.empty()) q.emplace_front(tmp.front()), tmp.pop();
		}
		cout << ans << endl;
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	return run::main();
}
