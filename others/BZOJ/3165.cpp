#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <cassert>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxN = 40000 << 2;

template <typename T> T read()
{
	register T ans(0), flag(1);
	register char c(getchar());
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

inline void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, m, lastans;
pair <long double, long double> Line[maxn];

int ssr1[maxn], ssr2[maxn];

int e[maxN];
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

const long double eps = 1e-10;
inline int gank(const long double &qaq) {return (qaq > eps) - (qaq < -eps);}

inline long double f(int id, int x)
{
	if (!id || x < ssr1[id] || x > ssr2[id]) return 0;
	return Line[id].first * x + Line[id].second;
}

void insert(int p, int l, int r, int L, int R, int id)
{
	if (L <= l && r <= R)
		if (!e[p]) e[p] = id;
		else
		{
			long double me = f(id, mid), hh_val = f(e[p], mid);
			switch (gank(me - hh_val))
			{
				case 1:
					if (l ^ r)
						switch (gank(Line[id].first - Line[e[p]].first))
						{
							case 1:
								insert(lson, L, R, e[p]);
								break;
							case -1:
								insert(rson, L, R, e[p]);
								break;
						}
					e[p] = id;
					break;
				case 0:
					if (l ^ r)
						switch (gank(Line[id].first - Line[e[p]].first))
						{
							case 1:
								insert(rson, L, R, e[p]);
								break;
							case -1:
								insert(lson, L, R, e[p]);
								break;
						}
					chkmin(e[p], id);
					break;
				case -1:
					if (l ^ r)
						switch (gank(Line[id].first - Line[e[p]].first))
						{
							case 1:
								insert(rson, L, R, id);
								break;
							case -1:
								insert(lson, L, R, id);
								break;
						}
					break;
			}
		}
	else
	{
		if (L <= mid)	insert(lson, L, R, id);
		if (R >  mid)	insert(rson, L, R, id);
	}
}
int query(int p, int l, int r, int x)
{
	if (l == r) return e[p];
	else
	{
		long double me = f(e[p], x), hh_val;
		int hh_id;
		if (x <= mid)	hh_val = f(hh_id = query(lson, x), x);
		else			hh_val = f(hh_id = query(rson, x), x);
		switch (gank(me - hh_val))
		{
			case 1:
				hh_id = e[p];
				break;
			case 0:
				if (e[p]) chkmin(hh_id, e[p]);
				break;
		}
		return hh_id;
	}
}

int main()
{
#ifdef CraZYali
	file("3165");
#endif
	register int T = read<int>();
	while (T--)
		if (!read<int>())
		{
			int x = (read<int>() + lastans - 1) % 39989 + 1;
			printf("%d\n", lastans = query(1, 1, 39989, x));
		}
		else
		{
			++m;
			register int x0 = (read<int>() + lastans - 1) % 39989 + 1;
			register int y0 = (read<int>() + lastans - 1) % 1000000000 + 1;
			register int x1 = (read<int>() + lastans - 1) % 39989 + 1;
			register int y1 = (read<int>() + lastans - 1) % 1000000000 + 1;

			if (x0 > x1) swap(x0, x1), swap(y0, y1);
			if (x0 == x1) Line[m] = make_pair(0, max(y0, y1));
			else
			{
				register long double k = 1. * (y0 - y1) / (x0 - x1);
				register long double b = y1 - k * x1;
				Line[m] = make_pair(k, b);
			}
			ssr1[m] = x0;
			ssr2[m] = x1;
			insert(1, 1, 39989, x0, x1, m);
		}
	return 0;
}
