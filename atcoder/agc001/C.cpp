#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2000 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int n, k, u[maxn], v[maxn];

int c;
void dfs(int x, int fa, int d = 0)
{
	c++;
	if (d == k / 2) return;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		dfs(to[i], x, d + 1);
}

int main()
{
#ifdef CraZYali
	freopen("1981.in", "r", stdin);
	freopen("1981.out", "w", stdout);
#endif
	cin >> n >> k;
	REP(i, 1, n - 1)
	{
		scanf("%d%d", u + i, v + i);
		add(u[i], v[i]);add(v[i], u[i]);
	}
	int ans = n;
	if (k & 1)
		REP(i, 1, n - 1)
		{
			c = 0;
			dfs(u[i], v[i]);
			dfs(v[i], u[i]);
			ans = min(ans, n - c);
		}
	else
		REP(i, 1, n)
		{
			c = 0;
			dfs(i, 0);
			ans = min(ans, n - c);
		}
	cout << ans << endl;
	return 0;
}
