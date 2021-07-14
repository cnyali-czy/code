/*
	Problem:	C.cpp
	Time:		2021-07-13 08:30
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <random>
#include <ctime>
#define i64 long long
#define u64 unsigned i64
using namespace std;
const int maxn = 2e5 + 10;

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

mt19937 hh;
int n, x[maxn], y[maxn];

inline i64 sqr(i64 x) {return x * x;}
inline double dis(int x1, int y1, int x2, int y2)
{
	return sqrt(1ll * (x1 - x2) * (x1 - x2) + 1ll * (y1 - y2) * (y1 - y2));
}
inline i64 dis2(int x1, int y1, int x2, int y2)
{
	return 1ll * (x1 - x2) * (x1 - x2) + 1ll * (y1 - y2) * (y1 - y2);
}

namespace bf
{
	int main()
	{
		REP(i, 1, n)
		{
			double ans = 0;
			REP(j, 1, n) ans += dis(x[i], y[i], x[j], y[j]);
			printf("%.10lf\n", ans);
		}
		return 0;
	}
}

namespace cheat
{
	struct node
	{
		int x, y, id;
	}P[maxn];
	struct
	{
		int lx, rx, ly, ry;
	}t[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid - 1
#define rson rs, mid + 1, r

	const unsigned unsigned_LIM = -1;
	inline double rand_double()
	{
		return (double)hh() / unsigned_LIM;
	}
	inline i64 rand_i64(i64 l, i64 r)
	{
		return l + (r - l) * rand_double();
	}
	inline void chkmax(int &x, int y) {if (x < y) x = y;}
	inline void chkmin(int &x, int y) {if (x > y) x = y;}
	void build(int p, int l, int r, int flg = 0)
	{
		if (l > r) return;
		if (flg) sort(P + l, P + r + 1, [&](node x, node y) {return x.x < y.x;});
		else	 sort(P + l, P + r + 1, [&](node x, node y) {return x.y < y.y;});
		t[p].lx = t[p].rx = P[mid].x;
		t[p].ly = t[p].ry = P[mid].y;
		if (l == r) return;
		if (l < mid)
		{
			build(lson, !flg);
			chkmin(t[p].lx, t[ls].lx);chkmax(t[p].rx, t[ls].rx);
			chkmin(t[p].ly, t[ls].ly);chkmax(t[p].ry, t[ls].ry);
		}
		if (mid < r)
		{
			build(rson, !flg);
			chkmin(t[p].lx, t[rs].lx);chkmax(t[p].rx, t[rs].rx);
			chkmin(t[p].ly, t[rs].ly);chkmax(t[p].ry, t[rs].ry);
		}
	}
	int o;
	int query(int p, int l, int r, i64 rr)
	{
		if (dis2(x[o], y[o], t[p].lx, t[p].ly) < rr && 
			dis2(x[o], y[o], t[p].lx, t[p].ry) < rr && 
			dis2(x[o], y[o], t[p].rx, t[p].ly) < rr &&
			dis2(x[o], y[o], t[p].rx, t[p].ry) < rr) return r - l + 1;
		
		int res = (dis2(x[o], y[o], P[mid].x, P[mid].y) < rr);
		if (l < mid) res += query(lson, rr);
		if (mid < r) res += query(rson, rr);
		return res;
	}
	inline int f(i64 rr)
	{
		return n - query(1, 1, n, rr);
	}
	double ans;

#undef mid
	const double eps = 1e-5;
	inline double h(int fl, int fr, double sl, double sr)
	{
		return (fr + fl) * (sr - sl) / 2;
	}
	void work(i64 l, i64 r, int fl, int fr, double sl, double sr, int flr = 0)
	{
		if (flr == 10)
		{
			ans += h(fl, fr, sl, sr);
			return;
		}
		i64 L = l, R = r - 1, gd = (l + r >> 1);
//		while (gd + 1 < r && f(gd) == fl)
//			gd = (gd + r >> 1);
		i64 mid = gd;
	
		int v1 = f(mid), v2 = f(mid + 1);
		double s1 = sqrt(mid), s2 = sqrt(mid + 1);

		work(l, mid, fl, v1, sl, s1, flr + 1);
		work(mid + 1, r, v2, fr, s2, sr, flr + 1);
	}
	int main()
	{
		REP(i, 1, n) P[i] = {x[i], y[i], i};
		build(1, 1, n);
//		const i64 lim = sqr(t[1].rx - t[1].lx) + sqr(t[1].ry - t[1].ly);
//		const double slim = sqrt(lim);
		static int id[maxn];
		REP(i, 1, n) id[i] = i;
		REP(i, 1, n)
		{
			ans = 0;
			int T = 10000;
			REP(j, 1, T)
			{
				int k = hh() % n + 1;
				ans += dis(x[i], y[i], x[k], y[k]);
			}
			printf("%.10lf\n", ans + ans / T * (n - T));
			//			work(1, lim, f(1), f(lim), 1, slim);
			//			printf("%.10lf\n", ans);
		}
		cerr << clock() * 1. / CLOCKS_PER_SEC << '\n';
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	srand(time(0));
	hh = mt19937(rand());
	n = read<int>();
	REP(i, 1, n) x[i] = read<int>(), y[i] = read<int>();
	if (0 && n <= 3000) return bf :: main();
	return cheat :: main();
}
