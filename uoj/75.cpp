/*
	Problem:	75.cpp
	Time:		2021-06-14 23:32
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <iostream>
#include <cstdio>
#define i64 long long
#define ty char
#define pii pair <ty, ty>
#define graph vector <pii>

using namespace std;
const int MOD = 998244353, maxn = 100 + 5;

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

int a[maxn][maxn], n, m, k, picke;
inline void add(int x, int y)
{
	a[x][x]++;a[y][y]++;
	a[x][y]--;a[y][x]--;
}
inline i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		if (b >>= 1) (base *= base) %= MOD;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

pii e[maxn * maxn / 2];
const double alpha = .8;
const int gen = 800;
#define fi first
#define se second

vector <pair <int, graph> > v1, v2;
unordered_map <int, int> id;

inline int det(int n)
{
	i64 ans = 1;
	REP(i, 1, n)
	{
		if (!a[i][i])
			REP(j, i + 1, n) if (a[j][i])
			{
				REP(k, i, n) swap(a[i][k], a[j][k]);
				ans = -ans;
				break;
			}
		if (!a[i][i]) return 0;
		(ans *= a[i][i]) %= MOD;
		const i64 iv = inv(a[i][i]);
		REP(j, i + 1, n) if (a[j][i])
		{
			const i64 t = a[j][i] * iv % MOD;
			REP(k, i, n) a[j][k] = (a[j][k] - t * a[i][k]) % MOD;
		}
	}
	return (ans + MOD) % MOD;
}
graph merge(graph g1, graph g2, int n)
{
	graph res = g1;
	for (auto i : g2)
	{
		auto t = i;
		t.fi += n;t.se += n;
		res.emplace_back(t);
	}
	res.emplace_back(1, n + 1);
	return res;
}

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}

void init()
{
	srand(time(0));
	n = 12;
	REP(i, 1, n) REP(j, i + 1, n) e[m++] = make_pair(i, j);
	picke = m * alpha;

	REP(c, 0, gen - 1)
	{
		REP(i, 1, n) REP(j, 1, n) a[i][j] = 0;
		random_shuffle(e, e + m);
		vector <pii> v(picke);
		REP(i, 1, n) fa[i] = i;
		REP(i, 0, picke - 1)
		{
			add(e[i].fi, e[i].se);
			fa[find(e[i].fi)] = find(e[i].se);
			v[i] = e[i];
		}
		bool flg = 1;
		REP(i, 1, n) if (find(i) ^ find(1)) {flg = 0;break;}
		if (flg) v1.emplace_back(det(n - 1), v);
	}
	REP(i, 0, v1.size() - 1) REP(j, i, v1.size() - 1)
		v2.emplace_back(1ll * v1[i].fi * v1[j].fi % MOD, merge(v1[i].se, v1[j].se, n));
	REP(i, 0, (int)v2.size() - 1) id[v2[i].fi] = i;
}

int main()
{
#ifdef CraZYali
	file("75");
#endif
	init();
	register int T = read<int>();
	while (T--)
	{
		k = read<int>();
		if (!k)
		{
			puts("2 0");
			continue;
		}
		REP(i, 0, (int)v2.size() - 1)
		{
			i64 nd = k * inv(v2[i].fi) % MOD;
			if (id.find(nd) != id.end())
			{
				auto ans = merge(v2[i].se, v2[id[nd]].se, n + n);
				printf("%d %d\n", n * 4, (int)ans.size());
				for (auto i : ans) printf("%d %d\n", i.fi, i.se);
				goto ok;
			}
		}
		puts("qwq");
		DEBUG;
ok:;
	}
	return 0;
}
