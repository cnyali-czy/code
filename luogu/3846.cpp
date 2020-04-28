#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

#define i64 long long

int power_pow(i64 base, int b, const int MOD)
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

namespace BSGS
{
	int a, P, block;
	unordered_map <int, int> Mem;
	void prepare(int A)
	{
		const int MOD = P;
		a = A;
		block = sqrt(P + .5);
		const int a_block = power_pow(a, block, P);
		for (i64 i = 1, j = a_block, end_i = P / block + 1; i <= end_i; i++, (j *= a_block) %= MOD)
			if (Mem[j]) continue;
			else Mem[j] = i;
	}
	int BSGS(int b)
	{
		if (b == 1) return 0;
		const int MOD = P;
		i64 k = b;
		REP(i, 1, block)
		{
			(k *= a) %= MOD;
			if (Mem.count(k)) return Mem[k] * block - i;
		}
		return -1;
	}
}

int main()
{
#ifdef CraZYali
	file("3846");
#endif
	BSGS::P = read<int>();
	BSGS::prepare(read<int>());
	int res = BSGS::BSGS(read<int>());
	if (res > 0) cout << res << endl;
	else puts("no solution");
	return 0;
}
