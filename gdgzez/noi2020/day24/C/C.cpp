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
const int maxn = 1000 + 10, maxm = maxn * 3 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e;
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

int m, n, k;

bool vis[maxn];
int ans;
void dfs(int x, int y = 0)
{
	chkmax(ans, y);
	vis[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
		dfs(to[i], y + w[i]);
	vis[x] = 0;
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	m = 3 * (n - 2);
	while (m--)
	{
		int x = read<int>(), y = read<int>(), z = read<int>();
		add(x, y, z);add(y, x, z);
	}
	REP(i, 1, n + 1 >> 1) dfs(i);
	cout << ans << endl;
	return 0;
}
