/*
	Problem:	qaq.cpp
	Time:		2020-06-16 20:53
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int MOD = 998244353, inv3 = (MOD + 1) / 3, inv2 = MOD + 1 >> 1;
#define poly vector <int> 
#define i64 long long
#define u64 unsigned i64

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

const int maxn = 1 << 21;
u64 NTTtmp[maxn];
int R[maxn];
void NTT(poly &a, int n, int flag)
{
	if (a.size() ^ n) a.resize(n);
	if (flag < 0) reverse(a.begin() + 1, a.end());
	static int *w[30], pool[maxn << 1 | 10];
	static bool vis[30];
	w[0] = pool;
	REP(i, 0, n - 1)
	{
		R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
		if (i < R[i]) swap(a[i], a[R[i]]);
	}
	REP(i, 0, n - 1) NTTtmp[i] = a[i];
	int lstc = 0;
	for (int i = 1, c = 0; i < n; i <<= 1, c++)
	{
		lstc = c;
		if (!vis[c])
		{
			vis[c] = 1;
			const i64 wn = power_pow(3, (MOD - 1) >> c + 1);
			if (i < maxn) w[c + 1] = w[c] + i;
			w[c][0] = 1;
			REP(j, 1, i - 1) w[c][j] = w[c][j - 1] * wn % MOD;
		}
		for (int k = 0; k < n; k += i + i)
			for (int l = 0; l < i; l++)
			{
				u64 x(NTTtmp[k + l]), y(NTTtmp[k + l + i] * w[c][l] % MOD);
				NTTtmp[k + l] = x + y;
				NTTtmp[k + l + i] = MOD + x - y;
			}
	}
	REP(i, 0, n - 1) a[i] = NTTtmp[i] % MOD;
	if (flag < 0)
	{
		static int mem[30];
		const int invn = (mem[lstc] ? mem[lstc] : mem[lstc] = inv(n));
		REP(i, 0, n - 1) a[i] = 1ll * a[i] * invn % MOD;
	}
}
inline int deg(const poly &a) {return (int)a.size() - 1;}
const int BF = 500;const u64 LIM = 17e18;
inline poly mul(poly a, poly b, int need_most)
{
	int l = 1, n = deg(a), m = deg(b);
	if (need_most <= 100 || (n + 1) * (m + 1ll) <= BF)
	{
		static u64 res[BF + 5];
		REP(i, 0, n) if (a[i]) REP(j, 0, min(need_most - i, m)) if (b[j])
		{
			res[i + j] += (u64)a[i] * b[j];
			if (res[i + j] >= LIM) res[i + j] %= MOD;
		}
		a.resize(n + m + 1);
		REP(i, 0, n + m) a[i] = res[i] % MOD, res[i] = 0;
		return a;
	}
	while (l <= n + m) l <<= 1;
	NTT(a, l, 1);NTT(b, l, 1);
	REP(i, 0, l - 1) a[i] = 1ll * a[i] * b[i] % MOD;
	NTT(a, l, -1);
	a.resize(n + m + 1);
	return a;
}

void output(poly a, const char Split = ' ', const char End = '\n')
{
	REP(i, 0, (int)a.size() - 1) printf("%d%c", a[i], i == end_i ? End : Split);
}
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

namespace run
{
	const int maxn = 2e6 + 10;
	int n, v[maxn], t[maxn], it[maxn], f[maxn];

	void getinv(int a[], int res[], int n)
	{
		static int b[maxn];
		b[1] = a[1];REP(i, 2, n) b[i] = 1ll * b[i - 1] * a[i] % MOD;
		res[n] = inv(b[n]);
		DEP(i, n - 1, 1) res[i] = 1ll * res[i + 1] * a[i + 1] % MOD;
		b[0] = 1;
		REP(i, 1, n) res[i] = 1ll * res[i] * b[i - 1] % MOD;
	}
	inline void reduce(int &x) {x += x >> 31 & MOD;}
	void cdq(int l, int r)
	{
		if (l == r)
		{
			if (l % 2 == 0) f[l] = (f[l] + 1ll * f[l >> 1] * t[l >> 1]) % MOD;
			f[l] = 1ll * (MOD + t[l] - f[l]) * it[l] % MOD;
			return;
		}
		int mid = l + r >> 1;
		cdq(l, mid);
		if (mid + 1 + l <= n / 2)
		{
			int need_most = n / 2 - (mid + 1 + l);
			poly F(mid - l + 1, 0), G(r - mid, 0);
			REP(i, l, min(need_most + l, mid))				F[i - l] = f[i];
			REP(i, mid + 1, min(need_most + mid + 1, r))	G[i - (mid + 1)] = t[i];
			if (deg(F) > need_most) F.resize(need_most + 1);
			if (deg(G) > need_most) G.resize(need_most + 1);
			F = mul(F, G, need_most);
			REP(i, 0, min(need_most, deg(F)))
				reduce(f[i + (mid + 1) + l] += F[i] - MOD);
		}
		//		REP(i, mid + 1, r) if (i - (mid + 1) - l >= 0) (f[i] += F[i - (mid + 1) - l]) %= MOD;
		cdq(mid + 1, r);
	}

	int main()
	{
		n = read<int>();
		t[0] = 1;
		REP(i, 1, n) v[i] = read<int>(), t[i] = 1ll * t[i - 1] * v[i] % MOD;
		t[0] = 0;
		getinv(t, it, n);
		cdq(0, n / 2);
		REP(i, n, n)
		{
			u64 res = 0;
			REP(j, 0, i / 2)
			{
				res += 1ll * f[j] * t[i - j];
				if (!(j & 15)) res %= MOD;
			}
			f[i] = (t[i] + MOD - res % MOD) % MOD * it[i] % MOD;			
		}
		cout << 1ll * f[n] * t[n] % MOD << endl;
		return 0;
	}
}


int main()
{
#ifdef CraZYali
	file("C");
#endif
	return run :: main();
}
