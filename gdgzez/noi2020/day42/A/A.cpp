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

void output()
{
	if (dp[n] > -inf / 2) cout << dp[n] << endl;
	else puts("Impossible");
}

struct Queue
{
	vector <int> v;
	int hd;
	Queue() {v.clear();hd = 0;}
	bool push(int val)
	{
		if (hd == v.size() || v[hd] < val)
		{
			v.clear();v.emplace_back(val);
			hd = 0;
			return 1;
		}
		while (v.size() > hd && v.back() < val) v.pop_back();
		v.emplace_back(val);
		return 0;
	}
	int front()
	{
		return hd < v.size() ? v[hd] : -inf;
	}
	bool erase(int val)
	{
		if (v[hd] == val) hd++;
		return hd == v.size() || v[hd] < val;
	}
}Q[maxn << 1];

namespace SMT
{
	const int maxn = ::maxn << 1;
	int Max[maxn << 2], lf[maxn];
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
	void build(int p, int l, int r)
	{
		Max[p] = -inf;
		if (l == r)
		{
			lf[l] = p;
			return;
		}
		else
		{
			build(lson);
			build(rson);
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
		pos += n;
		Max[lf[pos]] = val;
		for (int p = lf[pos] >> 1; p; p >>= 1)
			Max[p] = max(Max[ls], Max[rs]);
	}
	int query(int l, int r)
	{
		return query(1, 0, n + n, l + n, r + n);
	}
}

void add(int pos)
{
	pos--;
	int x = s[pos], val = dp[pos];
	if (Q[x + n].push(val)) SMT :: update(x, val);
}
void del(int pos)
{
	pos--;
	int x = s[pos], val = dp[pos];
	if (Q[x + n].erase(val)) SMT :: update(x, Q[x].front());
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
		int Max = SMT :: Max[SMT :: lf[s[i] + n]];
		if (s[i] < n) chkmax(Max, SMT :: query(s[i] + 1, n) - 1);
		if (s[i] >-n) chkmax(Max, SMT :: query(-n, s[i] - 1) + 1);
		dp[i] = Max;
	}
	output();
	return 0;
}
