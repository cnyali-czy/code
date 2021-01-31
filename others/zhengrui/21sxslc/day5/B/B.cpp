/*
	Problem:	B.cpp
	Time:		2021-01-31 17:05
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#define i64 long long

using namespace std;
const int maxn = 2e5 + 10, maxm = 5e5 + 10, MOD = 998244353;

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

int n, m, u[maxm], v[maxm], deg[maxn];
vector <int> G[maxn], sG[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();
		REP(i, 1, n) deg[i] = 0, sG[i].clear();
		REP(i, 1, m)
		{
			int x = read<int>(), y = read<int>();
			sG[x].emplace_back(y);sG[y].emplace_back(x);
			u[i] = x;v[i] = y;
			deg[x]++;deg[y]++;
		}
		static int id[maxn];
		REP(i, 1, n) G[i].clear();
		REP(i, 1, m)
		{
			int &x = u[i], &y = v[i];
			if (make_pair(deg[x], x) < make_pair(deg[y], y)) swap(x, y);
			G[x].emplace_back(y);
		}
		i64 c3 = 0, c4 = 0;
		static int frm[maxn], cnt[maxn];
		REP(i, 1, n)
		{
			for (int j : G[i]) frm[j] = i;
			for (int j : G[i]) for (int k : G[j]) if (frm[k] == i) c3++;
			for (int j : G[i]) frm[j] = 0;
		}
		REP(i, 1, n)
		{
			for (int j : G[i]) for (int k : sG[j])
			{
				if (i == k || make_pair(deg[i], i) < make_pair(deg[k], k)) continue;
				if (frm[k] ^ i) cnt[k] = 0;
				frm[k] = i;
				c4 += (cnt[k]++);
			}
			for (int j : G[i]) for (int k : sG[j]) cnt[k] = frm[k] = 0;
		}
		i64 ans = (3 * c3 + c4 + m * (n + m - 3ll)) % MOD;
		REP(i, 1, n) (ans += deg[i] * (deg[i] - 1ll) / 2) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
}
