/*
	Problem:	A.cpp
	Time:		2021-06-26 08:17
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_map>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned long long

using namespace std;
const int MOD = 998244353, p = 998244352, maxk = 200 + 5;

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

namespace BSGS
{
	int a, P, block;
	unordered_map <int, int> Mem;
	void prepare(int A)
	{
		const int P = MOD;
		a = A;
		block = 10000;
		const int a_block = power_pow(a, block);
		for (i64 i = 1, j = a_block, end_i = P / block + 1; i <= end_i; i++, (j *= a_block) %= MOD)
			if (Mem[j]) continue;
			else Mem[j] = i;
	}
	int BSGS(int b)
	{
		if (b == 1) return 0;
		i64 k = b;
		REP(i, 1, block)
		{
			(k *= a) %= MOD;
			if (Mem.count(k)) return Mem[k] * block - i;
		}
		return -1;
	}
}

int n, k, f[maxk], b[maxk];

int base[maxk][maxk], res[maxk][maxk];

const u64 LIM = 17e18;
void mul(int C[maxk][maxk], int A[maxk][maxk], int B[maxk][maxk])
{
	u64 res[maxk][maxk];
	REP(I, 1, k) REP(K, 1, k) if (A[I][K])
		REP(J, 1, k) if (B[K][J])
		{
			res[I][J] += (u64) A[I][K] * B[K][J];
			if (res[I][J] >= LIM) res[I][J] %= p;
		}
	REP(i, 1, k) REP(j, 1, k) C[i][j] = res[i][j] % p, res[i][j] = 0;
}
int main()
{
#ifdef CraZYali
	file("A");
#endif
	BSGS :: prepare(3);
	n = read<int>();k = read<int>();

	REP(i, 1, k) b[i] = read<int>() % p;
//	DEP(i, k, 1) b[i] = read<int>();
	REP(i, 1, k) f[i] = read<int>();
	
	REP(i, 1, k) f[i] = BSGS :: BSGS(f[i]);

	REP(i, 1, k) res[i][i] = 1;
	REP(i, 1, k) base[i][1] = b[i];
	REP(i, 1, k - 1) base[i][i + 1] = 1;

	int N = n - k;
	while (N)
	{
		if (N & 1) mul(res, res, base);
		if (N >>= 1) mul(base, base, base);
	}
	i64 ans = 0;
	REP(i, 1, k)
		(ans += 1ll * res[i][1] * f[k - i + 1]) %= p;
	cout << power_pow(3, ans) << endl;
	return 0;
}
