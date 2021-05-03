/*
	Problem:	1219.cpp
	Time:		2021-04-29 14:46
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10, B = 300;

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

int n, q, a[maxn], b[maxn], m;

struct Query
{
	int l, r, id;
	Query() {}
	Query(int l, int r, int id) : l(l), r(r), id(id) {}
	inline bool operator < (const Query &B) const {return r < B.r;}
};
vector <Query> vec[maxn];
int blg[maxn];
i64 ans[maxn], cnt[maxn];

inline i64 bf(int l, int r)
{
	i64 ans = 0;
	REP(i, l, r)
	{
		cnt[a[i]]++;
		ans = max(ans, cnt[a[i]] * b[a[i]]);
	}
	REP(i, l, r) cnt[a[i]] = 0;
	return ans;
}
inline void add(int x, i64 &ans)
{
	cnt[x]++;
	ans = max(ans, cnt[x] * b[x]);
}

int main()
{
#ifdef CraZYali
	file("1219");
#endif
	cin >> n >> q;
	REP(i, 1, n) a[i] = b[i] = read<int>();
	sort(b + 1, b + 1 + n);m = unique(b + 1, b + 1 + n) - b - 1;
	REP(i, 1, n) a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b;
	REP(i, 1, n) blg[i] = (i - 1) / B + 1;
	REP(i, 1, q)
	{
		int l = read<int>(), r = read<int>();
		if (blg[l] == blg[r]) ans[i] = bf(l, r);
		else vec[blg[l]].emplace_back(l, r, i);
	}
	REP(i, 1, blg[n]) if (vec[i].size())
	{
		sort(vec[i].begin(), vec[i].end());
		int r = i * B;
		i64 Ans = 0;
		for (auto Q : vec[i])
		{
			while (r < Q.r) add(a[++r], Ans);
			i64 res = Ans;
			REP(j, Q.l, i * B) add(a[j], res);
			ans[Q.id] = res;
			REP(j, Q.l, i * B) cnt[a[j]]--;			
		}
		REP(j, i * B + 1, r) cnt[a[j]] = 0;
	}
	REP(i, 1, q) printf("%lld\n", ans[i]);
	return 0;
}
