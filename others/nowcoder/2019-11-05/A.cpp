/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.06 21:23
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);
#include <unordered_map>

namespace run
{
	const int maxn = 1e5 + 10, MOD = 1e9 + 7, Inv2 = (MOD + 1) / 2;

	int n, k, a[maxn], b[maxn], ans;
	unordered_map <int, int> mem;
	int main()
	{
		n = read<int>();
		k = read<int>();
		const long long basic = 1ll * n * k % MOD;
		REP(i, 1, n)
		{
			a[i] = read<int>();
			b[i] = i - mem[a[i]];
			mem[a[i]] = i;
			(ans += (basic - i + 1) % MOD * b[i] % MOD) %= MOD;
		}
		const long long hanhan = 1ll * Inv2 * (k - 1) % MOD * k % MOD * n % MOD;
		REP(i, 1, n)
		{
			if (b[i] == i) b[i] += n - mem[a[i]];
			(ans += (hanhan - 1ll * (k - 1) * (i - 1) % MOD) % MOD * b[i] % MOD) %= MOD;
		}
		cout << (ans + MOD) % MOD << endl;
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	return run::main();
}
