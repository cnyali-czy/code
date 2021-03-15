#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;

namespace ex_lucas
{
	const int maxp = 1e6 + 10;
	
	int p[233], k[233], top;
	void split(int x)
	{
		top = 0;
		for (int i = 2; i * i <= x; i++) if (x % i == 0)
		{
			int c = 0;
			while (x % i == 0) c++, x /= i;
			p[++top] = i;k[top] = c;
		}
		if (x > 1) p[++top] = x, k[top] = 1;
	}

	inline i64 d(i64 x, const int p)
	{
		i64 ans = 0;
		while (x >= p)
		{
			i64 fk = x / p;
			ans += fk;x = fk;
		}
		return ans;
	}
	void exgcd(i64 a, i64 b, i64 &x, i64 &y)
	{
		if (!b)
		{
			x = 1;
			y = 0;
			return;
		}
		exgcd(b, a % b, y, x);
		y -= a / b * x;
	}
	inline i64 inv(i64 v, const i64 p)
	{
		i64 x, y;
		exgcd(v >= p ? v % p : v, p, x, y);
		return (x + p) % p;
	}
	inline int fuck(int x, const int p)
	{
		while (x % p == 0) x /= p;
		return x;
	}
	int fac[maxp];
	void init(const int p, const int pk)
	{
		fac[0] = 1;
		REP(i, 1, pk - 1)
			fac[i] = 1ll * fuck(i, p) * fac[i - 1] % pk;
	}
	i64 power_pow(i64 base, i64 b, const int MOD)
	{
		i64 ans = 1;
		while (b)
		{
			if (b & 1) (ans *= base) %= MOD;
			if (b >>= 1) (base *= base) %= MOD;
		}
		return ans;
	}
	inline i64 FAC(i64 n, const int p, const int pk) // don't calc divisor p, return ans % pk
	{
		int k = n / pk;
		cerr << n << ' ' << p << ' ' << power_pow(fac[pk - 1], k, pk) * fac[n % pk] % pk << endl;
		return power_pow(fac[pk - 1], k, pk) * fac[n % pk] % pk;
	}
	namespace CRT
	{
		int r[233], m[233], n;// x % m[i] = r[i]
		void extend(int res, int mod)
		{
			++n;
			r[n] = res;m[n] = mod;
#ifdef CraZYali
			printf("%% %d = %d\n", mod, res);
#endif
		}
		int solve()
		{
			int M = 1;
			REP(i, 1, n) M *= m[i];
			int ans = 0;
			REP(i, 1, n)
				ans = (ans + 1ll * r[i] * (M / m[i]) * inv(M / m[i], m[i])) % M;
			return ans;
		}
	}
	using CRT :: extend;
	int work(i64 n, i64 m, int P)
	{
		split(P);
		REP(fk, 1, top)
		{
			int pk = 1, _p = p[fk], _k = k[fk];REP(i, 1, _k) pk *= _p;
			int a = d(n, _p), b = d(m, _p), c = d(n - m, _p);
			if (a - b - c >= _k) {extend(0, pk);continue;}

			init(_p, pk);
			i64 res = FAC(n, _p, pk) * inv(FAC(m, _p, pk), pk) * inv(FAC(n - m, _p, pk), pk) % pk;
			REP(i, 1, a - b - c) res *= _p;

			extend(res % pk, pk);
		}
		return CRT :: solve();
	}
}

int main()
{
#ifdef CraZYali
	freopen("4720.in", "r", stdin);
	freopen("4720.out", "w", stdout);
#endif
	i64 n, m, p;
	cin >> n >> m >> p;
	cout << ex_lucas :: work(n, m, p) << endl;
	return 0;
}
