/*
	Problem:	5071.cpp
	Time:		2021-04-29 16:34
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64

using namespace std;
const int maxn = 1e5 + 10, MOD = 19260817;

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		if (b >>= 1) (base *= base) %= MOD;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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

int n, q;

int small[233], st;
int pool[maxn * 180], *cur = pool, *s[1050];
unordered_map <int, int> id;

int m, cnt[maxn * 3];
/*
vector <pair <int, int> > vec[maxn];
*/
int bg[maxn], ne[maxn * 3], e;
pair <int, int> to[maxn * 3];
inline void add(int x, pair <int, int> y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
#define fi first
#define se second

void maintain(int i, int p, int k)
{
	if (p <= 1000)
	{
		if (s[p] == NULL) s[p] = cur, cur += n + 2, small[++st] = p;
		s[p][i] += k;
	}
	else
	{
		if (!id[p]) id[p] = ++m;
		add(i, make_pair(id[p], k));
	}
}

const int B = 500;

int blg[maxn];
struct Query
{
	int l, r, id;
	inline bool operator < (const Query &B) const
	{
		return blg[l] < blg[B.l] || blg[l] == blg[B.l] && ((r < B.r) ^ (blg[l] & 1));
	}
}Q[maxn];

int invs[maxn * 3];
const u64 LIM = 9e11;
u64 Ans = 1;
int ans[maxn];
inline void mul(u64 &x, u64 y)
{
	x *= y;
	if (x >= LIM) x %= MOD;
}
#define ins(x, flg)\
{\
	for (int E = bg[x]; E; E = ne[E])\
	{\
		mul(Ans, invs[cnt[to[E].fi] + 1]);\
		cnt[to[E].fi] += to[E].se * flg;\
		mul(Ans, cnt[to[E].fi] + 1);\
	}\
}
#undef i

int main()
{
#ifdef CraZYali
	file("5071");
#endif
	REP(i, 1, 1000) s[i] = NULL;
	n = read<int>();q = read<int>();
	invs[0] = invs[1] = 1;
	REP(i, 2, n * 3) invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
	REP(i, 1, n)
	{
		int x = read<int>();
		for (int j = 2; j * j <= x; j++) if (x % j == 0)
		{
			int k = 0;
			while (x % j == 0) k++, x /= j;
			maintain(i, j, k);
		}
		if (x > 1) maintain(i, x, 1);
	}
	REP(j, 1, st)
	{
		int p = small[j];
		REP(i, 1, n) s[p][i] += s[p][i - 1];
	}
	REP(i, 1, n) blg[i] = (i - 1) / B + 1;
	REP(i, 1, q)
	{
		int l = read<int>(), r = read<int>();
		Q[i] = (Query) {l, r, i};
	}
	sort(Q + 1, Q + 1 + q);
	int l = 1, r = 0;
	REP(i, 1, q)
	{
		while (r < Q[i].r) ins(++r, 1);
		while (l > Q[i].l) ins(--l, 1);
		while (r > Q[i].r) ins(r--, -1);
		while (l < Q[i].l) ins(l++, -1);
		u64 res = Ans;
		REP(j, 1, st)
		{
			int p = small[j], k = s[p][Q[i].r] - s[p][Q[i].l - 1];
			if (k) mul(res, k + 1);
		}
		ans[Q[i].id] = res % MOD;
	}
	REP(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
