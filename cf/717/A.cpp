/*
	Problem:	A.cpp
	Time:		2020-11-30 21:41
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 200 + 5, MOD = 1e9 + 7, inv2 = (MOD + 1 >> 1);

i64 power_pow(i64 base, i64 b)
{
	if (b >= MOD - 1) b %= (MOD - 1);
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int fac[maxn], Inv[maxn], invs[maxn], inv5[maxn];
inline int add(int x, int y) {x += y;if (x >= MOD) x -= MOD;return x;}
inline int sub(int x, int y) {x -= y;if (x < 0) x += MOD;return x;}
struct num
{
	int a, b;//a + b * Sqrt(5)
	num(int a = 0, int b = 0) : a(a), b(b) {}
	num operator + (num B) {return num(add(a, B.a), add(b, B.b));}
	num operator - (num B) {return num(sub(a, B.a), sub(b, B.b));}
	num operator * (num B) {return num((1ll * a * B.a + 5ll * b * B.b) % MOD, (1ll * a * B.b + 1ll * b * B.a) % MOD);}
	num operator ^ (i64 b)
	{
		num base = *this, ans(1, 0);
		while (b)
		{
			if (b & 1) ans = ans * base;
			base = base * base;
			b >>= 1;
		}
		return ans;
	}
	inline bool operator == (num B) {return a == B.a && b == B.b;}
};
num binx[maxn], biny[maxn];
num X(inv2, inv2), Y(inv2, MOD - inv2);
void init(int n)
{
	fac[0] = invs[0] = Inv[0] = 1;
	fac[1] = invs[1] = Inv[1] = 1;
	inv5[0] = 1;inv5[1] = inv(5);
	binx[0] = biny[0] = 1;
	binx[1] = X;biny[1] = Y;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Inv[i] = 1ll * invs[i] * Inv[i - 1] % MOD;
		inv5[i] = 1ll * inv5[i - 1] * inv5[1] % MOD;
		binx[i] = binx[i - 1] * X;
		biny[i] = biny[i - 1] * Y;
	}
}
inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

int k, str[205][205];
i64 l, r;
num s(num x, i64 n)
{
	if (!n) return 0;
	if (x == 1) return n % MOD;
	num half = x ^ (n / 2);
	num res = s(x, n / 2);
	res = res * (half + 1);
	if (n & 1) res = res + half * half * x;
	return res;
}
signed main()
{
#ifdef CraZYali
	file("A");
#endif
	k = read<int>(), l = read<i64>(), r = read<i64>();
	str[0][0] = 1;
	REP(i, 1, k) REP(j, 1, i) str[i][j] = (str[i - 1][j - 1] + (i - 1ll) * str[i - 1][j]) % MOD;
	REP(i, 1, k) REP(j, 1, i) if (i + j & 1) str[i][j] = MOD - str[i][j];
	init(k);
	int ans = 0;
	REP(j, 0, k)
	{
		int realres = 0;
		REP(l, 0, j)
		{
			num qaq = binx[l] * biny[j - l];
			num res = (qaq ^ (::l + 1)) * s(qaq, r - ::l + 1);
			int Res = res.a + res.b;
			if (j - l & 1) Res = MOD * 2 - Res;
			realres = (realres + Res * C(j, l)) % MOD;
		}
		realres = 1ll * realres % MOD * inv5[j >> 1] % MOD;
		ans = (ans + 1ll * realres * str[k][j]) % MOD;
	}
	cout << 1ll * ans * Inv[k] % MOD << endl;
	return 0;
}
