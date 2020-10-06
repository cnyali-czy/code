/*
	Problem:	A.cpp
	Time:		2020-08-14 08:42
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cassert>
#include <vector>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <ctime>
using namespace std;
const int maxn = 1e6 + 20, inf = 1e9;

inline void chkmax(int &x, int y) {if (x < y) x = y;}
inline void chkmin(int &x, int y) {if (x > y) x = y;}

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

int n, l, r, a[maxn], s[maxn], dp[maxn];

inline int w(int j, int i)
{
	int qaq = s[i] - s[j - 1];
	return qaq > 0 ? 1 : qaq < 0 ? -1 : 0;
}

void output()
{
	if (dp[n] > -inf / 2) cout << dp[n] << endl;
	else puts("Impossible");
}

namespace bf
{
	void work()
	{
		REP(i, 1, n)
		{
			dp[i] = -inf;
			REP(j, max(1ll, i + 1ll - r), i - l + 1) chkmax(dp[i], dp[j - 1] + w(j, i));
		}
		output();
	}
}
//int ph[maxn << 1], *head = ph + 1000005;
//vector <int> pv[maxn << 1], *Q = pv + 1000005;
int head[maxn << 1];
vector <int> Q[maxn << 1];

namespace SMT
{
	const int maxn = ::maxn << 1;
	int Max[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
	void build(int p, int l, int r)
	{
		Max[p] = -inf;
		if (l == r) return;
		else
		{
			build(lson);
			build(rson);
		}
	}
	void update(int p, int l, int r, int pos, int val)
	{
		if (l == r) Max[p] = val;
		else
		{
			if (pos <= mid) update(lson, pos, val);
			else			update(rson, pos, val);
			Max[p] = max(Max[ls], Max[rs]);
		}
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return Max[p];
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return max(query(lson, L, R), query(rson, L, R));
		}
	}
	void build()
	{
		build(1, 0, n + n);
	}
	void update(int pos, int val)
	{
		update(1, 0, n + n, pos + n, val);
	}
	int query(int l, int r)
	{
		return query(1, 0, n + n, l + n, r + n);
	}
}

void add(int pos)
{
	pos--;
	int val = s[pos] + n, gd = dp[pos];
	if (Q[val].size() == head[val] || Q[val].size() > head[val] && gd > Q[val][head[val]])
	{
		Q[val].clear();
		Q[val].emplace_back(gd);
		head[val] = 0;
		SMT :: update(s[pos], gd);
		return;
	}
//	while (Q[val].size() > head[val] && Q[val].back() < gd) Q[val].pop_back();
	Q[val].emplace_back(gd);
}
void del(int pos)
{
	pos--;
	int val = s[pos] + n, gd = dp[pos];
	if (gd == Q[val][head[val]])
	{
		head[val]++;
		if (head[val] >= Q[val].size())
			SMT :: update(s[pos], -inf);
		else if (Q[val][head[val]] < gd);
			SMT :: update(s[pos], Q[val][head[val]]);
	}
}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();l = read<int>();r = read<int>();
	REP(i, 1, n) a[i] = read<int>(), s[i] = s[i - 1] + a[i];
	SMT :: build();
	int L = 1, R = 0;
	REP(i, 1, n)
	{
		while (i - (R + 1) + 1 >= l)	add(++R);
		while (i - L + 1 > r)			del(L++);
		int Max = SMT :: query(s[i], s[i]);
		if (s[i] < n) chkmax(Max, SMT :: query(s[i] + 1, n) - 1);
		if (s[i] >-n) chkmax(Max, SMT :: query(-n, s[i] - 1) + 1);
		dp[i] = Max;
	}
	output();
	return 0;
}
