//test

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <unordered_map>
#define i64 long long
using namespace std;
const int N = 5e4 + 5, E = 34, MOD = 998244353;

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

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

int n, a[N], ans;

struct dp
{
	int m, w[N], val[N][E], l[N][E], r[N][E], f[N][E], tf[N], tm, tl[E], tr[E],
	tv[E], tot, cnt[N], s1[N], s2[N];
	inline int& operator [] (int x) {return w[x];}

	unordered_map <int, int> ty;
	vector <int> a[N * E], th[N * E];

	void work()
	{
		REP(i, 1, n)
		{
			tl[tm = 1] = tr[1] = i; tv[1] = w[i];
			REP(j, 1, m)
			{
				int tmp = __gcd(w[i], val[i - 1][j]);
				if (tv[tm] == tmp) tl[tm] = l[i - 1][j];
				else tl[++tm] = l[i - 1][j], tr[tm] = r[i - 1][j], tv[tm] = tmp;
			}
			cnt[i] = m = tm;
			REP(j, 1, m)
			{
				l[i][j] = tl[j];
				r[i][j] = tr[j];
				val[i][j] = tv[j];
				if (!ty[val[i][j]]) ty[val[i][j]] = ++tot;
				a[ty[val[i][j]]].emplace_back(i);
				th[ty[val[i][j]]].emplace_back(j);
			}
		}
		REP(V, 1, tot)
		{
			int m = a[V].size(), pl = 0, pr = 0;
			REP(i, 1, m)
			{
				int p = a[V][i - 1], q = th[V][i - 1], le = l[p][q], ri = r[p][q];
				while (a[V][pr] < ri) pr++; while (a[V][pl] < le) pl++;
				tf[i] = add(mul(s1[pl] + 1, ri - le + 1), mul(sub(s1[pr], s1[pl]), ri));
				inc(tf[i], sub(s2[pl], s2[pr]));
				s1[i] = add(s1[i - 1], tf[i]);
				s2[i] = add(s2[i - 1], mul(tf[i], p));
				f[p][q] = tf[i];
			}
		}
	}
} A, B;

unordered_map <int, int> L, R;
int cL, cR, cLR;

inline void insL(int num, int f)
{
	inc(L[num], f);
	inc(cL, f);
	inc(cLR, mul(f, R[num]));
}

inline void insR(int num, int f)
{
	inc(R[num], f);
	inc(cR, f);
	inc(cLR, mul(f, L[num]));
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		a[i] = read<int>();
		A[i] = B[n - i + 1] = a[i];
	}
	A.work(); B.work();
	REP(i, 1, n) REP(j, 1, A.cnt[i]) inc(ans, A.f[i][j]);
	REP(i, 1, n) REP(j, 1, B.cnt[i]) insR(B.val[i][j], B.f[i][j]);
	REP(i, 1, n)
	{
		REP(j, 1, B.cnt[n - i + 1])
			insR(B.val[n - i + 1][j], MOD - B.f[n - i + 1][j]);
		if (i > 1) REP(j, 1, A.cnt[i - 1])
			insL(A.val[i - 1][j], A.f[i - 1][j]);
		printf("%d%c", sub(ans, add(cLR, add(cL, cR))), i == n ? '\n' : ' ' );
	}
	return 0;
}
