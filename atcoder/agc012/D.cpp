/*
	Problem:	D.cpp
	Time:		2021-06-01 14:34
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
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 2e5 + 10, MOD = 1e9 + 7;

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

int n, m, x, y;
vector <int> v[maxn], r[maxn];

int fac[maxn], invs[maxn], Invs[maxn];
void init(int n)
{
	fac[0] = invs[0] = Invs[0] = 1;
	fac[1] = invs[1] = Invs[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i ) * invs[MOD % i] % MOD;
		Invs[i] = 1ll * invs[i] * Invs[i - 1] % MOD;
	}
}
int fa[maxn], siz[maxn];unordered_map <int, int> cnt[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
inline void uni(int x, int y)
{
	fa[find(x)] = find(y);
}
int main()
{
#ifdef CraZYali
	file("D");
#endif
	init(n = read<int>());
	x = read<int>();y = read<int>();
	REP(i, 1, n)
	{
		static int id[maxn];
		int c = read<int>(), w = read<int>();
		if (!id[c]) id[c] = ++m;
		v[c = id[c]].emplace_back(w);
	}
	n = 0;
	REP(i, 1, m)
	{
		int mi = 0;
		REP(j, 0, (int)v[i].size() - 1) if (v[i][j] < v[i][mi]) mi = j;
		swap(v[i][0], v[i][mi]);
		REP(j, 0, (int)v[i].size() - 1) r[i].emplace_back(++n);
	}
	REP(i, 1, n) fa[i] = i;
	REP(i, 1, m)
		REP(j, 0, (int)v[i].size() - 1) if (v[i][j] + v[i][0] <= x) uni(r[i][j], r[i][0]);

	int mi = 1, se = 2;
	REP(i, 3, m)
		if (v[i][0] < v[mi][0]) se = mi, mi = i;
		else if (v[i][0] < v[se][0]) se = i;
	REP(i, 1, m) if (i ^ mi) REP(j, 0, (int)v[i].size() - 1)
		if (v[i][j] + v[mi][0] <= y) uni(r[mi][0], r[i][j]);
	if (se <= m) REP(j, 0, (int)v[mi].size() - 1)
		if (v[mi][j] + v[se][0] <= y) uni(r[se][0], r[mi][j]);
//	REP(i, 1, m) REP(j, 0, (int)v[i].size() - 1) REP(I, 1, m) REP(J, 0, (int)v[I].size() - 1) if (v[i][j] + v[I][J] <= (i == I ? x : y)) uni(r[i][j], r[I][J]);

	REP(i, 1, n) siz[find(i)]++;
	REP(i, 1, m) for (auto j : r[i]) cnt[find(j)][i]++;

	int ans = 1;
	int k = 0;
	REP(i, 1, n) if (i == find(i))
	{
		k++;
		ans = 1ll * ans * fac[siz[i]] % MOD;
		for (auto j : cnt[i]) ans = 1ll * ans * Invs[j.second] % MOD;
	}
	cerr<<k<<endl;

	cout << ans << endl;
	return 0;
}
