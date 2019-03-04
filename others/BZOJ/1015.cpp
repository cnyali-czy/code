#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 400000 + 10, maxm = 400000 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, k, t[maxn], ans[maxn];
bool forbid[maxn];

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
int cnt;
void uni(int x, int y)
{
	if (find(x) == find(y)) return;
	cnt--;
	fa[find(x)] = find(y);
}

int main()
{
#ifdef CraZYali
	freopen("1015.in", "r", stdin);
	freopen("1015.ans", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) fa[i] = i;
	REP(i, 1, m)
	{
		int x = read<int>() + 1, y = read<int>() + 1;
		add(x, y);add(y, x);
	}
	cin >> k;
	REP(i, 1, k) forbid[t[i] = read<int>() + 1] = 1;
	REP(x, 1, n) if (!forbid[x])
		for (int i = bg[x]; i ; i = ne[i])
			if (!forbid[to[i]]) uni(x, to[i]);
	cnt = 0;
	REP(i, 1, n) if (!forbid[i] && find(i) == i) cnt++;
	DREP(I, k, 1)
	{
		ans[I] = cnt++;
		forbid[t[I]] = 0;
		for (int i = bg[t[I]] ; i ; i = ne[i])
			if (!forbid[to[i]]) uni(t[I], to[i]);
	}
	printf("%d\n", cnt);
	REP(i, 1, k) printf("%d\n", ans[i]);
	return 0;
}
