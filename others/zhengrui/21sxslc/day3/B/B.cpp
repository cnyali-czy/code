/*
	Problem:	B.cpp
	Time:		2021-01-17 12:01
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
const int maxn = 1e5 + 10, MOD = 998244353, inv2 = MOD + 1 >> 1;

vector <int> G[maxn];
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

int n, rt;
int v[maxn];

namespace flower
{
	bool judge() {return G[rt].size() == n - 1;}
	int main()
	{
		i64 ans = 0;
		REP(i, 1, n) if (i ^ rt) ans += v[i];
		cout << ans % MOD * inv(n - 1) % MOD << endl;
		return 0;
	}
}
namespace chain
{
	bool flag = 1;
	int bini2[maxn], p[maxn];
	int main()
	{
		bini2[0] = 1;
		REP(i, 1, n) bini2[i] = 1ll * inv2 * bini2[i - 1] % MOD;
		p[1] = (MOD + inv2 - bini2[n]) % MOD;
		REP(k, 3, n) p[k] = 1ll * bini2[k] * (MOD + inv2 - bini2[n - k + 1]) % MOD;
		i64 s = 0;
		REP(i, 1, n) s += p[i];
		cout << s % MOD << endl;
		return 0;
	}
}
int invs[maxn];
namespace bf
{
	int vis[maxn];
	i64 ans = 0;
	void dfs(int x, int p = 1)
	{
		int cnt = 0;
		for (int y : G[x]) if (vis[y] != 2) cnt++;
		if (cnt)
		{
			p = 1ll * p * invs[cnt] % MOD;
			vis[x]++;
			for (int y : G[x]) if (vis[y] != 2)
				dfs(y, p);
			vis[x]--;
		}
		else
		{
			ans = (ans + 1ll * p * v[x]) % MOD;
			return;
		}
	}
	int main()
	{
		dfs(rt);
		REP(i, 0, 10000)REP(j,1,10000)if(i*inv(j)%MOD==ans)
		{
			cout << i << " / " << j << endl;
			goto gg;
		}
gg:;
		cout << ans << endl;
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();rt = read<int>();
	invs[0] = invs[1] = 1;
	REP(i, 2, n) invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
	REP(i, 1, n) v[i] = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		G[x].emplace_back(y);G[y].emplace_back(x);
		if (y != x + 1) chain :: flag = 0;
	}
	return bf :: main();
	if (flower :: judge()) return flower :: main();
	else if (n <= 15) return bf :: main();
	else if (chain :: flag) return chain :: main();
	return 0;
}
