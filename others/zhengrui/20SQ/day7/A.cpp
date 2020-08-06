/*
	Problem:	A.cpp
	Time:		2020-08-04 16:00
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10, maxN = 4e7, N = 40e4;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

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

int n, k;

int ls[maxN], rs[maxN], s[maxN], rt[maxn], tr[maxn], cur;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)

void insert(int &p, int l, int r, int pos)
{
	if (!p) p = ++cur;
	s[p]++;
	if (l == r) return;
	else if (pos <= mid)	insert(lson, pos);
	else					insert(rson, pos);
}

int query(int p, int l, int r, int L, int R)
{
	if (!p) return 0;
	if (L <= l && r <= R) return s[p];
	else
	{
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}

int fa[maxn], dep[maxn], wfa[maxn];
void dfs(int x)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		wfa[to[i]] = w[i];
		fa[to[i]] = x;
		dep[to[i]] = dep[x] + w[i];
		dfs(to[i]);
	}
	for (int l = x; l; l = fa[l])
	{
		insert(rt[l], 0, 2 * N, N + dep[x] - 2 * dep[l]);
		insert(tr[l], 0, 2 * N, N + dep[x] - 2 * dep[l] + 2 * wfa[l]);
	}
}

int top, stk[maxn << 1];

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();k = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>(), z = read<int>();
		add(x, y, z);add(y, x, z);
	}
	dfs(1);
	REP(i, 1, n)
	{
		top = 0;
		for (int l = i, s = 0; l; l = fa[s = l])
		{
			stk[++top] = rt[l];
			stk[++top] =-tr[s];
		}
		int l = 0, r = 2 * N, jjs = k;
		while (l ^ r)
		{
			int res_l = 0;
			REP(j, 1, top)
				if (stk[j] > 0)	res_l += s[ls[ stk[j]]];
				else			res_l -= s[ls[-stk[j]]];
			if (res_l >= jjs)
			{
				REP(j, 1, top)
					if (stk[j] > 0) stk[j] = ls[ stk[j]];
					else			stk[j] =-ls[-stk[j]];
				r = mid;
			}
			else
			{
				jjs -= res_l;
				REP(j, 1, top)
					if (stk[j] > 0) stk[j] = rs[ stk[j]];
					else			stk[j] =-rs[-stk[j]];
				l = mid + 1;
			}
		}
		printf("%d\n", l + dep[i] - N);
	}
	return 0;
}
