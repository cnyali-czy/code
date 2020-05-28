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
const int maxn = 200 + 5, maxm = 200 + 5;

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

int C, n, m, b[maxn], a[maxn][maxm], s[maxn];

vector <int> v[maxn][maxm], p2[maxn];
int p1[maxn];
bool vis[maxn];

bool dfs(int x, int y)
{
	for (auto i : v[x][y]) if (!vis[i])
	{
		vis[i] = 1;
		if (p2[i].size() < b[i])
		{
			p1[x] = i;
			p2[i].emplace_back(x);
			return 1;
		}
		for (auto &j : p2[i]) if (dfs(j, a[j][i]))
		{
			p1[x] = i;
			j = x;
			return 1;
		}
	}
	return 0;
}

int tp1[maxn][maxn];
vector <int> tp2[maxn][maxn];
int ans1[maxn], ans2[maxn];

void work1()
{
	REP(i, 1, n)
	{
		memset(vis, 0, sizeof vis);
		REP(j, 1, m) if (v[i][j].size() && dfs(i, j)) break;
		copy(p1 + 1, p1 + i + 1, tp1[i] + 1);
		copy(p2 + 1, p2 + m + 1, tp2[i] + 1);
	}
}
bool judge(int i, int x)
{
	REP(i, 1, x - 1) p1[i] = tp1[x - 1][i];
	REP(i, 1, m) p2[i] = tp2[x - 1][i];
	memset(vis, 0, sizeof vis);
	REP(j, 1, s[i]) if (v[i][j].size() && dfs(i, j)) return 1;
	return 0;
}

int main()
{
#ifdef CraZYali
	file("4382");
#endif
	register int T = read<int>();C = read<int>();
	REP(Case, 1, T)
	{
		n = read<int>();m = read<int>();
		REP(i, 1, m) b[i] = read<int>(), p2[i].clear();
		REP(i, 1, n) p1[i] = 0;
		REP(i, 1, n)
			REP(j, 1, m)
			{
				a[i][j] = read<int>();
				if (a[i][j]) v[i][a[i][j]].emplace_back(j);
			}
		REP(i, 1, n) a[i][0] = m + 1;
		REP(i, 1, n) s[i] = read<int>();
		work1();
		REP(i, 1, n) printf("%d%c", ans1[i] = a[i][p1[i]], i == n ? '\n' : ' ');
		REP(i, 1, n)
		{
			if (ans1[i] <= s[i])
			{
				ans2[i] = 0;
				continue;
			}
			int gd = 0, l = 1, r = i - 1;
			while (l <= r)
			{
				int mid = l + r >> 1;
				if (judge(i, mid)) l = (gd = mid) + 1;
				else r = mid - 1;
			}
			ans2[i] = i - gd;
		}
		REP(i, 1, n) printf("%d%c", ans2[i], i == n ? '\n' : ' ');
		REP(i, 1, n) REP(j, 1, m) v[i][a[i][j]].clear();
	}
	return 0;
}
