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
#include <queue>
#define int long long
using namespace std;
const int maxn = 1000 + 10, M = (int)2e9 + 10;

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

int m, n, k;
int r[maxn], c[maxn], a[maxn], b[maxn], p[maxn], g[maxn], G[maxn];

int f[M / 32];
priority_queue <pair <int, int > > q;
int at(int x, int i) {return x >> i & 1;}
bool in(int x, int y, int X, int Y) {return X % x == 0 && Y % x == 0 && (!y || (X % (x << 1)) == (Y % (x << 1)));}
signed main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		r[i] = read<int>();
		c[i] = read<int>();
		a[i] = read<int>();
		b[i] = read<int>();
		p[i] = read<int>();
		g[i] = __gcd(a[i], b[i]);
		a[i] /= g[i];b[i] /= g[i];
		G[i] = !((a[i] & 1) ^ (b[i] & 1));
	}
	int X = -r[1], Y = -c[1];
	if (!X && !Y) {puts("0");return 0;}
	REP(i, 1, n)
	{
		r[i] += X;c[i] += Y;
		if (!r[i] && !c[i]) q.emplace(-p[i], g[i] << 1 | G[i]);
	}
	while (!q.empty())
	{
		int c = -q.top().first, x = q.top().second;q.pop();
		if (at(f[x >> 5], x & 31)) continue;
		f[x >> 5] |= 1ll << (x & 31);
		int y = x & 1;x >>= 1;
		if (in(x, y, X, Y))
		{
			cout << c << endl;
			return 0;
		}
		REP(i, 1, n) if (in(x, y, r[i], ::c[i]))
		{
			int xx = __gcd(x, g[i]), yy;
			if (y && G[i]) yy = 1;
			else if (!y && !G[i]) yy = 0;
			else if (y) yy = __gcd(x * 2, g[i]) == xx ? 0 : 1;
			else yy = __gcd(g[i] * 2, x) == xx ? 0 : 1;
			int st = xx << 1 | yy;
			if (!at(f[st >> 5], st & 31)) q.emplace(-c - p[i], st);
		}
	}
	puts("-1");
	return 0;
}
