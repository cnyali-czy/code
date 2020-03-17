/*
	Problem:	A.cpp
	Time:		2020-03-10 08:58
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 2000 + 10, maxN = 2e7, MOD = 998244353;

inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

int bin[maxn];
struct __initbin__
{
	__initbin__(const int n = maxn - 1)
	{
		bin[0] = 1;
		REP(i, 1, n) bin[i] = mul(bin[i-1], 2);
	}
}__INITBIN__;

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

int n, a[maxn];
/*
int lg[maxn], st[maxn][18];
struct __init__
{
	__init__(const int n = maxn - 1)
	{
		REP(i, 2, n) lg[i] = lg[i >> 1] + 1;
	}
}__INIT__;
inline int query(int l, int r)
{
	int k = lg[r - l + 1];
	return __gcd(st[l][k], st[r - (1 << k) + 1][k]);
}
*/

unordered_map <int, int> id;
int id_cur;
vector <int> cl[1000000 + 10], cr[1000000 + 10], ans;

inline void add(vector <int> &c, int x, int val = 1)
{
	while (x <= n)
	{
		c[x] += val;
		x += x & -x;
	}
}
inline int sum(const vector <int> &c, int x)
{
	int res = 0;
	while (x > 0)
	{
		res += c[x];
		x &= (x - 1);
	}
	return res;
}

int G[maxn][maxn], dp[maxn];
vector <pair <int, int> > v[1000005];
int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
//	REP(i, 1, n) st[i][0] = a[i];
//	REP(j, 1, 16)
//		REP(i, 1, n - (1 << j) + 1) st[i][j] = __gcd(st[i][j-1], st[i + (1 << j - 1)][j-1]);
	REP(i, 1, n)
	{
		int g = a[i];
		REP(j, i, n)
		{
			g = __gcd(g, a[j]);
			v[g].emplace_back(i, j);
			G[i][j] = g;
			if (!id[g])
			{
				id[g] = ++id_cur;
				cl[id_cur].resize(n + 5);
				cr[id_cur].resize(n + 5);
			}
			add(cl[id[g]], i);
			add(cr[id[g]], j);
			printf("%d %d %d\n", i, j, g);
		}
	}
	puts("");
	ans.resize(n + 5);
	REP(i, 1, n)
		REP(j, i, n)
		{
			int idg = id[G[i][j]], outside = sum(cr[idg], i - 1) + sum(cl[idg], n) - sum(cl[idg], j);
			printf("%d %d %d\n", i, j, outside);
			add(ans, i, bin[outside]);
			add(ans, j + 1, -bin[outside]);
		}
	REP(i, 1, n) cout << sum(ans, i) << (i == n ? '\n' : ' ');
	return 0;
}
