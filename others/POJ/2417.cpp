#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)
#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

long long MOD, a, b;

namespace MyHash
{
	const long long P1 = 2000003, P2 = 19260817;
	long long Hash(long long x)
	{
		register long long ans = 1;
		while (x)
		{
			ans = ans * P2 + (x % 10);
			ans %= P1;
			x /= 10;
		}
		return (ans + P1) % P1;
	}
	struct Hash_Table
	{
		long long bg[P1 + 5], ne[P1 + 5], e;
		pair <long long, long long> to[P1 + 5];
		inline void add(long long x, long long y)
		{
			register long long H = Hash(x);
			e++;
			to[e] = make_pair(x, y);
			ne[e] = bg[H];
			bg[H] = e;
		}

		void insert(long long val, long long i)
		{
			add(val, i);
		}

		void clear_e() {e = 0;}
		void del(long long key) {bg[Hash(key)] = 0;}
	}H;
}
long long power_pow(long long a, long long b)
{
	a %= MOD;
	register long long ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}

int main()
{
#ifdef CraZYali
	freopen("2417.in", "r", stdin);
	freopen("2417.out", "w", stdout);
#endif
	while (scanf("%lld%lld%lld", &MOD, &a, &b) != EOF)
	{
		if (a == 0)
		{
			if (b) printf("no solution\n");
			else printf("1\n");
			continue;
		}
		MyHash::H.clear_e();
		register long long t = sqrt(MOD) + 1;
		REP(j, 0, t - 1)
		{
			register long long val = power_pow(a, j) * b % MOD;
			val = (val + MOD) % MOD;
			MyHash::H.insert(val, j);
		}
		register bool flag = 0;
		register long long ans = 1ll << 60ll;
		REP(i, 0, t)
		{
			register long long val = power_pow(power_pow(a, i), t);
			register long long H = MyHash::Hash(val);
			for (register long long I = MyHash::H.bg[H]; I ; I = MyHash::H.ne[I])
				if (MyHash::H.to[I].first == val)
				{
					register long long j = MyHash::H.to[I].second;
					if (i * t - j >= 0)
					{
						flag = 1;
						chkmin(ans, i * t - j);
					}
				}
		}
		if (!flag) printf("no solution\n");
		else printf("%lld\n", ans);
		
		fflush(stdout);
		REP(j, 0, t - 1)
		{
			register long long val = power_pow(a, j) * b % MOD;
			MyHash::H.del((val + MOD) % MOD);
		}
	}
	return 0;
}
