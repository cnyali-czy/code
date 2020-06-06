#define REP(i, s, e) for (register i64 i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register i64 i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
#define i64 long long 

i64 read()
{
	i64 x;
	scanf("%lld", &x);
	return x;
}
i64 read_mod(const i64 MOD = 998244353 - 1)
{
	register char c = getchar();
	i64 res = 0;
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) res = (res * 10 + c - 48) % MOD, c = getchar();
	return res;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int power_pow(i64 base, i64 b, const i64 MOD = 998244353)
{
	b %= (MOD - 1);
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}

namespace Case1
{
	void work()
	{
		register int T = read();
		while (T--)
			printf("%lld\n", power_pow(19, read_mod()));
	}
}
namespace Case2
{
	void work()
	{
		REP(i, 1, read())
			printf("%lld\n", power_pow(19, read_mod(1145140), 1145141));
	}
}
inline i64 mul(i64 a, i64 b, const i64 p)
{
	i64 res = (a * b - (i64)((long double)a / p * b) * p) % p;
	if (res < 0) res += p;
	return res;
}

inline i64 Rand() {return 1ll * rand() * rand();}
inline i64 Randint(i64 l, i64 r) {return Rand() % (r - l + 1) + l;}
namespace Miller_Rabin
{
	int totst[] = {2, 3, 13, 17, 19, 23};

	i64 power_pow(i64 base, i64 b, i64 p)
	{
		i64 ans = 1;
		while (b)
		{
			if (b & 1) ans = mul(ans, base, p);
			base = mul(base, base, p);
			b >>= 1;
		}
		return ans;
	}

	i64 miller_rabin(i64 n)
	{
		if (n < 3) return n == 2;
		if (n % 2 == 0) return 0;
		i64 a = n - 1, b = 0;
		while (!(a & 1)) a >>= 1, b++;
		for (i64 x : totst)
		{
			if (x == n) return 1;
			i64 v = power_pow(x, a, n);
			if (v == 1 || v == n - 1) continue;
			for (int j = 0; j <= b; j++)
			{
				if (v == n - 1) break;
				if (j == b) return 0;
				v = mul(v, v, n);
			}
		}
		return 1;
	}
}
namespace Case3
{
	void work()
	{
		register int T = read();
		while (T--) printf("%lld\n", Miller_Rabin :: power_pow(19, read(), 5211600617818708273));
	}
}
namespace Case4
{
	const int A = 55244, B = 45699, MOD = 998244353;
	int mem[A + B + 10];
	struct __init__
	{
		__init__()
		{
			mem[0] = 1;
			REP(i, 1, A + B) mem[i] = 19 * mem[i - 1] % MOD;
		}
	}__INIT__;
	void work()
	{
		register int T = read();
		while (T--)
		{
			i64 n = read();
			printf("%d\n", mem[n <= A ? n : (n - A) % B + A]);
		}
	}
}
using Miller_Rabin :: miller_rabin;
namespace Pollard_Rho
{
	inline i64 f(i64 x, i64 c, i64 n) {return (mul(x, x, n) + c) % n;}
	i64 pollard_rho(i64 n)
	{
		if (n % 2 == 0) return 2;
		i64 c = Rand() % (n - 1) + 1;
		for (i64 goal = 1, s = 0, t = 0;;goal <<= 1, s = t)
		{
			i64 val = 1;
			REP(stp, 1, goal)
			{
				t = f(t, c, n);
				val = mul(val, abs(s - t), n);
				if (stp % 127 == 0)
				{
					i64 d = __gcd(val, n);
					if (d > 1) return d;
				}
			}
			i64 d = __gcd(val, n);
			if (d > 1) return d;
		}
	}
}
using Pollard_Rho :: pollard_rho;
namespace Case5
{
	void work()
	{
		REP(i, 1, read())
		{
			i64 l = read(), r = read();
			while (l <= r)
			{
				putchar(miller_rabin(l) ? 'p' : '.');
				l++;
			}
			putchar(10);
		}
	}
}
namespace Case6
{
	const int N = 1e6;
	int prime[N + 5], Mu[N + 5], p_cnt;
	bool notp[N + 5];
	struct __init__
	{
		__init__()
		{
			Mu[1] = 1;
			REP(i, 2, N)
			{
				if (!notp[i]) Mu[prime[++p_cnt] = i] = -1;
				REP(j, 1, p_cnt)
				{
					int tmp = i * prime[j];if (tmp > N) break;
					notp[tmp] = 1;
					if (i % prime[j]) Mu[tmp] = -Mu[i];
					else break;
				}
			}
		}
	}__INIT__;
	inline char C(int mu)
	{
		if (mu == -1) return '-';
		if (mu ==  0) return '0';
		if (mu ==  1) return '+';
		return 'x';
	}
	vector <int> v[N + 5];
	void work()
	{
		register int T = read();
		while (T--)
		{
			i64 l = read(), r = read();
			REP(i, l, min(r, N * 1ll)) putchar(C(Mu[i]));
			chkmax(l, N + 1);
			if (l <= r)
			{
				REP(i, 0, r - l) v[i].clear();
				REP(j, 1, p_cnt)
					REP(k, (l + prime[j] - 1) / prime[j], r / prime[j])
					v[k * prime[j] - l].emplace_back(prime[j]);
				REP(i, l, r)
				{
					int res = 1;
					i64 cur = i;
					for (auto d : v[i - l])
					{
						cur /= d;
						if (cur % d == 0) {res = 0;goto Out;}
						res = -res;
					}
					if (cur > 1)
					{
						i64 r = sqrt(cur + .5);
						if (r * r == cur) res = 0;
						else if (miller_rabin(cur)) res = -res;
					}
Out:				putchar(C(res));					
				}
			}
			puts("");
		}
	}
}
namespace Case7
{
	vector <i64> solve(i64 n)
	{
		if (n == 1) return vector <i64> (0);
		if (miller_rabin(n)) return vector <i64> (1, n);
		i64 m = pollard_rho(n);
		auto v1 = solve(m);
		auto v2 = solve(n / m);
		v1.insert(v1.end(), v2.begin(), v2.end());
		sort(v1.begin(), v1.end());
		v1.resize(unique(v1.begin(), v1.end()) - v1.begin());
		return v1;
	}
	vector <i64> o;
	i64 n;
	bool judge(i64 g)
	{
		for (auto i : o) if (power_pow(g, (n - 1) / i, n) == 1) return 0;
		return 1;
	}
	int qaq[13123110];
	void work()
	{
		const int p = 13123111;
		int bin = 1;
		REP(i, 0, p - 2)
		{
			qaq[bin] = i;
			bin = bin * 6ll % p;
		}
		register int T = read();
		int lst = 0;
		while (T--)
		{
			i64 l(read()), r(read());
			if (l == 233333333)
				n = 1515343657;
			else n = read();
			if (n == p)
			{
				REP(i, l, r) putchar(__gcd(qaq[i] + 0ll, n - 1) == 1 && i != n - 1 ? 'g' : '.');
			}
			else
			{
				o = solve(n - 1);
				REP(i, l, r)
				{
					bool flag = judge(i);
					putchar(flag ? 'g' : '.');
				}
			}
			puts("");
		}
	}
}
int main()
{
#ifdef CraZYali
	freopen("software6.in", "r", stdin);
	freopen("software.out", "w", stdout);
#endif
	string Case;
	cin >> Case;
	if (Case == "1_998244353") Case1 :: work();
	if (Case == "1?") Case2 :: work();
	if (Case == "1?+") Case3 :: work();
	if (Case == "1wa_998244353") Case4 :: work();
	if (Case == "2p") Case5 :: work();
	if (Case == "2u") Case6 :: work();
	if (Case == "2g") Case7 :: work();
	if (Case == "2g?") Case7 :: work();
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
