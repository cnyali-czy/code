/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.12 21:11
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxm = 1e5 + 10, maxN = 4e7;

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

struct brush
{
	int c, l, r;
	inline bool operator < (const brush &B) const {return r < B.r;}
}b[maxm];
int n, m, c[maxm], l[maxm], r[maxm];
long long x, y, ans, dp[maxm];

int ls[maxN], rs[maxN], rt_0, rt[2][4], cur;
long long Max[maxN], tag[maxN];
bool need[maxN];
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
const long long inf = 1e15;

void maintain(int &p, long long val)
{
	if (!p) Max[p = ++cur] = -inf, tag[p] = -inf;
	need[p] = 1;
	chkmax(Max[p], val);
	chkmax(tag[p], val);
}

void pushdown(int p, long long val)
{
	maintain(ls[p], val);
	maintain(rs[p], val);
	need[p] = 0;
	tag[p] = -inf;
}
inline long long mymax(long long x, long long y) {if (x > y) return x;return y;}
void update(int &p, int l, int r, int L, int R, long long val)
{
	if (!p) Max[p = ++cur] = -inf, tag[p] = -inf;
	if (L <= l && r <= R) maintain(p, val);
	else
	{
		if (need[p]) pushdown(p, tag[p]);
		if (L <= mid) update(lson, L, R, val);
		if (R >  mid) update(rson, L, R, val);
		Max[p] = mymax(ls[p] ? Max[ls[p]] : -inf , rs[p] ? Max[rs[p]] : -inf);
	}
}

long long query(int &p, int l, int r, int L, int R)
{
	if (!p) return -inf;
	if (L <= l && r <= R) return Max[p];
	else
	{
		if (need[p]) pushdown(p, tag[p]);
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return mymax(query(lson, L, R), query(rson, L, R));
	}
}
int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> m >> x >> y;
	REP(i, 1, m)
	{
		b[i].c = read<int>();
		b[i].l = read<int>();
		b[i].r = read<int>();
	}
	int rrt(0);
	sort(b + 1, b + 1 + m);
	REP(i, 1, m)
	{
		int c(b[i].c), l(b[i].l), r(b[i].r);
		dp[i] = mymax(0ll, l > 1 ? query(rt_0, 1, n, 1, l - 1) : 0) + x * (r - l + 1);
		REP(j, 1, 3)
			if (j == c)	chkmax(dp[i], x * r + query(rt[0][j], 1, n, l, l));
			else		chkmax(dp[i], x * r + (x + y) * (l - 1) + query(rt[1][j], 1, n, l, l));
		update(rt_0, 1, n, r, r, dp[i]);
		if (l < r) 
		{
			update(rt[0][c], 1, n, l + 1, r, dp[i] - r * x);
			update(rt[1][c], 1, n, l + 1, r, dp[i] - r * x - (x + y) * r);
		}
		/*
		   REP(j, 1, i - 1)
		   if (r[j] < l[i])	chkmax(dp[i], dp[j] + x * (r[i] - l[i] + 1));
		   else if (l[j] < l[i] && l[i] <= r[j])
		   if (c[j] == c[i])	chkmax(dp[i], dp[j] + x * (r[i] - r[j]));
		   else				chkmax(dp[i], dp[j] + x * (r[i] - r[j]) - (x + y) * (r[j] - l[i] + 1));
		   */
		chkmax(ans, dp[i]);
	}
	cout << ans << endl;
	return 0;
}
