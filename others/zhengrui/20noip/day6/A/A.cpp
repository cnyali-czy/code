#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10, MOD = 1e9 + 7;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int n, a[maxn], ans;
double f[maxn][2];
inline int id(int x, int y) {return x + y * n;}
vector <int> G[maxn << 1];

void dfs(int x, int fa = 0)
{
	f[x][0] = 0;
	f[x][1] = log(a[x]);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		int y = to[i];
		dfs(y, x);
		f[x][1] += f[y][0];G[id(x, 1)].emplace_back(id(y, 0));
		if (f[y][0] > f[y][1])
		{
			f[x][0] += f[y][0];
			G[id(x, 0)].emplace_back(id(y, 0));
		}
		else
		{
			f[x][0] += f[y][1];
			G[id(x, 0)].emplace_back(id(y, 1));
		}
	}
}
void orz(int x)
{
	if (x > n) ans = 1ll * ans * a[x - n] % MOD;
	for (int y : G[x]) orz(y);
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	dfs(1);
	ans = 1;
	if (f[1][0] > f[1][1]) orz(id(1, 0));
	else orz(id(1, 1));
	cout << ans << endl;
	return 0;
}
