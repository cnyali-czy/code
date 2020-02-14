/*
Problem:	C.cpp
Time:		2020-02-14 21:51
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
const int maxn = 3e5 + 10, maxN = maxn << 2;
const int MOD = 1e9 + 9, sqrt5 = 383008016, inv2 = MOD + 1 >> 1, base1 = 1ll * (1 + sqrt5) * inv2 % MOD, base2 = (MOD + 1ll - sqrt5) * inv2 % MOD, inv5 = (MOD + 1) / 5, invsqrt5 = 1ll * sqrt5 * inv5 % MOD;

inline int add(int x, int y) {register int res = x + y;return res >= MOD ? res - MOD : res;}
inline int sub(int x, int y) {register int res = x - y;return res <    0 ? res + MOD : res;}
inline int mul(i64 x, int y) {register i64 res = x * y;return res >= MOD ? res % MOD : res;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
int power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
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

int n, m, sum[maxn];
int ls[maxN], rs[maxN], tag[maxN], s[maxN], rt1, rt2, cur;

int fib(int n)
{
	return 1ll * invsqrt5 * (power_pow(base1, n) - power_pow(base2, n) + MOD) % MOD;
}
int bin[3][maxn], Inv[3][maxn];
const int i1 = inv(base1), i2 = inv(base2);
const int i_1 = inv(base1 - 1), i_2 = inv(base2 - 1);

struct __init__
{
	__init__(const int N = maxn - 10)
	{
		bin[1][0] = bin[2][0] = 1;
		Inv[1][0] = Inv[2][0] = 1;
		REP(i, 1, N)
		{
			bin[1][i] = mul(bin[1][i - 1], base1);
			bin[2][i] = mul(bin[2][i - 1], base2);
			Inv[1][i] = mul(Inv[1][i - 1], i1);
			Inv[2][i] = mul(Inv[2][i - 1], i2);
		}
	}
}__INIT__;

#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
int calc(int l, int r, int fir, int f)
{
	int res = 1ll * fir * (bin[f][r - l + 1] - 1) % MOD * (f == 1 ? i_1 : i_2) % MOD;
	return res;
}
void maintain(int &p, int l, int r, int val, int f)
{
	if (!p) p = ++cur;
	inc(tag[p], val);
	inc(s[p], calc(l, r, val, f));
}
void pushdown(int p, int l, int r, int f)
{
	maintain(lson, tag[p], f);
	maintain(rson, mul(tag[p], bin[f][mid - l + 1]), f);
	tag[p] = 0;
}
void update(int &p, int l, int r, int L, int R, int f)
{
	if (!p) p = ++cur;
	if (L <= l && r <= R) maintain(p, l, r, bin[f][l - L + 1], f);
	else
	{
		if (tag[p]) pushdown(p, l, r, f);
		if (L <= mid) update(lson, L, R, f);
		if (R >  mid) update(rson, L, R, f);
		s[p] = add(s[ls[p]], s[rs[p]]);
	}
}
int query(int p, int l, int r, int L, int R, int f)
{
	if (!p) return 0;
	if (L <= l && r <= R) return s[p];
	else
	{
		if (tag[p]) pushdown(p, l, r, f);
		if (R <= mid) return query(lson, L, R, f);
		if (L >  mid) return query(rson, L, R, f);
		return add(query(lson, L, R, f), query(rson, L, R, f));
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) sum[i] = add(sum[i-1], read<int>());
	while (m--)
	{
		int opt = read<int>(), l = read<int>(), r = read<int>();
		if (opt == 2)
		{
			int res1 = query(rt1, 1, n, l, r, 1), res2 = query(rt2, 1, n, l, r, 2);
			printf("%d\n", add(sub(sum[r], sum[l-1]), mul(invsqrt5, sub(res1, res2))));
		}
		else
		{
			update(rt1, 1, n, l, r, 1);
			update(rt2, 1, n, l, r, 2);
		}
	}
	return 0;
}
