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

using namespace std;
const int MOD = 998244353;

int power_pow(long long base, int b)
{
	long long ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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

int n;

void NTT(vector <int> &F, int n, int flag)
{
	int L(log2(n));
	vector <int> R(n);
	R[0] = 0;
	REP(i, 1, n - 1)
	{
		R[i] = (R[i >> 1] >> 1) | ((i & 1) << L - 1);
		if (i < R[i]) swap(F[i], F[R[i]]);
	}
	for (int i = 1; i < n; i <<= 1)
	{
		int wn = power_pow(3, (MOD - 1) / (i << 1));
		if (flag == -1) wn = inv(wn);
		for (int k = 0; k < n; k += i << 1)
			for (int l = 0, w = 1; l < i; l++, w = 1ll * w * wn % MOD)
			{
				int x(F[k + l]), y(1ll * w * F[k + l + i] % MOD);
				F[k + l] = (x + y) % MOD;
				F[k + l + i] = (x - y) % MOD;
			}
	}
	if (flag == -1)
	{
		const int InvN = inv(n);
		REP(i, 0, n - 1) F[i] = 1ll * F[i] * InvN % MOD;
	}
}

vector <int> getInv(vector <int> F, int n)
{
	if (!n) return vector<int>(1, inv(F[0]));
	vector <int> A(n + n, 0);
	vector <int> B(getInv(F, n >> 1));
	B.resize(n + n);
	F.resize(n);
	F.resize(n + n);
	NTT(F, n + n, 1);
	NTT(B, n + n, 1);
	REP(i, 0, n + n - 1) A[i] = (2ll * B[i] % MOD - 1ll * F[i] * B[i] % MOD * B[i] % MOD) % MOD;
	NTT(A, n + n, -1);
	A.resize(n);
	return A;
}
vector <int> F, Inv;

signed main()
{
#ifdef CraZYali
	file("4238-new");
#endif
	cin >> n;
	const int lim = 1 << (int)ceil(log2(n) + 1);
	F.resize(lim);
	REP(i, 0, n - 1) F[i] = read<int>();
	Inv = getInv(F, lim >> 1);
	REP(i, 0, n - 1) printf("%d%c", (Inv[i] + MOD) % MOD, i == n - 1 ? '\n' : ' ');
	return 0;
}
