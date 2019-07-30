#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>
#define int long long 

using namespace std;
const int MOD = 10007, maxn = MOD + 5;

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

int power_pow(int a, int b)
{
	int ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

int fac[maxn], Inv[maxn];
int C(int n, int m) {return n < m ? 0 : fac[n] * Inv[m] % MOD * Inv[n-m] % MOD;}
int lucas(int n, int m)
{
	if (!m) return 1;
	return C(n % MOD, m % MOD) * lucas(n / MOD, m / MOD) % MOD;
}

signed main()
{
#ifdef CraZYali
	file("2982");
#endif
	fac[0] = Inv[0] = 1;
	REP(i, 1, MOD-1) fac[i] = fac[i-1] * i % MOD;
	Inv[MOD-1] = inv(fac[MOD-1]);
	DREP(i, MOD - 2, 1) Inv[i] = Inv[i+1] * (i + 1) % MOD;
	int T = read<int>();
	while (T--)
	{
		int n = read<int>(), m = read<int>();
		cout << (lucas(n, m) + MOD) % MOD << endl;
	}
	return 0;
}
