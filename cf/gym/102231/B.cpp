/*
	Problem:	B.cpp
	Time:		2020-11-21 18:26
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
#define int long long

using namespace std;
const int maxn = 3e5 + 10, MOD = 998244353;

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

int n, k, a[maxn];

const int maxN = maxn * 65;
int ch[maxN][2], s[maxN], cur, rt;
void ins(int &p, int dep, int x, int y)
{
	if (!p) p = ++cur;
	(s[p] += y) %= MOD;
	if (dep == -1) return;
	ins(ch[p][x >> dep & 1], dep - 1, x, y);
}
int query(int p, int dep, int x)
{
	if (!p) return 0;
	if (dep == -1) return s[p];
	bool fk = k >> dep & 1, fx = x >> dep & 1;
	if (fk) return query(ch[p][!fx], dep - 1, x);
	else return (s[ch[p][!fx]] + query(ch[p][fx], dep - 1, x)) % MOD;
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	sort(a + 1, a + 1 + n);
	static int f[maxn], ans = 0;
	REP(i, 1, n)
	{
		f[i] = (1 + query(rt, 60, a[i])) % MOD;
		ins(rt, 60, a[i], f[i]);
//		REP(j, 1, i - 1) if ((a[i] ^ a[j]) >= k) f[i] += f[j];
		ans += f[i];
	}
	cout << ans % MOD << endl;
	return 0;
}
