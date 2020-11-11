#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <vector>
#include <set>
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn];

multiset <i64, greater <i64> > s[maxn];

int allnode, rt;
int siz[maxn], Max[maxn];
bool vis[maxn];
void findrt(int x, int fa = 0)
{
	siz[x] = 1;Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
	{
		findrt(to[i], x);
		siz[x] += siz[to[i]];
		Max[x] = max(Max[x], siz[to[i]]);
	}
	Max[x] = max(Max[x], allnode - siz[x]);
	if (Max[x] < Max[rt] || !rt) rt = x;
}
int dep[maxn], stk[maxn], mina[maxn], top;
void dfs2(int x, int fa = 0)
{
	stk[++top] = x;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
	{
		mina[to[i]] = min(mina[x], a[to[i]]);
		dep[to[i]] = dep[x] + 1;
		dfs2(to[i], x);
	}
}
void calc(int x, int A, int d, int flag)
{
	top = 0;
	dep[x] = d;
	mina[x] = A;
	dfs2(x);
	sort(stk + 1, stk + 1 + top, [&](int x, int y) {return mina[x] < mina[y];});
	static int sd[maxn];
	sd[top] = dep[stk[top]];
	DEP(i, top - 1, 1) sd[i] = max(sd[i + 1], dep[stk[i]]);
	REP(i, 1, top)
	{
		int u = stk[i];
		REP(j, 1, top)
		{
			int v = stk[j];
			i64 val = (dep[u] + dep[v] + 1ll) * min(mina[u], mina[v]);
			if (flag > 0)
				s[u].emplace(val);
			else
			{
				auto it = s[u].find(val);
				if (it != s[u].end()) s[u].erase(it);
			}
		}
	}
}
void dfs(int x)
{
	vis[x] = 1;
	calc(x, a[x], 0, 1);
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
	{
		calc(to[i], min(a[x], a[to[i]]), 1, -1);
		allnode = siz[to[i]];
		rt = 0;
		findrt(to[i]);
		dfs(rt);
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	allnode = n;
	findrt(1);
	dfs(rt);
	REP(i, 1, n) printf("%lld%c", *s[i].begin(), i == end_i ? '\n' : ' ');
	return 0;
}
