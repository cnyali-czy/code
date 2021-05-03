/*
	Problem:	4887.cpp
	Time:		2021-05-02 21:16
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10;

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

int n, q, k, a[maxn], b[4444], N;

int cnt[16384];
i64 Ans, ans[maxn];
inline void ins(int x)
{
	REP(i, 1, N) Ans += cnt[x ^ b[i]];
	cnt[x]++;
}
inline void del(int x)
{
	cnt[x]--;
	REP(i, 1, N) Ans -= cnt[x ^ b[i]];
}

int blg[maxn];
struct Query
{
	int l, r, id;
	inline bool operator < (const Query &B) const
	{
		return blg[l] < blg[B.l] || blg[l] == blg[B.l] && ((r < B.r) ^ (blg[l] & 1));
	}
}Q[maxn];

int main()
{
#ifdef CraZYali
	file("4887");
#endif
	n = read<int>();q = read<int>();k = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 0, 16383) if (__builtin_popcount(i) == k) b[++N] = i;

	const int B = max(5., n / sqrt(q));
	REP(i, 1, n) blg[i] = (i - 1) / B + 1;
	REP(i, 1, q)
	{
		int l = read<int>(), r = read<int>();
		Q[i] = (Query){l, r, i};
	}
	sort(Q + 1, Q + 1 + q);
	int l = 1, r = 0;
	REP(i, 1, q)
	{
		while (r < Q[i].r) ins(a[++r]);
		while (l > Q[i].l) ins(a[--l]);
		while (r > Q[i].r) del(a[r--]);
		while (l < Q[i].l) del(a[l++]);
		ans[Q[i].id] = Ans;
	}
	REP(i, 1, q) printf("%lld\n", ans[i]);

	
	return 0;
}
