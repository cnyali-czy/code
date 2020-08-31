/*
	Problem:	6774.cpp
	Time:		2020-08-30 22:01
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxq = 2e5 + 10;

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

int n, q;
int p[maxn], pos[maxn];

struct fenwick
{
	int s[maxn], tot;
	fenwick() {memset(s, 0, sizeof s);tot = 0;}
	void add(int x, int y = 1)
	{
		tot += y;
		while (x <= n)
		{
			s[x] += y;
			x += x & -x;
		}
	}
	int sp(int x)
	{
		int y = 0;
		while (x > 0)
		{
			y += s[x];
			x &= (x - 1);
		}
		return y;
	}
	int sf(int x)
	{
		if (x > n) return 0;
		int y = tot;
		x--;
		while (x > 0)
		{
			y -= s[x];
			x &= (x - 1);
		}
		return y;
	}
}f, F;
int blg[maxn], l, r, L, R;
struct Query
{
	int l, r, L, R, id;
	Query() {}
	Query(int l, int r, int L, int R, int id) : l(l), r(r), L(L), R(R), id(id) {}
	inline bool operator < (const Query &B) const
	{
		if (blg[l] < blg[B.l]) return 1;
		if (blg[l] > blg[B.l]) return 0;
		if (blg[r] < blg[B.r]) return 1;
		if (blg[r] > blg[B.r]) return 0;
		if (blg[L] < blg[B.L]) return 1;
		if (blg[L] > blg[B.L]) return 0;
		return R < B.R;
	}
}Q[maxq];
long long ans[maxq], Ans;
bool in[maxn];

inline void modi(int v, int flag)
{
	F.add(v, flag);
	f.add(pos[v], flag);
}

inline void Optl(int v)
{
	if (v < L || v > R) return;
	int res = F.sf(v + 1);
	if (in[v]) Ans -= res, modi(v, -1);
	else Ans += res, modi(v, 1);
	in[v] ^= 1;
}
inline void Optr(int v)
{
	if (v < L || v > R) return;
	int res = F.sp(v - 1);
	if (in[v]) Ans -= res, modi(v, -1);
	else Ans += res, modi(v, 1);
	in[v] ^= 1;
}
inline void OptL(int i)
{
	if (i < l || i > r) return;
	int res = f.sf(i + 1);
	int v = p[i];
	if (in[v]) Ans -= res, modi(v, -1);
	else Ans += res, modi(v, 1);
	in[v] ^= 1;
}
inline void OptR(int i)
{
	if (i < l || i > r) return;
	int res = f.sp(i - 1);
	int v = p[i];
	if (in[v]) Ans -= res, modi(v, -1);
	else Ans += res, modi(v, 1);
	in[v] ^= 1;
}

int main()
{
#ifdef CraZYali
	file("6774");
#endif
	n = read<int>();q = read<int>();
//	const int block = 400;
	const int block = max(5., pow(pow(n, 4) / (4 - 1) / q, 1. / 4));
	cerr << block << endl;
	REP(i, 1, n) blg[i] = (i - 1) / block + 1;
	REP(i, 1, n) pos[p[i] = read<int>()] = i;
	REP(i, 1, q)
	{
		int l = read<int>(), r = read<int>(), L = read<int>(), R = read<int>();
		Q[i] = Query(l, r, L, R, i);
	}
	sort(Q + 1, Q + 1 + q);
	L = R = p[1];l = r = 1;
	f.add(1);F.add(p[1]);
	in[p[1]] = 1;

	REP(i, 1, q)
	{
		while (r < Q[i].r) Optr(p[++r]);
		while (l > Q[i].l) Optl(p[--l]);
		while (r > Q[i].r) Optr(p[r--]);
		while (l < Q[i].l) Optl(p[l++]);
		while (R < Q[i].R) OptR(pos[++R]);
		while (L > Q[i].L) OptL(pos[--L]);
		while (R > Q[i].R) OptR(pos[R--]);
		while (L < Q[i].L) OptL(pos[L++]);
		if (i % 2000 == 0) fprintf(stderr, "Done %d / %d = %.2lf%%\n", i, q, i * 100. / q);
		ans[Q[i].id] = Ans;
	}

	REP(i, 1, q) printf("%lld\n", ans[i]);
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
