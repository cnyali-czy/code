/*
	Problem:	A.cpp
	Time:		2020-05-19 19:34
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <queue>
#include <ctime>
#include <cassert>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
inline void chkmax(i64 &x, i64 y) {if (x < y) x = y;}

using namespace std;
const int maxn = 150000 + 10, maxq = maxn;

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, q, a[maxn], b[maxn];

int blg[maxn], L[maxn], R[maxn], block;
i64 ans[maxq];

namespace Structure
{
	struct Query
	{
		int l, r, L, R, id;
		Query() {}
		Query(int l, int r, int L, int R, int id) : l(l), r(r), L(L), R(R), id(id) {}
		inline bool operator < (const Query &B) const {	return r < B.r;	}
	};
}
vector <Structure :: Query> V[maxn];

namespace RMQ
{
	i64 bst[maxn], cur[maxn];
	inline void add(int x, int y)
	{
		cur[x] += y;
		chkmax(bst[blg[x]], cur[x]);
	}
	i64 Query(int l, int r)
	{
		i64 ans = 0;
		if (r - l + 1 <= block)
		{
			REP(i, l, r) chkmax(ans, cur[i]);
			return ans;
		}
		int bl = blg[l], br = blg[r];
		REP(i, l, R[bl]) chkmax(ans, cur[i]);
		REP(i, L[br], r) chkmax(ans, cur[i]);
		REP(i, bl + 1, br - 1) chkmax(ans, bst[i]);
		return ans;
	}
};
inline void opt(int i) {RMQ :: add(a[i], b[i]);}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();q = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, n) b[i] = read<int>();
	int N = max(n, m);
	block = max(5., .5 * (m + n) / sqrt(q));
	REP(i, 1, N) blg[i] = (i - 1) / block + 1;
	REP(i, 1, N) R[blg[i]] = i;
	DEP(i, N, 1) L[blg[i]] = i;
	REP(i, 1, q)
	{
		int l(read<int>()), r(read<int>()), L(read<int>()), R(read<int>());
		if (r - l + 1 <= block)
		{
			REP(j, l, r) RMQ :: cur[a[j]] += b[j];
			REP(j, l, r) if (L <= a[j] && a[j] <= R)
				chkmax(ans[i], RMQ :: cur[a[j]]);
			REP(j, l, r) RMQ :: cur[a[j]] -= b[j];
		}
		else V[blg[l]].emplace_back(l, r, L, R, i);
	}
	int tot = blg[n];
	REP(i, 1, tot) if (V[i].size())
	{
		sort(V[i].begin(), V[i].end());
		int curr = R[i];
		for (auto j : V[i])
		{
			while (curr < j.r) opt(++curr);
			ans[j.id] = RMQ :: Query(j.L, j.R);
			REP(k, j.l, R[i]) RMQ :: cur[a[k]] += b[k];
			REP(k, j.l, R[i]) if (j.L <= a[k] && a[k] <= j.R) chkmax(ans[j.id], RMQ :: cur[a[k]]);
			REP(k, j.l, R[i]) RMQ :: cur[a[k]] -= b[k];
		}
		REP(j, R[i], curr)
		{
			RMQ :: cur[a[j]] = 0;
			RMQ :: bst[blg[a[j]]] = 0;
		}
	}
	REP(i, 1, q) cout << ans[i] << '\n';
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
