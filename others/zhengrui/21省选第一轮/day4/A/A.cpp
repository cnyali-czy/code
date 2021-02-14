#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <queue>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 5e5 + 10;

int n, k, a[maxn], b[maxn];

int read()
{
	int res = 0, flg = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flg = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		res = res * 10 + (c - 48);
		c = getchar();
	}
	return res * flg;
}
int f[maxn], g[maxn];

#define pii pair <int, int>
#define fi first
#define se second
priority_queue <pii > que;

signed main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	n = read();k = read();
	REP(i, 1, n) a[i] = read();
	REP(i, 1, n) b[i] = read();
	int ans = 0;
	REP(i, 1, n) if (a[i] > 0) ans += a[i], a[i] = 0;
	REP(i, 1, n) if (b[i] > 0) ans += b[i], b[i] = 0;
	f[1] = g[1] = a[1] + b[1];
	int t1 = 1, t2 = 1;
	que.emplace(f[1], 1);
	que.emplace(g[1], -1);
	while (que.size())
	{
		int x = que.top().se;que.pop();
		if (x > 0)
		{
			REP(i, t1 + 1, min(n, x + k)) que.emplace(f[i] = g[x] + a[i], -i);
			t1 = max(t1, min(n, x + k));
		}
		else
		{
			x = -x;
			REP(i, t2 + 1, min(n, x + k)) que.emplace(g[i] = f[x] + b[i], i);
			t2 = max(t2, min(n, x + k));
		}
	}
	cout << ans + max(f[n] + b[n], g[n] + a[n]) << endl;

	return 0;
}
