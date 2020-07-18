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
#define int long long
using namespace std;
const int maxn = 500 + 5, inf = 1e18;

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

int n, m, a[maxn][maxn];
namespace KM
{
	int mat[maxn], pre[maxn], ka[maxn], kb[maxn], c[maxn];
	bool vis[maxn];
	void orz(int jjs)
	{
		int v = 0;
		REP(i, 1, n) pre[i] = 0, vis[i] = 0, c[i] = inf;
		mat[v] = jjs;
		do
		{
			int x = mat[v], Min = inf, nxt = 0;
			vis[v] = 1;
			REP(y, 1, n) if (!vis[y])
			{
				if (c[y] > ka[x] + kb[y] - a[x][y])
				{
					c[y] = ka[x] + kb[y] - a[x][y];
					pre[y] = v;
				}
				if (c[y] < Min) Min = c[y], nxt = y;
			}
			REP(i, 0, n)
				if (vis[i])	ka[mat[i]] -= Min, kb[i] += Min;
				else		c[i] -= Min;
			v = nxt;
		}while (mat[v]);
		while (v)
		{
			mat[v] = mat[pre[v]];
			v = pre[v];
		}
	}
	void work()
	{
		REP(i, 1, n) orz(i);
		int ans = 0;
		REP(i, 1, n) ans += a[mat[i]][i];
		cout << ans << endl;
		REP(i, 1, n) printf("%lld%c", mat[i], i == n ? '\n' : ' ');
	}
}

signed main()
{
#ifdef CraZYali
	file("6577");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) REP(j, 1, n) a[i][j] = -inf;
	while (m--)
	{
		int x = read<int>(), y = read<int>(), w = read<int>();
		chkmax(a[x][y], w);
	}
	KM :: work();
	return 0;
}
