#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e5 + 10, inf = 1e15;

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

int n;
pair <int, int> p[maxn];
#define x first
#define y second
int d[2005][2005];
int fa[maxn], siz[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (x == y) return;
	fa[x] = y;
	siz[y] += siz[x];
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		int tx = read<int>(), ty = read<int>();
		p[i] = make_pair(tx + ty, tx - ty);
	}
	REP(i, 1, n) siz[fa[i] = i] = 1;
	REP(i, 1, n) REP(j, i + 1, n)
	{
		int dx = abs(p[i].x - p[j].x), dy = abs(p[i].y - p[j].y), cur = min(dx, dy);
		if (!cur) uni(i, j);
	}
	int Min = inf, cnt = 0;
	REP(i, 1, n) REP(j, 1, n) d[i][j] = inf;
	REP(i, 1, n) d[i][i] = 0;

	REP(i, 1, n) REP(j, 1, i - 1) if (find(i) != find(j))
	{
		int dx = abs(p[i].x - p[j].x), dy = abs(p[i].y - p[j].y), cur = min(dx, dy);
		int fi = find(i), fj = find(j);
		if (d[fi][fj] > cur)
		{
			d[fi][fj] = d[fj][fi] = cur;
			if (Min > cur) Min = cur, cnt = 0;
			if (Min == cur) cnt += 1ll * siz[fi] * siz[fj];
		}
	}
	if (!cnt)
	{
		puts("-1");
		return 0;
	}
	cout << Min << endl << cnt << endl;
	return 0;
}
