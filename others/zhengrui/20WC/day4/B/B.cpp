#define REP(i, s, e) for (register i64 i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register i64 i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int MOD = 998244353, inv2 = MOD + 1 >> 1;

const int N = 23333333;
int mem[N];
i64 f(i64 x)
{
	if (!x) return 0;
	while (!(x & 1)) x >>= 1;
	if (x < N && mem[x]) return mem[x];
	while (!(x & 1)) x >>= 1;
	int lowbit = x & -x, res = ((f(x - lowbit) + f(x + lowbit)) * inv2 + 1) % MOD;
	if (x < N) mem[x] = res;
	return res;
}

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	mem[1] = 2;
	register int T;cin >> T;
	while (T--)
	{
		i64 L, R, res = 0;
		scanf("%lld%lld", &L, &R);
		REP(i, L, R) res += f(i);
		printf("%lld\n", res % MOD);
	}
	return 0;
}
