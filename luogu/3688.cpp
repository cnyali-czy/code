#ifndef CraZYali
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
#endif
#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <bitset>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
const int maxn = 1e5 + 10, MOD = 998244353, maxN = 5.5e7;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, q, invs[maxn];
inline int Merge(int x, int y)
{
	return MOD + 1 - (x * (MOD + 1ll - y) + (MOD + 1ll - x) * y) % MOD;
}
#define merge(x, y) (x = Merge(x, y))

int ls[maxN], rs[maxN], s[maxN], rt[maxn << 2], cur;
#define Ls p << 1
#define Rs p << 1 | 1
#define Lson Ls, l, mid
#define Rson Rs, mid + 1, r
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
void update(int &p, int l, int r, int L, int R, register int val)
{
	if (!p) s[p = ++cur] = 1;
	if (L <= l && r <= R) merge(s[p], val);
	else
	{
		if (L <= mid) update(lson, L, R, val);
		if (R >  mid) update(rson, L, R, val);
	}
}

void update(int p, int l, int r, int x1, int x2, int y1, int y2, register int val)
{
	if (x1 <= l && r <= x2) update(rt[p], 1, n, y1, y2, val);
	else
	{
		if (x1 <= mid) update(Lson, x1, x2, y1, y2, val);
		if (x2 >  mid) update(Rson, x1, x2, y1, y2, val);
	}
}

int query(int p, int l, int r, register int x)
{
	if (!p) return 1;
	if (l == r) return s[p];
	else
		if (x <= mid)	return Merge(s[p], query(lson, x));
		else			return Merge(s[p], query(rson, x));
}
int query(int p, int l, int r, int x, int y)
{
	int res = query(rt[p], 1, n, y);
	if (l == r) return res;
	else
		if (x <= mid)	return Merge(res, query(Lson, x, y));
		else			return Merge(res, query(Rson, x, y));
}
inline int upd(int x) {return x >= MOD ? x - MOD : x;}
void write(int x)
{
	if (x / 10) write(x / 10);
	putchar(x % 10 + 48);
}
int main()
{
#ifdef CraZYali
	file("3688");
#endif
	n = read<int>();q = read<int>();
	invs[0] = invs[1] = 1;
	REP(i, 2, n) invs[i] = (MOD - MOD / i) * 1ll * invs[MOD % i] % MOD;
	while (q--)
	{
		int opt(read<int>()), l(read<int>()), r(read<int>());
		if (opt == 1)
		{
			if (1 < l) update(1, 0, n, 1, l - 1, l, r, MOD + 1 - invs[r - l + 1]), update(1, 0, n, 0, 0, 1, l - 1, 0);
			if (r < n) update(1, 0, n, l, r, r + 1, n, MOD + 1 - invs[r - l + 1]), update(1, 0, n, 0, 0, r + 1, n, 0);
			update(1, 0, n, l, r, l, r, MOD + 1 - 2 * invs[r - l + 1]);update(1, 0, n, 0, 0, l, r, invs[r - l + 1]);
		}
		else write(upd(query(1, 0, n, l - 1, r))), putchar(10);
	}
	return 0;
}
