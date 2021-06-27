/*
	Problem:	A.cpp
	Time:		2021-06-22 15:45
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define int long long

using namespace std;
const int maxn = 2e6 + 10, inf = 3e18;

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

#define poly vector <int>
int n, k;
poly f[maxn];

inline int deg(const poly &f) {return (int)f.size() - 1;}
int F[maxn], G[maxn];poly ret;
inline bool chkmin(int &x, int y) {if (x > y) {x = y;return 1;}return 0;}
void work(int l, int r, int L, int R)
{
	if (l > r || L > R) return;
	int mid = l + r >> 1, res = inf, pos = L;
	REP(i, L, min(mid, R))
		if (chkmin(res, F[i] + G[mid - i])) pos = i;
	ret[mid] = res;
	work(l, mid - 1, L, pos);
	work(mid + 1, r, pos, R);
}
poly operator * (poly f, poly g)
{
	int n = deg(f), m = deg(g);
	ret = poly(min(k, n + m) + 1, inf);ret[0] = 0;
	REP(i, 1, deg(ret)) F[i] = G[i] = inf;
	REP(i, 1, deg(f)) F[i] = f[i];
	REP(i, 1, deg(g)) G[i] = g[i];
	work(0, deg(ret), 0, deg(ret));
	return ret;
}
poly cdq(int l, int r)
{
	if (l == r) return f[l];
	int mid = l + r >> 1;
	return cdq(l, mid) * cdq(mid + 1, r);
}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n)
	{
		int m = read<int>(), a0 = read<int>();
		f[i].resize(m + 1);
		REP(j, 1, m) f[i][j] = f[i][j - 1] + read<int>();
		REP(j, 1, m) f[i][j] += a0;
		if (deg(f[i]) > k) f[i].resize(k + 1);
	}
	auto ans = cdq(1, n);
	REP(i, 1, k) printf("%lld%c", ans[i], i == end_i ? '\n' : ' ' );

	static int a[maxn], b[maxn];
	a[1] = 1;
	cout << a << ' ' << b << ' ' << a[1] << ' ' << b[1] << endl;
	swap(a, b);
	cout << a << ' ' << b << ' ' << a[1] << ' ' << b[1] << endl;

	return 0;
}
