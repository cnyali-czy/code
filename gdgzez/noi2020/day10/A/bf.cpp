#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;
#define i64 long long
int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;

void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

template <typename T> T read()
{
	T ans(0), flag(1);
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, m, ty;
i64 a[maxn], lastans;

int fa[maxn], wfa[maxn];
void dfs(int x)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		wfa[to[i]] = w[i];
		fa[to[i]] = x;
		dfs(to[i]);
	}
}
vector <pair <int, int> > mem[maxn];
i64 query(int x)
{
	i64 res = 0;
	for (int y = x, mn = 1e9; y; chkmin(mn, wfa[y]), y = fa[y])
		for (auto i : mem[y]) if (mn >= i.second) res += i.first;
	return res;
}


int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();ty = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		add(x, y, z);add(y, x, z);
	}
	dfs(1);
	while (m--)
	{
		int opt = read<int>();
		if (opt == 1)
		{
			int x = read<int>();
			if (ty) x = (x + lastans) % n + 1;
			printf("%lld\n", lastans = (a[x] + query(x)));
		}
		else
		{
			int v = read<int>(), d = read<int>(), x = read<int>();
			if (ty) x = (x + lastans) % n + 1;
			mem[x].emplace_back(v, d);
		}
	}
	return 0;
}
