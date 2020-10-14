/*
	Problem:	A.cpp
	Time:		2020-10-14 11:08
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <ctime>
#include <cassert>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxm = 400 + 5, MOD = 1e9 + 7, inv2 = MOD + 1 >> 1, inv3 = (MOD + 1) / 3, inv4 = 1ll * inv2 * inv2 % MOD, inv8 = 1ll * inv2 * inv4 % MOD, inv6 = 1ll * inv2 * inv3 % MOD, inv24 = 1ll * inv3 * inv8 % MOD;

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

int m, k, s, l[maxm], r[maxm];
i64 ans;

inline int both(int l1, int r1, int l2, int r2)
{
	int l = max(l1, l2), r = min(r1, r2);
	return max(0, r - l + 1);
}

i64 Ax2()
{
	if (s & 1) return 0;
	REP(i, 1, m)
		if (l[i] <= s / 2 && s / 2 <= r[i]) return 1;
	return 0;
}

i64 A2x()
{
	i64 res = 0;
	REP(i, 1, m)
	{
		int L = s - r[i], R = s - l[i];
		REP(j, 1, m)
			res += both(L, R, l[j], r[j]);
	}
	return res % MOD;
}

namespace two
{
	// ( A^2(x) - A(x^2) ) / 2
	void work()
	{
		ans = (A2x() - Ax2() + MOD) % MOD * inv2 % MOD;
	}
}

const int NNN = 20;
int fac[NNN + 5], Inv[NNN + 5];
struct __init__
{
	__init__()
	{
		fac[0] = 1;
		REP(i, 1, NNN) fac[i] = 1ll * i * fac[i - 1] % MOD;
		Inv[NNN] = inv(fac[NNN]);
		DEP(i, NNN - 1, 0) Inv[i] = (i + 1ll) * Inv[i + 1] % MOD;
	}
}__INIT__;
inline i64 C(int n, int m)
{
	if (n < m || m < 0) return 0;
	i64 down = 1;
	REP(i, 1, m) down = down * (n - i + 1) % MOD;
	return down * Inv[m] % MOD;
}
inline i64 magic(int n, int m) // [x ^ n](1 / (1 - x)) ^ m
{
	return C(n + m - 1, m - 1);
}

i64 A3x()
{
	i64 res = 0;
	REP(i, 1, m) REP(j, i, m) REP(k, j, m)
	{
//		int L[] = {l[i], l[j], l[k]};
//		int R[] = {r[i], r[j], r[k]};
		i64 cur = 0;
		REP(S, 0, 7)
		{
			int ard = 0, sgn = 1;
			if (S >> 0 & 1) ard += l[i];
			else			ard += r[i] + 1, sgn = -sgn;
			if (S >> 1 & 1) ard += l[j];
			else			ard += r[j] + 1, sgn = -sgn;
			if (S >> 2 & 1) ard += l[k];
			else			ard += r[k] + 1, sgn = -sgn;
			if (ard > s) continue;
			cur += sgn * magic(s - ard, 3);
		}
		int times;
		if (i == j)
			if (j == k) times = 1;
			else times = 3;
		else
			if (j == k) times = 3;
			else times = 6;
		res += cur * times;
	}
	res %= MOD;
	if (res < 0) res += MOD;
	return res;
}
i64 AxAx2()
{
	i64 res = 0;
	REP(i, 1, m)
	{
		int l1 = s - r[i], r1 = s - l[i];
		REP(j, 1, m)
		{
			int l2 = l[j] * 2, r2 = r[j] * 2;
			if (l2 > s) continue;
			int gdl = max(l1, l2), gdr = min(r1, r2);
			if ((gdl - l2) & 1) gdl++;
			if ((gdr - l2) & 1) gdr--;
			if (gdl > gdr) continue;
			res += (gdr - gdl + 1 + 1) / 2;
		}
	}
	return res % MOD;
}
i64 Ax3()
{
	if (s % 3) return 0;
	REP(i, 1, m)
		if (l[i] <= s / 3 && s / 3 <= r[i]) return 1;
	return 0;
}

namespace three
{
	// ( A^3(x) - 3A(x)A(x^2) + 2A(x^3) ) / 6
	void work()
	{
		ans = (A3x() - 3 * AxAx2() + 2 * Ax3()) * inv6 % MOD;
		if (ans < 0) ans += MOD;
	}
}

inline i64 sgn(i64 x) {return x & 1 ? -1 : 1;}

i64 A4x_bf()
{
	i64 res = 0;
	REP(i, 1, m) REP(j, 1, m) REP(k, 1, m) REP(o, 1, m)
	{
		int L[] = {l[i], l[j], l[k], l[o]};
		int R[] = {r[i] + 1, r[j] + 1, r[k] + 1, r[o] + 1};
		i64 cur = 0;
		REP(S, 0, (1 << 4) - 1)
		{
			int sgn = 1, ard = 0;
			REP(i, 0, 3)
				if (S >> i & 1) ard += L[i];
				else			ard += R[i], sgn = -sgn;
			if (ard > s) continue;
			cur += sgn * magic(s - ard, 4);
		}
		int times = 1;
		res += cur * times;
	}
	res %= MOD;
	if (res < 0) res += MOD;
	return res;
}

i64 A4x()
{
	static pair <int, int> A[maxm * 2], A2[maxm * maxm * 4];
	REP(i, 1, m) A[i] = make_pair(l[i], 1), A[i + m] = make_pair(r[i] + 1, -1);
	int N = 0;
	REP(i, 1, m + m) REP(j, 1, m + m)
		A2[++N] = make_pair(A[i].first + A[j].first, A[i].second * A[j].second);
	sort(A2 + 1, A2 + 1 + N);
	i64 res = 0;
	i64 s1 = 0, s2 = 0, s3 = 0, s4 = 0;
	for (int i = N, k = 0; i >= 1; i--)
	{
		while (k < N && A2[i].first + A2[k + 1].first <= s)
		{
			k++;
			s1 += A2[k].second;
		}
		int ai = A2[i].first, fi = A2[i].second;
		i64 b = s - ai + 3;
		if (b < 0) continue;
		i64 cur = 0;

		REP(j, 1, k)
		{
			int aj = A2[j].first, fj = A2[j].second;
			i64 a = aj;
			if (ai + aj <= s)
				cur += fj * (-a * a % MOD * a + 3 * a * a % MOD * (b - 1) + (-2 + 6 * b - 3 * b * b) % MOD * a % MOD + (2 - 3 * b + b * b) % MOD * b) % MOD;
			else break;
		}

		res += cur * fi;
	}
	res = res % MOD * Inv[3] % MOD;
	if (res < 0) res += MOD;
	return res;
}

i64 magic1(i64 n) // [x^n] 1 / (1-x^2) / (1-x)^2
{
	return (7 + sgn(n) + 8 * n + 2 * n * n) % MOD * inv8 % MOD;
}
i64 Ax2A2x()
{
	i64 res = 0;
	REP(i, 1, m) REP(j, 1, m) REP(k, 1, m)
	{
		int L[] = {2 * l[i], l[j], l[k]};
		int R[] = {2 * (r[i] + 1), r[j] + 1, r[k] + 1};
		i64 cur = 0;
		REP(S, 0, (1 << 3) - 1)
		{
			int sgn = 1, ard = 0;
			REP(i, 0, 2)
				if (S >> i & 1) ard += L[i];
				else			ard += R[i], sgn = -sgn;
			if (ard > s) continue;
			cur += sgn * magic1(s - ard);
		}
		int times = 1;
		res += cur * times;
	}
	res %= MOD;
	if (res < 0) res %= MOD;
	return res;
}
i64 magic2(i64 n) // [x ^ n] 1 / (1 - x^2)^2
{
	if (n & 1) return 0;
	return n + 2 >> 1;
}
i64 A2x2()
{
	i64 res = 0;
	REP(i, 1, m) REP(j, 1, m)
	{
		int L[] = {2 * l[i], 2 * l[j]};
		int R[] = {2 * (r[i] + 1), 2 * (r[j] + 1)};
		i64 cur = 0;
		REP(S, 0, (1 << 2) - 1)
		{
			int sgn = 1, ard = 0;
			REP(i, 0, 1)
				if (S >> i & 1) ard += L[i];
				else			ard += R[i], sgn = -sgn;
			if (ard > s) continue;
			cur += sgn * magic2(s - ard);
		}
		int times = 1;
		res += cur * times;
	}
	res %= MOD;
	if (res < 0) res += MOD;
	return res;
}
i64 magic3(i64 n) // [x ^ n] 1 / (1 - x ^ 3)(1 - x)
{
	return n / 3 + 1;
}
i64 Ax3Ax()
{
	i64 res = 0;
	REP(i, 1, m) REP(j, 1, m)
	{
		int L[] = {3 * l[i], l[j]};
		int R[] = {3 * (r[i] + 1), r[j] + 1};
		i64 cur = 0;
		REP(S, 0, (1 << 2) - 1)
		{
			int sgn = 1, ard = 0;
			REP(i, 0, 1)
				if (S >> i & 1) ard += L[i];
				else			ard += R[i], sgn = -sgn;
			if (ard > s) continue;
			cur += sgn * magic3(s - ard);
		}
		int times = 1;
		res += cur * times;
	}
	res %= MOD;
	if (res < 0) res += MOD;
	return res;
}
i64 Ax4()
{
	if (s % 4) return 0;
	REP(i, 1, m)
		if (l[i] <= s / 4 && s / 4 <= r[i]) return 1;
	return 0;
}

namespace four
{
	// (A(x)^4 - 6A(x^2)A(x)^2 + 3A(x^2)^2 + 8A(x^3)A(x) - 6A(x^4)) / 24
	void work()
	{
		ans = (A4x() - 6 * Ax2A2x() + 3 * A2x2() + 8 * Ax3Ax() - 6 * Ax4()) * inv24 % MOD;
		if (ans < 0) ans += MOD;
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	m = read<int>();k = read<int>();s = read<int>();
	for (int i = 1; i <= m; i++)
	{
		l[i] = read<int>(), r[i] = read<int>();
		if (l[i] > s)
		{
			i--;
			m--;
		}
	}
	if (k == 2) two :: work();
	if (k == 3) three :: work();
	if (k == 4) four :: work();
	cout << ans << endl;
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	return 0;
}
