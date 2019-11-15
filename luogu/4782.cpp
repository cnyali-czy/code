#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e6 * 2 + 10, maxm = 1e6 * 4 + 5;

int bg[maxn], ne[maxm], to[maxm], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
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

int n, m;

int dfn[maxn], low[maxn], dfs_clock, blg[maxn], cnt, stack[maxn], top;
bool ins[maxn];

void dfs(int x)
{
	ins[stack[++top] = x] = 1;
	dfn[x] = low[x] = ++dfs_clock;
	for (int i = bg[x]; i; i = ne[i])
		if (!dfn[to[i]])
		{
			dfs(to[i]);
			chkmin(low[x], low[to[i]]);
		}
		else if (ins[to[i]]) chkmin(low[x], dfn[to[i]]);
	if (low[x] == dfn[x])
	{
		cnt++;
		int u;
		do
		{
			ins[u = stack[top--]] = 0;
			blg[u] = cnt;
		}while (u ^ x);
	}
}

int main()
{
#ifdef CraZYali
	file("4782");
#endif
	cin >> n >> m;
	while (m--)
	{
		int i(read<int>()), a(read<int>()), j(read<int>()), b(read<int>());
		if (a)
			if (b)
			{
				add(i + n, j);
				add(j + n, i);
			}
			else
			{
				add(i + n, j + n);
				add(j, i);
			}
		else
			if (b)
			{
				add(i, j);
				add(j + n, i + n);
			}
			else
			{
				add(i, j + n);
				add(j, i + n);
			}
	}
	const int N = n + n;
	REP(i, 1, N) if (!dfn[i]) dfs(i);
#ifdef CraZYali
	REP(i, 1, N) printf("%d%c", blg[i], i == N ? '\n' : ' ');
	puts("");
	REP(x, 1, N)
		for (int i = bg[x]; i; i = ne[i]) printf("%d %d\n", x, to[i]);
	puts("");
	REP(x, 1, N)
		for (int i = bg[x], y = to[i]; i; y = to[i = ne[i]])
			printf("if %d is [%s], then %d is [%s]\n", x > n ? x - n : x, x > n ? "False" : "True", y > n ? y - n : y, y > n ? "False" : "True");
#endif
	REP(i, 1, n)
		if (blg[i] == blg[i + n])
		{
			puts("IMPOSSIBLE");
			return 0;
		}
	puts("POSSIBLE");
	REP(i, 1, n)
		printf("%d%c", blg[i] < blg[i + n], i == n ? '\n' : ' ');
	return 0;
}
