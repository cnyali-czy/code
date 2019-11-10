/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.06 22:30
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

namespace run
{
	const int maxn = 1e5 + 10, MOD = 1e9 + 7;

	int n, m, ans, tmp[30], pre[30], C[30][30];

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

	int sum[maxn << 2][30], tag[maxn << 2][30];

	inline void maintain(int p, int val, int k)
	{
		tag[p][k] = 1ll * tag[p][k] * val % MOD;
		sum[p][k] = 1ll * sum[p][k] * val % MOD;
	}

	void pushdown(int p, int k)
	{
		if (tag[p][k] == 1) return;
		maintain(ls, tag[p][k], k);
		maintain(rs, tag[p][k], k);
		tag[p][k] = 1;
	}
	void add(int p, int l, int r, int x, int v, int k)
	{
		if (l == r) sum[p][k] = v;
		else
		{
			pushdown(p, k);
			if (x <= mid)	add(lson, x, v, k);
			else			add(rson, x, v, k);
			sum[p][k] = (sum[ls][k] + sum[rs][k]) % MOD;
		}
	}
	int query(int p, int l, int r, int x, int k)
	{
		if (r <= x) return sum[p][k];
		else
		{
			pushdown(p, k);
			return (query(lson, x, k) + (x > mid ? query(rson, x, k) : 0)) % MOD;
		}
	}
	void mul(int p, int l, int r, int x, int k)
	{
		if (r < x) return;
		if (x <= l) maintain(p, 2, k);
		else
		{
			pushdown(p, k);
			if (x <= mid) mul(lson, x, k);
			mul(rson, x, k);
			sum[p][k] = (sum[ls][k] + sum[rs][k]) % MOD;
		}
	}
	void build(int p, int l, int r, int k)
	{
		tag[p][k] = 1;
		if (l == r) return;
		else
		{
			build(lson, k);
			build(rson, k);
		}
	}
	int main()
	{
		C[0][0] = 1;
		REP(i, 1, 20)
		{
			C[i][0] = 1;
			REP(j, 1, i) C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
		}
		n = read<int>();
		m = read<int>();
		REP(k, 0, m) build(1, 1, n, k);
		REP(i, 1, n)
		{
			int a = read<int>();
			memset(tmp, 0, sizeof tmp);
			memset(pre, 0, sizeof pre);
			REP(k, 0, m) pre[k] = query(1, 1, n, a, k);
			DREP(k, m, 0)
				DREP(j, k, 0)
				(tmp[k] += 1ll * pre[j] * C[k][j] % MOD) %= MOD;
			REP(k, 0, m)
			{
				add(1, 1, n, a, tmp[k] + 1, k);
				mul(1, 1, n, a + 1, k);
			}
		}
		cout << (query(1, 1, n, n, m) + MOD) % MOD << endl;
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	return run::main();
}
