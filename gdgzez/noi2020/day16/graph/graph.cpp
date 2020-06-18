/*
	Problem:	graph.cpp
	Time:		2020-06-18 09:02
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxm = 2e5 + 10, MOD = 1e9 + 7;

int prime[maxn], p_cnt, Min_id[maxn], cnt[maxn];
bool notp[maxn];
struct __init__
{
	__init__(const int N = maxn - 10)
	{
		REP(i, 2, N)
		{
			if (!notp[i])
			{
				prime[++p_cnt] = i;
				Min_id[i] = p_cnt;
			}
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];
				if (tmp > N) break;
				notp[tmp] = 1;
				Min_id[tmp] = j;
				if (i % prime[j] == 0) break;
			}
		}
	}
}__INIT__;

int bg[maxn], ne[maxm], to[maxm], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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
#define i64 long long
#define ui64 unsigned i64
const ui64 base = 1e9 + 9;
int n, m, ty;
struct Matrix
{
	bitset <205> a[205];
	void clear() {REP(i, 1, min(n, 200)) a[i].reset();}
	bitset <205> & operator [](int x) {return a[x];}
	ui64 Hash()
	{
		ui64 res = 0;
		REP(i, 1, n) REP(j, 1, n) res = res * base + a[i].test(j);
		return res;
	}
	void output()
	{
		REP(i, 1, n) REP(j, 1, n) printf("%d%c", a[i].test(j), j == n ? '\n' : ' ');
	}
	inline bool operator == (Matrix b)
	{
		REP(i, 1, n) if (a[i] != b[i]) return 0;
		return 1;
	}
}tmp, G, A, bb, bin[201];
Matrix operator * (Matrix a, Matrix b)
{
	REP(i, 1, n) REP(j, 1, n) bb[j][i] = b[i][j];
	REP(i, 1, n) REP(j, 1, n)
		tmp[i][j] = (!!(a[i] & bb[j]).count());
	return tmp;			
}

namespace tarjan
{
	int dfn[maxn], low[maxn], dfs_clock;
	bool vis[maxn];
	int stack[maxn], top, blg[maxn], cnt;
	void dfs(int x)
	{
		low[x] = dfn[x] = ++dfs_clock;
		vis[x] = 1;
		stack[++top] = x;
		for (int i = bg[x]; i; i = ne[i])
			if (!dfn[to[i]]) {dfs(to[i]);chkmin(low[x], low[to[i]]);}
			else if (vis[to[i]]) chkmin(low[x], dfn[to[i]]);
		if (low[x] == dfn[x])
		{
			cnt++;
			while (1)
			{
				int y = stack[top--];
				vis[y] = 0;
				blg[y] = cnt;
				if (x == y) break;
			}
		}
	}
	int dep[maxn], res;
	void dfs1(int x)
	{
		for (int i = bg[x]; i; i = ne[i]) if (blg[x] == blg[to[i]])
			if (dep[to[i]]) res = __gcd(res, abs(dep[to[i]] - dep[x] - 1));
			else
			{
				dep[to[i]] = dep[x] + 1;
				dfs1(to[i]);
			}
	}
	void work()
	{
		REP(i, 1, n) if (!dfn[i])
			dfs(i);
		REP(i, 1, n) if (!vis[blg[i]])
		{
			vis[blg[i]] = 1;
			dep[i] = 1;
			res = 0;
			dfs1(i);
			while (res > 1)
			{
				int id(Min_id[res]), Min(prime[id]), k = 0;
				while (res % Min == 0) res /= Min, k++;
				chkmax(::cnt[id], k);
			}
		}
	}
}

Matrix power_pow(i64 b)
{
	Matrix res(G);
	b--;
	for (i64 i = 0; b; i++) if (b >> i & 1)
	{
		b ^= (1ll << i);
		res = res * bin[i];
	}
	return res;
}

int main()
{
#ifdef CraZYali
	file("graph");
#endif
	n = read<int>();m = read<int>();ty = read<int>();
	G.clear();
	while (m--)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);
	}
	tarjan :: work();
	i64 ans = 1, dd = 1;
	REP(i, 1, p_cnt) REP(j, 1, cnt[i]) (ans *= prime[i]) %= MOD, dd *= prime[i];
	if (!ty)
	{
		cout << ans << endl;
		return 0;
	}
	REP(x, 1, n) for (int i = bg[x]; i; i = ne[i]) G[x][to[i]] = 1;
	bin[0] = G;
	REP(i, 1, 60) bin[i] = bin[i - 1] * bin[i - 1];
	Matrix gd = power_pow(dd);
	i64 l = 1, r = 1e9, k = 114514;
	while (l <= r)
	{
		i64 mid = l + r >> 1;
		Matrix tmp = power_pow(mid);
		if (tmp * gd == tmp)
		{
			k = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	cout << k << ' ' << ans << endl;
	return 0;
}
