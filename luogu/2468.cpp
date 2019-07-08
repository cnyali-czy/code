#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int P = 1000, maxp = P + 5;

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

int r, c, m, n;

#define mid (l + r >> 1)

namespace small
{
	const int maxr = 200 + 5, maxc = 200 + 5;
	int a[maxr][maxc], cnt[maxp][maxr][maxc], cnts[maxp][maxr][maxc], sum[maxp][maxr][maxc];
	int s(int x1, int y1, int x2, int y2, int x, int a[maxp][maxr][maxc]) {return a[x][x2][y2] - a[x][x1-1][y2] - a[x][x2][y1-1] + a[x][x1-1][y1-1];}
	void work()
	{
		REP(i, 1, r)
			REP(j, 1, c)
			a[i][j] = read<int>();
		REP(k, 1, P)
			REP(i, 1, r)
			REP(j, 1, c)
			cnt[k][i][j] = cnt[k][i][j-1] + cnt[k][i-1][j] - cnt[k][i-1][j-1] + (a[i][j] == k);
		DREP(k, P, 1)	
			REP(i, 1, r)
			REP(j, 1, c)
			cnts[k][i][j] = cnts[k+1][i][j] + cnt[k][i][j];
		DREP(k, P, 1)
			REP(i, 1, r)
			REP(j, 1, c)
			sum[k][i][j] = sum[k+1][i][j] + k * cnt[k][i][j];
		while (m--)
		{
			int x1(read<int>()), y1(read<int>()), x2(read<int>()), y2(read<int>()), h(read<int>());
			int l = 1, r = 1000, ans = 1001;
			while (l <= r)
				if (s(x1, y1, x2, y2, mid, sum) >= h)
				{
					ans = mid;
					l = mid + 1;
				}
				else r = mid - 1;
			if (ans == 1001) printf("Poor QLW\n");
			else
			{
				int part1 = s(x1, y1, x2, y2, ans + 1, cnts);
				h -= s(x1, y1, x2, y2, ans + 1, sum);
				printf("%d\n", part1 + h / ans + (h % ans != 0));
			}
		}
	}
}

namespace president
{
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
	const int maxn = 500000 + 10, n_log_n = 9465800;
	int a[maxn], b[maxn], len;

	int rt[maxn], ls[n_log_n], rs[n_log_n], sum[n_log_n], cnt[n_log_n], cur;
	void build(int pre, int &p, int l, int r, int pos)
	{
		p = ++cur;
		ls[p] = ls[pre];
		rs[p] = rs[pre];
		cnt[p] = cnt[pre] + 1;
		sum[p] = sum[pre] + b[pos];
		if (l == r) return;
		if (pos <= mid) build(ls[pre], lson, pos);
		else build(rs[pre], rson, pos);
	}

	int query(int u, int v, int l, int r, int h)
	{
		if (l == r) return l;
		int x = sum[rs[v]] - sum[rs[u]];
		if (x >= h) return query(rs[u], rs[v], mid + 1, r, h);
		else return query(ls[u], ls[v], l, mid, h - x);
	}
	int count(int u, int v, int l, int r, int pos)
	{
		if (l >= pos) return cnt[v] - cnt[u];
		if (r < pos) return 0;
		else return count(ls[u], ls[v], l, mid, pos) + count(rs[u], rs[v], mid + 1, r, pos);
	}
	int tot(int u, int v, int l, int r, int pos)
	{
		if (l >= pos) return sum[v] - sum[u];
		if (r < pos) return 0;
		else return tot(ls[u], ls[v], l, mid, pos) + tot(rs[u], rs[v], mid + 1, r, pos);
	}

	void work()
	{
		REP(i, 1, n) a[i] = b[i] = read<int>();
		sort(b + 1, b + 1 + n);
		len = unique(b + 1, b + 1 + n) - b - 1;
		REP(i, 1, n) build(rt[i-1], rt[i], 1, len, lower_bound(b + 1, b + 1 + len, a[i]) - b);
		while (m--)
		{
			read<int>();int L(read<int>());	read<int>();int R(read<int>());	int h(read<int>());
//			fputs("------", stderr);
//			cout << h << endl;
//			REP(i, L, R) fprintf(stderr, "%d%c", a[i], i == R ? '\n' :' ');
			if (sum[rt[R]] - sum[rt[L-1]] < h)
			{
				printf("Poor QLW\n");
				continue;
			}
			int k = query(rt[L-1], rt[R], 1, len, h);
//			cerr << b[k] << ' ' << count(rt[L-1], rt[R], 1, len, k) << endl;
			int part1 = count(rt[L-1], rt[R], 1, len, k + 1);
			h -= tot(rt[L-1], rt[R], 1, len, k + 1);
			printf("%d\n", part1 + h / b[k] + (h % b[k] != 0));
		}
	}
}

int main()
{
#ifdef CraZYali
	file("2468");
#endif
	cin >> r >> c >> m;n = c;
	if (r == 1) president::work();
	else small::work();
	return 0;
}
