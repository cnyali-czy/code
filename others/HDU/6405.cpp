/*
	Problem:	6405.cpp
	Time:		2020-07-26 14:29
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 3e5 + 10, maxm = 1e6 + 10, MOD = 1e9 + 7, M = 1e6;

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
int ans[maxm];
namespace SAM
{
	const int maxn = ::maxn << 1;
	int ch[maxn][26], fail[maxn], len[maxn], last = 1, cur = 1, dfn[maxn], val[maxn];
	void extend(int c)
	{
		int u = ++cur, v = last;
		val[cur] = 1;
		len[u] = len[v] + 1;
		for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
		if (!v) fail[u] = 1;
		else if (len[ch[v][c]] == len[v] + 1) fail[u] = ch[v][c];
		else
		{
			int Old(ch[v][c]), New(++cur);
			val[New] = 1;
			len[New] = len[v] + 1;
			fail[New] = fail[Old];
			fail[Old] = fail[u] = New;
			copy(ch[Old], ch[Old] + 26, ch[New]);
			for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
		}
		last = u;
	}
	bool vis[maxn];
	void dfs(int p)
	{
		(ans[len[fail[p]] + 1]	+= val[p]) %= MOD;
		(ans[len[p] + 1]		-= val[p]) %= MOD;
		vis[p] = 1;
		REP(i, 0, 25) if (ch[p][i] && !vis[ch[p][i]]) dfs(ch[p][i]);
	}
}
int n, bin[maxm], Inv[maxm];
string str[10005];

int main()
{
#ifdef CraZYali
	file("6405");
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		cin >> str[i];
		str[i] = "W" + str[i];
		REP(j, 1, str[i].size() - 1) SAM :: extend(str[i][j] - 'a');
		SAM :: last = 1;
	}
	REP(i, 1, n)
	{
		int h = read<int>();
		int p = 1;
		REP(j, 1, (int)str[i].size() - 1)
		{
			int c = str[i][j] - 'a';
			p = SAM :: ch[p][c];
			int x = p;
			while (x && SAM :: dfn[x] != i)
			{
				SAM :: dfn[x] = i;
				SAM :: val[x] = 1ll * SAM :: val[x] * h % MOD;
				x = SAM :: fail[x];
			}
		}
	}
	SAM :: dfs(1);
	bin[0] = 1;
	REP(i, 1, M) bin[i] = 26ll * bin[i - 1] % MOD;
	REP(i, 2, M) (bin[i] += bin[i - 1]) %= MOD;
	REP(i, 1, M) (ans[i] += ans[i - 1]) %= MOD;
	REP(i, 1, M) (ans[i] += ans[i - 1]) %= MOD;
	REP(i, 1, M) ans[i] = (MOD + 1ll * ans[i] * inv(bin[i]) % MOD) % MOD;
	int q = read<int>();
	while (q--) printf("%d\n", ans[read<int>()]);
	return 0;
}
