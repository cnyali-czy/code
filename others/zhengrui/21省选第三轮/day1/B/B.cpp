#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10, inf = 1e9 + 5;

int n, a[maxn], b[maxn], c[maxn];
inline bool chkmin(int &x, int y) {if (x > y) {x = y;return 1;}return 0;}
i64 ans;
#define fi first
#define se second
#define mp make_pair

pair <pair <int, int>, int> P[maxn];

inline bool cmp(pair <int, int> A, pair <int, int> B) {return A.fi <= B.fi && A.se <= B.se;}

namespace fenwick
{
	i64 s1[maxn], s2[maxn];
	int dfn[maxn], dfs_clock;
	void clear() {dfs_clock++;}
	void add(int x, int y)
	{
		while (x > 0)
		{
			if (dfn[x] ^ dfs_clock)
			{
				dfn[x] = dfs_clock;
				s1[x] = s2[x] = 0;
			}
			s1[x]++;
			s2[x] += y;
			x &= (x - 1);
		}
	}
	pair <i64, i64> sum(int x)
	{
		i64 y1 = 0, y2 = 0;
		while (x <= n)
		{
			if (dfn[x] == dfs_clock)
			{
				y1 += s1[x];
				y2 += s2[x];
			}
			x += x & -x;
		}
		return mp(y1, y2);
	}
}

void work(int l, int r, int fx, int fy)
{
	int mid = l + r >> 1;
	REP(i, mid + 1, r)
	{
		P[i].fi.fi *= -1;
		P[i].fi.se *= -1;
	}
	REP(i, l, mid) P[i].fi.fi += fx, P[i].fi.se += fy;

	sort(P + l, P + mid + 1);
	sort(P + mid + 1, P + r + 1);

	static int b[maxn];int m = 0;
	REP(i, mid + 1, r) b[++m] = P[i].fi.se;
	sort(b + 1, b + 1 + m);m = unique(b + 1, b + 1 + m) - b - 1;

	fenwick :: clear();
	int j = r + 1;
	DEP(i, mid, l)
	{
		while (j > mid + 1 && P[i].fi.fi <= P[j - 1].fi.fi)
		{
			j--;
			int pos = lower_bound(b + 1, b + 1 + m, P[j].fi.se) - b;
			fenwick :: add(pos, P[j].se);
		}
		/*
		REP(k, j, r) if (P[i].fi.se <= P[k].fi.se)
		{
			ans += P[i].se + P[k].se;
		}*/
		auto res = fenwick :: sum(lower_bound(b + 1, b + 1 + m, P[i].fi.se) - b);
		ans += P[i].se * res.fi + res.se;
	}
}
void cdq(int l, int r)
{
	if (r - l + 1 <= 10)
	{
		static int f[maxn];
		REP(i, l, r)
		{
			REP(j, i, r) f[j] = inf;
			f[i] = 0;
			REP(j, i, r)
			{
				chkmin(f[j + 1], f[j] + a[j]);
				chkmin(f[j + 2], f[j] + b[j]);
				chkmin(f[j + 3], f[j] + c[j]);
				ans += f[j];
			}
		}
		return ;
	}
	int mid = l + r >> 1;
	cdq(l, mid);cdq(mid + 1, r);

	static int f[maxn][3];
	REP(i, l, r + 5) f[i][0] = f[i][1] = f[i][2] = inf;
	//0 : mid
	//1 : mid - 1
	//2 : mid - 2
	f[mid][0] = 0;f[mid - 1][1] = 0;f[mid - 2][2] = 0;
	/*
	   f[mid - 1][0] = a[mid - 1];f[mid - 1][1] = 0;
	   f[mid - 2][0] = min(a[mid - 2] + a[mid - 1], b[mid - 2]);
	   f[mid - 2][1] = a[mid - 2];f[mid - 2][2] = 0;
	 */

	DEP(i, mid, l) REP(k, 0, 2)
	{
		chkmin(f[i][k], f[i + 1][k] + a[i]);
		chkmin(f[i][k], f[i + 2][k] + b[i]);
		chkmin(f[i][k], f[i + 3][k] + c[i]);
	}
	REP(i, mid - 2, r) REP(k, 0, 2) if (mid - k <= i)
	{
		if (i + 1 > mid) chkmin(f[i + 1][k], f[i][k] + a[i]);
		if (i + 2 > mid) chkmin(f[i + 2][k], f[i][k] + b[i]);
		if (i + 3 > mid) chkmin(f[i + 3][k], f[i][k] + c[i]);
	}

	/*
	   REP(i, l, mid) REP(j, mid + 1, r)
	   {
	   int res = inf;
	   REP(k, 0, 2) chkmin(res, f[i][k] + f[j][k]);
	   ans += res;
	   }
	 */

	REP(i, l, r) P[i] = mp(mp(f[i][0] - f[i][1], f[i][0] - f[i][2]), f[i][0]);
	work(l, r, 0, 0);
	REP(i, l, r) P[i] = mp(mp(f[i][1] - f[i][0], f[i][1] - f[i][2]), f[i][1]);
	work(l, r, 1, 0);
	REP(i, l, r) P[i] = mp(mp(f[i][2] - f[i][0], f[i][2] - f[i][1]), f[i][2]);
	work(l, r, 1, 1);
}

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	int T;cin >> T;
	while (T--)
	{
		scanf("%d", &n);
		REP(i, 1, n - 1) scanf("%d", a + i);
		REP(i, 1, n - 2) scanf("%d", b + i);
		REP(i, 1, n - 3) scanf("%d", c + i);
		ans = 0;
		cdq(1, n);

		printf("%lld\n", ans);
	}
	return 0;
}
