#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)
#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

long long MOD, k;

inline long long fast_mul(long long A, long long B)
{
	A %= MOD;B %= MOD;
	return (A * B - (long long)((long double)A * B / MOD + 1e-4) * MOD + MOD) % MOD;
}

long long exgcd(long long a, long long b, long long &x, long long &y)
{
	if (!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	else
	{
		long long temp = exgcd(b, a % b, y, x);
		y -= a / b * x;
		return  temp;
	}
}

long long power_pow(long long A, long long B)
{
	A %= MOD;
	long long ans = 1, base = A;
	while (B)
	{
		if (B & 1) ans = fast_mul(ans, base);
		base = fast_mul(base, base);
		B >>= 1;
	}
	return (ans + MOD) % MOD;
}

map <long long , long long > X;

long long BSGS(long long A, long long B)
{
	A %= MOD;B %= MOD;
	long long m = ceil(sqrt(MOD));
	long long inv = power_pow(B, MOD - 2);
	long long ans = B;
	REP(i, 0, m - 1)
	{
		X[ans] = i;
		ans = fast_mul(ans, A);
	}
	ans = 1ll << 62ll;
	REP(i, 1, m + 1)
	{
		long long res = power_pow(A, i * m);
		if (X.find(res) != X.end()) chkmin(ans, i * m - X[res]);
	}
	return ans;
}

int main()
{
#ifdef CraZYali
	freopen("U38228.in", "r", stdin);
	freopen("U38228.out", "w", stdout);
#endif
	cin >> k >> MOD;

	cout << BSGS(10, 9ll * k + 1ll);
	
	return 0;
}
