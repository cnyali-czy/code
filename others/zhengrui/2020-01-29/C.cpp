/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.29 09:18
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 30000 + 10, maxm = 30000 + 10, MOD = 998244353;

void inc(int &x, int y)
{
	x += y;
	if (x >= MOD) x -= MOD;
}

#define inv(x) power_pow(x, MOD - 2)

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
	const int N = maxn;
	int n, K, m, a[N], po[6], tg1[N << 2], tg2[N << 2];
	struct mat
	{
		int a[6][6];
		inline void init() {memset(a, 0, sizeof a);}
		int* operator [] (int x) {return a[x];}
	}T[N << 2], TT[N << 2], bin[N], c;
	mat operator * (mat a, mat b)
	{
		c.init();
		REP(i, 0, K)
			REP(j, 0, K)
			{
				unsigned long long tmp = 0;
				REP(k, 0, K) tmp += 1ll * a[i][k] * b[k][j];
				c[i][j] = tmp % MOD;
			}
		return c;
	}
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
	inline void pushup(int p)
	{
		T[p] = T[ls] * T[rs];
		if (K == 4) TT[p] = TT[ls] * TT[rs];
	}
	void maintain1(int p, int l, int r, const int &v)
	{
		if (!v) return;
		(tg1[p] += v) %= MOD;
		REP(i, 0, K) po[i] = i < K ? (i + v) % K : K;
		REP(i, 0, K) REP(j, 0, K) c[po[i]][po[j]] = T[p][i][j];
		T[p] = c;
		if (K == 4 && (v & 1))
		{
			REP(i, 0, K) REP(j, 0, K) c[po[po[i]]][po[po[j]]] = TT[p][i][j];
			TT[p] = c;
		}
	}
	void maintain2(int p, int l, int r, const int &v)
	{
		if (v == 1) return;
		REP(i, 0, K) po[i] = i < K ? i * v % K : K;
		if (K == 4 && !v) T[p] = TT[p] = bin[r - l + 1];
		else if (K == 4 && v == 2) {T[p] = TT[p];TT[p] = bin[r - l + 1];}
		else if (!v) T[p] = bin[r - l + 1];
		else
		{
			REP(i, 0, K) REP(j, 0, K) c[po[i]][po[j]] = T[p][i][j];
			T[p] = c;
		}
		(tg1[p] *= v) %= K;
		(tg2[p] *= v) %= K;
	}
	void pushdown(int p, int l, int r)
	{
		if (tg2[p] != 1)
		{
			maintain2(lson, tg2[p]);
			maintain2(rson, tg2[p]);
			tg2[p] = 1;
		}
		if (tg1[p])
		{
			maintain1(lson, tg1[p]);
			maintain1(rson, tg1[p]);
			tg1[p] = 0;
		}
	}
	void build(int p, int l, int r)
	{
		tg1[p] = 0;
		tg2[p] = 1;
		if (l == r)
		{
			T[p].init();
			REP(i, 0, K) T[p][i][i] = T[p][i][a[l]] = 1;
			if (K == 4)
			{
				TT[p].init();
				REP(i, 0, K) TT[p][i][i] = TT[p][i][a[l] * 2 % 4] = 1;
			}
		}
		else
		{
			build(lson);
			build(rson);
			pushup(p);
		}
	}
	void update1(int p, int l, int r, const int &L, const int &R, const int &v)
	{
		if (L <= l && r <= R) maintain1(p, l, r, v);
		else
		{
			pushdown(p, l, r);
			if (L <= mid) update1(lson, L, R, v);
			if (R >  mid) update1(rson, L, R, v);
			pushup(p);
		}
	}
	void update2(int p, int l, int r, const int &L, const int &R, const int &v)
	{
		if (L <= l && r <= R) maintain2(p, l, r, v);
		else
		{
			pushdown(p, l, r);
			if (L <= mid) update2(lson, L, R, v);
			if (R >  mid) update2(rson, L, R, v);
			pushup(p);
		}
	}
	mat query(int p, int l, int r, const int &L, const int &R)
	{
		if (L <= l && r <= R) return T[p];
		pushdown(p, l, r);
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) * query(rson, L, R);
	}
	int main()
	{
		register int T = read<int>();
		while (T--)
		{
			n = read<int>();
			K = read<int>();
			m = read<int>();
			REP(i, 1, n) a[i] = read<int>();
			REP(i, 0, K)
				bin[1][i][i] = bin[1][i][0] = 1;
			REP(i, 2, n) bin[i] = bin[1] * bin[i-1];
			build(1, 1, n);
			while (m--)
			{
				int opt = read<int>(), l = read<int>(), r = read<int>(), x;
				if (opt ^ 3) x = read<int>();
				if (opt == 1) update1(1, 1, n, l, r, x);
				else if (opt == 2) update2(1, 1, n, l, r, x);
				else
				{
					mat res = query(1, 1, n, l, r);
					int ans = 0;
					REP(i, 0, K - 1) inc(ans, res[K][i]);
					printf("%d\n", ans);
				}
			}
		}
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	return run::main();
}
