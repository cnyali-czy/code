/*
	Problem:	2171.cpp
	Time:		2021-04-23 15:44
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10;
const i64 inf = 1e18;

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

int n, e;
i64 t, x[maxn], f[maxn];

struct SMT
{
	i64 Min[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
	void update(int p, int l, int r, int pos, i64 val)
	{
		if (l == r) Min[p] = val;
		else
		{
			if (pos <= mid) update(lson, pos, val);
			else update(rson, pos, val);
			Min[p] = min(Min[ls], Min[rs]);
		}
	}
	i64 query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return Min[p];
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return min(query(lson, L, R), query(rson, L, R));
		}
	}
}s1, s2;

int main()
{
#ifdef CraZYali
	file("2171");
#endif
	cin >> n >> e >> t;
	REP(i, 1, n) x[i] = read<i64>();
	int k = 1;
	s1.update(1, 0, n, 0, -2 * x[1]);
	REP(i, 1, n)
	{
		i64 res = inf;
		while (k <= i && 2 * (x[i] - x[k]) > t) k++;

		//\forall k to i , 2 (x[i] - x[k]) <= t
//		REP(j, 1, k - 1)
//			res = min(res, f[j - 1] + 2 * (x[i] - x[j]));
		if (1 <= k - 1) res = min(res, s1.query(1, 0, n, 0, k - 2) + 2 * x[i]);
//		REP(j, k, i)
//			res = min(res, f[j - 1] + t);
		if (k <= i) res = min(res, s2.query(1, 0, n, k - 1, i - 1) + t);
		f[i] = res;
		s1.update(1, 0, n, i, res - 2 * x[i + 1]);
		s2.update(1, 0, n, i, res);
//		f[i] = res;
	}
	cout << f[n] + (e) << '\n';
	return 0;
}
