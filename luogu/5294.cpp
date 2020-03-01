/*
	Problem:	5294.cpp
	Time:		2020-03-01 12:02
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
const int maxn = 1e5 + 10, maxN = 2e7, MOD = 998244353;

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

int power_pow(int base, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(asn, base);
		base = mul(base, base);
		b >>= 1;
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m;
int a[maxn];

int ls[maxN], rs[maxN], rt[maxn], cur, k[maxN];
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)

void update(int pre, int &p, int l, int r, int pos)
{
	p = ++cur;
	ls[p] = ls[pre];
	rs[p] = rs[pre];
	k[p] = k[pre];
	if (pos <= mid)
	{
		update(lson, pos);
		k[p] = k[ls[p]];
	}
	else			update(rson, pos);

}
int query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return s[p];
	else
	{
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}

int dp[maxn], sum[maxn], sum2[maxn];
inline int sqr(int x) {return mul(x, x);}
int main()
{
#ifdef CraZYali
	file("5294");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, n) sum[i] = add(sum[i-1], a[i]);
	REP(i, 1, n) sum2[i] = add(sum2[i-1], mul(a[i], a[i]));
	REP(i, 1, n)
	{
	}
	return 0;
}
