#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmin(a, b) (a > (b) ? a = (b) : a)
#define chkmax(a, b) (a < (b) ? a = (b) : a)

#include <algorithm>
#include <cstdio>
#include <iostream>
#define i64 long long

using namespace std;
const int maxn = 1000 + 10;
const i64 inf = 0x7f7f7f7f7f7f7f7fll;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if(c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void exgcd(int a, int b, int &x, int &y)
{
	if (!b)
	{
		x = 1;y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
inline int inv(int a, int m)
{
	a = (a % m + m) % m;
	int x, y;
	exgcd(a, m, x, y);
	return (x % m + m) % m;
}
int find(int m, int s, int p, int w)
{
	if (p < w) return p;
	if (!s) return -1;
	if (p >= s)
	{
		int g = (m - 1 - p) / s;
		p = p + (g + 1) * s - m;
	}
	if (p < w) return p;
	int ns = m % s;
	int np = w + (s - 1 - p);
	int x = find(s, ns, np, w);
	return (x == -1 ? -1 : w - 1 - x);
}
int calc(int m, int p, int s, int l, int r)
{
	p = (p + m - l) % m;
	int w = find(m, s, p, r - l + 1);
	if (w == -1)
		return -1;
	int A = (w - p + m) % m, B = s, C = m;
	int d = __gcd(B, C);
	A /= d, B /= d, C /= d;
	return int(1ll * A * inv(B, C) % C);
}
int w, h, n, x[maxn], y[maxn];

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout) 

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	w = read<int>();h = read<int>();
	n = read<int>();
	REP(i, 0, n - 1) x[i] = read<int>(), y[i] = read<int>();
	register int T = read<int>();
	while (T--)
	{
		int xs(read<int>()), ys(read<int>());
		i64 ans = inf;
		REP(rx, 0, 1)
		{
			REP(ry, 0, 1)
			{
				REP(t, 0, 1)
				{
					REP(i, 0, n - 1)
						if (x[i] == x[(i + 1) % n])
						{
							int l = y[i];
							int r = y[(i + 1) % n];
							if (l > r) swap(l, r);
							int t = (x[i] - xs + 2 * w) % (2 * w);
							int p = (ys + t) % (2 * h);
							int s = (2 * w) % (2 * h);
							int c = calc(2 * h, p, s, l, r);
							if (c != -1) chkmin(ans, 2ll * w * c + t);
						}
					REP(i, 0, n - 1) swap(x[i], y[i]);
					swap(xs, ys);
					swap(w, h);
				}
				REP(i, 0, n - 1) y[i] = h + h - y[i];
			}
			REP(i, 0, n - 1) x[i] = w + w - x[i];
		}
		if (ans == inf) puts("-1");
		else
		{
			int xf = (xs + ans) % (2 * w);
			int yf = (ys + ans) % (2 * h);
			if (xf >= w) xf = w + w - xf;
			if (yf >= h) yf = h + h - yf;
			printf("%lld %d %d\n", ans, xf, yf);
		}
	}
	return 0;
}
