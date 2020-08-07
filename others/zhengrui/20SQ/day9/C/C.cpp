/*
	Problem:	C.cpp
	Time:		2020-08-07 09:49
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m;

vector <int> G[maxn];
bool vis[maxn];
int in[maxn];

void dfs(int u)
{
	vis[u] = 1;
	for (int v : G[u])
	{
		in[v]++;
		if (!vis[v]) dfs(v);
	}
}

const int MOD = 1000114519;

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

int k = 11;
struct table
{
	int a[11];
	inline int& operator [] (int x) {return a[x];}
	inline table operator + (table b)
	{
		table c;
		REP(i, 0, k) c[i] = (a[i] + b[i]) % MOD;
		return c;
	}
	inline table operator * (i64 b)
	{
		table c;
		REP(i, 0, k) c[i] = a[i] * b % MOD;
		return c;
	}
};
struct E
{
	int rnk, a[11];
	inline int& operator [] (int x) {return a[x];}
	table b[11];
	inline void ins(table t)
	{
		REP(i, 0, k - 1) if (t.a[i])
			if (a[i]) t = t + b[i] * (MOD - t[i]);
			else
			{
				rnk++;
				a[i] = 1;
				b[i] = t * inv(t[i]);
				return;
			}
	}
}a[maxn];

int q[maxn], head, tail, ans[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	srand(114514);
	n = read<int>();m = read<int>();
	while (m--)
	{
		int x = read<int>(), y = read<int>();
		G[x].emplace_back(y);
	}
	k = G[1].size();
	dfs(1);
	q[0] = 1;
	int cur = 0;
	while (head <= tail)
	{
		int u = q[head++];
		ans[u] = a[u].rnk;
		for (int v : G[u])
		{
			table t;REP(i, 0, k) t[i] = 0;
			if (u == 1) t[cur++] = 1;
			else REP(i, 0, k) if (a[u][i]) t = t + a[u].b[i] * (1ll * rand() * rand() % MOD);
			a[v].ins(t);
			if (!(--in[v])) q[++tail] = v;
		}
	}
	REP(i, 2, n) printf("%d\n", ans[i]);
	return 0;
}
