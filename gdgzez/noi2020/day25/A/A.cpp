#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <queue>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;

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

int n, m, type;

int fa[maxn], siz[maxn], edg[maxn];
bool need;
bool ins[maxn];
struct info
{
	int x, fa, siz, edg;
	info() {}
	info(int id)
	{
		x = id;
		fa = ::fa[x];
		siz = ::siz[x];
		edg = ::edg[x];
	}
}ssr[maxn];
void restore(info x)
{
	fa[x.x] = x.fa;
	siz[x.x] = x.siz;
	edg[x.x] = x.edg;
	ins[x.x] = 0;
}
int N;

int ans, lastans;

int find(int x)
{
	if (need && !ins[x])
	{
		ins[x] = 1;
		ssr[++N] = x;
	}
	return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
}
void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (siz[x] < siz[y]) swap(x, y);
	if (need && !ins[x])
	{
		ins[x] = 1;
		ssr[++N] = x;
	}
	if (x == y)
	{
		edg[x]++;
		if (edg[x] == siz[x]) ans++;
	}
	else
	{
		if (edg[x] + 1 == siz[x] || edg[y] + 1 == siz[y]) ans++;
		fa[y] = x;
		siz[x] += siz[y];
		edg[x] += edg[y] + 1;
	}
}
pair <int, int> q1[maxn], q2[maxn];
int h1, t1, h2, t2;

int block;

void rebuild()
{
	int cnt = 0;
	ans = 0;
	h1 = 0;t1 = -1;
	while (h2 <= t2 && cnt < block)
	{
		q1[++t1] = q2[h2++];
		cnt++;
	}
	reverse(q1, q1 + t1 + 1);t1--;
	REP(i, 1, n) fa[i] = i, siz[i] = 1, edg[i] = 0;
	REP(i, h2, t2) uni(q2[i].first, q2[i].second);
}
void work()
{
	need = 1;
	REP(i, h1, t1) uni(q1[i].first, q1[i].second);
	need = 0;
	REP(i, 1, N) restore(ssr[i]);//restore();
	N = 0;
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();type = read<int>();
	REP(i, 1, n) fa[i] = i, siz[i] = 1;
	block = sqrt(m);
	t1 = -1;t2 = -1;
	REP(i, 1, m)
	{
		int opt = read<int>();
		if (type) opt = (opt + lastans) % 2;
		if (!opt)
			if (h1 <= t1) t1--;
			else rebuild();
		else
		{
			int a = read<int>(), b = read<int>();
			if (type) a = (a + lastans) % n + 1, b = (b + lastans) % n + 1;
			q2[++t2] = make_pair(a, b);
			uni(a, b);
		}
		int tmp = ans;
		work();
		printf("%d\n", lastans = ans);
		ans = tmp;
	}
	return 0;
}
