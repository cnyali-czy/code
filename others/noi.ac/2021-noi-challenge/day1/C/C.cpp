/*
	Problem:	C.cpp
	Time:		2021-06-19 11:08
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <cassert>
#include <iostream>
#include <cstdio>

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

int n, m, q, ml[maxn], mr[maxn];
int a[maxn];

inline void bf(int r, int l, int &L, int &R)
{
	DEP(i, r, l)
	{
		int ll = max(L, ml[i]), rr = min(R, mr[i]);
		if (ll <= rr) L = min(L, ml[i]), R = max(R, mr[i]);
	}
}

namespace pure_bf
{
	int main()
	{
		while (q--)
		{
			int opt = read<int>();
			if (opt == 1)
			{
				int u = read<int>();
				a[u] = read<int>();
			}
			else
			{
				int l = read<int>(), r = read<int>(), k = read<int>();
				int L = k, R = k;
				/*
				   static int b[maxn];
				   REP(i, 1, n) b[i] = a[i];
				   REP(i, l, r)
				   {
				   int mx = 0;
				   REP(j, ml[i], mr[i]) mx = max(mx, b[j]);
				   REP(j, ml[i], mr[i]) b[j] = mx;
				   }
				   */
				bf(r, l, L, R);
				int ans = 0;
				REP(i, L, R) ans = max(ans, a[i]);
				printf("%d\n", ans);
			}
		}
		return 0;
	}
}

namespace SMT_MX
{
	int mx[maxn << 2], tg[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
	void update(int p, int l, int r, int pos, int val)
	{
		if (l == r) mx[p] = val;
		else
		{
			if (pos <= mid) update(lson, pos, val);
			else update(rson, pos, val);
			mx[p] = max(mx[ls], mx[rs]);
		}
	}
	int *A;
	void build(int p, int l, int r)
	{
		tg[p] = -1;
		if (l == r) mx[p] = A[l];
		else
		{
			build(lson);
			build(rson);
			mx[p] = max(mx[ls], mx[rs]);
		}
	}
	inline void maintain(int p, int val)
	{
		tg[p] = mx[p] = val;
		return;
	}
	inline void pushdown(int p)
	{
		maintain(ls, tg[p]);
		maintain(rs, tg[p]);
		tg[p] = -1;
	}
	void modi(int p, int l, int r, int L, int R, int val)
	{
		if (L <= l && r <= R) maintain(p, val);
		else
		{
			if (~tg[p]) pushdown(p);
			if (L <= mid) modi(lson, L, R, val);
			if (R >  mid) modi(rson, L, R, val);
			mx[p] = max(mx[ls], mx[rs]);
		}
	}
	int qmax(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return mx[p];
		else
		{
			if (~tg[p]) pushdown(p);
			if (R <= mid) return qmax(lson, L, R);
			if (L >  mid) return qmax(rson, L, R);
			return max(qmax(lson, L, R), qmax(rson, L, R));
		}
	}
	void dfs(int p, int l, int r)
	{
		if (l == r) A[l] = mx[p];
		else
		{
			if (~tg[p]) pushdown(p);
			dfs(lson);
			dfs(rson);
		}
	}
}
namespace SMT_MI
{
	int mi[maxn << 2], tg[maxn << 2];
	void update(int p, int l, int r, int pos, int val)
	{
		if (l == r) mi[p] = val;
		else
		{
			if (pos <= mid) update(lson, pos, val);
			else update(rson, pos, val);
			mi[p] = min(mi[ls], mi[rs]);
		}
	}
	int *A;
	void build(int p, int l, int r)
	{
		tg[p] = -1;
		if (l == r) mi[p] = A[l];
		else
		{
			build(lson);
			build(rson);
			mi[p] = min(mi[ls], mi[rs]);
		}
	}
	inline void maintain(int p, int val)
	{
		tg[p] = mi[p] = val;
		return;
	}
	inline void pushdown(int p)
	{
		maintain(ls, tg[p]);
		maintain(rs, tg[p]);
		tg[p] = -1;
	}
	void modi(int p, int l, int r, int L, int R, int val)
	{
		if (L <= l && r <= R) maintain(p, val);
		else
		{
			if (~tg[p]) pushdown(p);
			if (L <= mid) modi(lson, L, R, val);
			if (R >  mid) modi(rson, L, R, val);
			mi[p] = min(mi[ls], mi[rs]);
		}
	}
	int qmin(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return mi[p];
		else
		{
			if (~tg[p]) pushdown(p);
			if (R <= mid) return qmin(lson, L, R);
			if (L >  mid) return qmin(rson, L, R);
			return min(qmin(lson, L, R), qmin(rson, L, R));
		}
	}
	void dfs(int p, int l, int r)
	{
		if (l == r) A[l] = mi[p];
		else
		{
			if (~tg[p]) pushdown(p);
			dfs(lson);
			dfs(rson);
		}
	}
}
const int B = 600;
int blg[maxn], L[maxn], R[maxn];
int goL[maxn], goR[maxn];
void init(int id, int l, int r)
{
	static int ID[maxn];
	REP(i, 1, n) ID[i] = i;
	SMT_MI :: A = ID;SMT_MI :: build(1, 1, n);
	REP(i, l, r)
	{
		int res = SMT_MI :: qmin(1, 1, n, ml[i], mr[i]);
		SMT_MI :: modi(1, 1, n, ml[i], mr[i], res);
	}
	SMT_MI :: A = goL;
	SMT_MI :: dfs(1, 1, n);

	SMT_MX :: A = ID;SMT_MX :: build(1, 1, n);
	REP(i, l, r)
	{
		int res = SMT_MX :: qmax(1, 1, n, ml[i], mr[i]);
		SMT_MX :: modi(1, 1, n, ml[i], mr[i], res);
	}
	SMT_MX :: A = goR;
	SMT_MX :: dfs(1, 1, n);
	REP(i, 1, n) assert(goL[i] >= goL[i - 1]);
	REP(i, 1, n) assert(goR[i] >= goR[i - 1]);
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();q = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, m) ml[i] = read<int>(), mr[i] = read<int>();

	REP(i, 1, m) blg[i] = (i - 1) / B + 1;
	REP(i, 1, m) R[blg[i]] = i;
	DEP(i, m, 1) L[blg[i]] = i;
//	REP(i, 1, blg[m]) init(i, L[i], R[i]);

	static int O[maxn], U[maxn], V[maxn], W[maxn], ok[maxn], cl[maxn], cr[maxn];
	REP(i, 1, q)
	{
		O[i] = read<int>();U[i] = read<int>();V[i] = read<int>();
		if (O[i] == 2) cl[i] = cr[i] = W[i] = read<int>();	
	}
	REP(C, 1, q) if (O[C] == 2)
	{
		int l = U[C], r = V[C], k = W[C];
		int &L = cl[C], &R = cr[C];
		if (r - l + 1 <= B) continue;
		int bl = blg[l], br = blg[r];
		bf(r, ::L[br], L, R);
	}
	/*
		DEP(i, br - 1, bl + 1)
		{
		L = goL[i][L];
		R = goR[i][R];
		}
		bf(::R[bl], l, L, R);*/
	DEP(i, blg[m], 1)
	{
		init(i, L[i], R[i]);
		REP(C, 1, q) if (O[C] == 2)
		{
			int l = U[C], r = V[C], k = W[C];
			int &L = cl[C], &R = cr[C];
			
			if (r - l + 1 <= B) continue;
			if (blg[l] < i && i < blg[r])
			{
				L = goL[L];
				R = goR[R];
			}
			else if (i == blg[l]) bf(::R[i], l, L, R);
		}
	}
	SMT_MX :: A = a;SMT_MX :: build(1, 1, n);
	REP(C, 1, q)
	{
		int opt = O[C];
		if (opt == 1)
		{
			int u = U[C], v = V[C];
			SMT_MX :: update(1, 1, n, u, v);
		}
		else
		{
			int l = U[C], r = V[C], k = W[C];
			int &L = cl[C], &R = cr[C];
			if (r - l + 1 <= B) bf(r, l, L, R);
			printf("%d\n", SMT_MX :: qmax(1, 1, n, L, R));
		}
	}
	cerr << clock () * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
