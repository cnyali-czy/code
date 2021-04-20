/*
	Problem:	7514.cpp
	Time:		2021-04-16 08:59
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10, inf = 1e9;

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

int n, m, a[maxn][2], A[maxn << 1], N;

namespace SMT
{
	const int maxN = 3e7;
	int ls[maxN], rs[maxN], s[maxN], cur;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
	void ins(int pre, int &p, int l, int r, int pos)
	{
		p = ++cur;
		ls[p] = ls[pre];
		rs[p] = rs[pre];
		s[p] = s[pre] + 1;
		if (l == r) return ;
		if (pos <= mid) ins(ls[pre], lson, pos);
		else ins(rs[pre], rson, pos);
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (!s[p]) return 0;
		if (L <= l && r <= R) return s[p];
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return query(lson, L, R) + query(rson, L, R);
		}
	}
	int query(int u, int v, int l, int r, int L, int R)
	{
		if (!s[u] && !s[v]) return 0;
		if (L <= l && r <= R) return s[u] - s[v];
		else
		{
			if (R <= mid) return query(ls[u], ls[v], l, mid, L, R);
			if (L >  mid) return query(rs[u], rs[v], mid + 1, r, L, R);
			return query(ls[u], ls[v], l, mid, L, R) + query(rs[u], rs[v], mid + 1, r, L, R);
		}
	}
}

int rt[maxn << 2], id[maxn][2], ans = inf;
int judge(int Mi, int Mx)
{
	int need = (A[Mi] & 1) + (A[Mx] & 1), mi = a[A[Mi] >> 1][A[Mi] & 1], mx = a[A[Mx] >> 1][A[Mx] & 1];
	need += SMT :: s[rt[Mi - 1]];
	need += SMT :: s[rt[n + n]] - SMT :: s[rt[Mx]];
	if (need > m) return inf + 5;
	//	REP(k, 1, n) if (id[k][0] < Mi && id[k][1] < Mi) return inf + 5;
	//	REP(k, 1, n) if (id[k][0] < Mi && id[k][1] > Mx) return inf + 5;
	//	REP(k, 1, n) if (id[k][0] > Mx && id[k][1] < Mi) return inf + 5;
	//	REP(k, 1, n) if (id[k][0] > Mx && id[k][1] > Mx) return inf + 5;
	if (SMT :: query(rt[Mi - 1], 0, N, 0, Mi - 1)) return inf + 5;
	if (SMT :: query(rt[Mi - 1], 0, N, Mx + 1, N)) return inf + 5;
	if (SMT :: query(rt[n + n], rt[Mx], 0, N, 0, Mi - 1)) return inf + 5;
	if (SMT :: query(rt[n + n], rt[Mx], 0, N, Mx + 1, N)) return inf + 5;

	//	REP(k, 1, n) if (id[k][0] < Mi) need++;
	//	REP(k, 1, n) if (id[k][0] > Mx) need++;
	return need <= m ? mx - mi : inf + 5;
}

int main()
{
#ifdef CraZYali
	file("7514");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) a[i][0] = read<int>();
	REP(i, 1, n) a[i][1] = read<int>();
	REP(i, 1, n) A[i] = i << 1, A[i + n] = i << 1 | 1;
	sort(A + 1, A + 1 + n + n, [&](int x, int y) {return a[x >> 1][x & 1] < a[y >> 1][y & 1];});
	REP(i, 1, n + n) id[A[i] >> 1][A[i] & 1] = i;
	N = n + n + 2;
	REP(k, 1, n + n)
	{
		rt[k] = rt[k - 1];
		if (!(A[k] & 1)) SMT :: ins(rt[k], rt[k], 0, N, id[A[k] >> 1][1]);
	}

	int Mx = n + n, tmp;
	DEP(Mi, n + n - 1, 1)
	{
		while (Mi < Mx - 1 && (tmp = judge(Mi, Mx - 1)) < inf)
		{
			ans = min(ans, tmp);
			Mx--;
		}
	}
	cout << ans << endl;
	return 0;
}
