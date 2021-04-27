#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int n, c[maxn];

int siz[maxn], hvy[maxn], dfn[maxn], back[maxn], dfs_clock;
void dfs0(int x, int fa = 0)
{
	siz[x] = 1;
	back[dfn[x] = ++dfs_clock] = x;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs0(to[i], x);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}

i64 s[maxn], cnt[maxn], mx;
inline void ins(int x)
{
	s[cnt[x]] -= x;
	s[++cnt[x]] += x;
	mx = max(mx, cnt[x]);
}
inline void del(int x)
{
	s[cnt[x]--] -= x;
	s[cnt[x]] += x;
	while (mx && !s[mx]) mx--;
}
i64 ans[maxn];

void dfs(int x, int fa = 0)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && to[i] ^ hvy[x])
	{
		dfs(to[i], x);
		REP(j, dfn[to[i]], dfn[to[i]] + siz[to[i]] - 1) del(c[back[j]]);
	}
	if (hvy[x]) dfs(hvy[x], x);
	ins(c[x]);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && to[i] ^ hvy[x])
		REP(j, dfn[to[i]], dfn[to[i]] + siz[to[i]] - 1) ins(c[back[j]]);
	ans[x] = s[mx];
}

int main()
{
#ifdef CraZYali
	freopen("E-new.in", "r", stdin);
	freopen("E-new.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%d", c + i);
	REP(i, 2, n)
	{
		int x, y;scanf("%d%d", &x, &y);
		add(x, y);add(y, x);
	}
	dfs0(1);dfs(1);
	REP(i, 1, n) printf("%lld%c", ans[i], i == end_i ? '\n' : ' ' );
	return 0;
}
