#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e7 + 10, MOD = 998244353;

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

i64 n, a1, A, B, P;
int m, a[maxn], lst[maxn];

i64 cnt[maxn];

const int maxm = 100 + 5;
#define poly vector <int>
inline int deg(const poly &f) {return (int)f.size() - 1;}
const unsigned i64 End = 17e18;
poly operator * (poly a, poly b)
{
	static unsigned i64 res[maxm << 1];
	int n = deg(a), m = deg(b);
	REP(i, 0, n) if (a[i])
		REP(j, 0, m) if (b[j])
		{
			res[i + j] += 1ll * a[i] * b[j];
			if (res[i + j] >= End) res[i + j] %= MOD;
		}
	a.resize(n + m + 1);
	REP(i, 0, n + m)
	{
		if (res[i] >= MOD) res[i] %= MOD;
		a[i] = res[i];res[i] = 0;
	}
	return a;
}
poly operator ^ (poly base, int b)
{
	int n = deg(base);
	poly ans(1, 1);
	while (b)
	{
		if (b & 1)
		{
			ans = ans * base;
			if (deg(ans) > n) ans.resize(n + 1);
		}
		base = base * base;
		base.resize(n + 1);
		b >>= 1;
	}
	return ans;
}
int Cnt[maxm];
int Inv[maxm];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> m;
	cin >> a1 >> A >> B >> P;
	Inv[0] = Inv[1] = 1;
	REP(i, 2, m)
		Inv[i] = 1ll * Inv[MOD % i] * (MOD - MOD / i) % MOD;
	REP(i, 2, m)
		Inv[i] = 1ll * Inv[i - 1] * Inv[i] % MOD;
	lst[a[1] = a1] = 1;
	cnt[a1] = 1;
//	cout << a1 << ' ' ;
	DEBUG;
	REP(i, 2, min(n, P))
	{
		a[i] = (a[i - 1] * A + B) % P + 1;
//		cout << a[i] << ' ' ;
		if (lst[a[i]])
		{
//			cerr << i << ' ' << lst[a[i]] << endl;
			int len = i - lst[a[i]];
			i64 times = (n - i + 1) / len;
//			cerr << times << endl;
			REP(j, lst[a[i]], i - 1)
				cnt[a[j]] += times;
			REP(j, 1, (n - i + 1) % len) cnt[a[lst[a[i]] + j - 1]]++;
			break;
		}
		else lst[a[i]] = i;
		cnt[a[i]]++;
	}
	DEBUG;
//	cout << endl;
	poly Ans(1, 1);
	REP(i, 1, P) if (cnt[i])
		Cnt[min(i, m)] = (Cnt[min(i, m)] + cnt[i]) % MOD;
	DEBUG;
	poly qaq(m + 1, 0);
	DEBUG;
	REP(i, 0, m)
	{
		qaq[i] = Inv[i];
		if (Cnt[i])
		{
			auto tmp = qaq ^ Cnt[i];
			Ans = Ans * tmp;
			if (deg(Ans) > m) Ans.resize(m + 1);
		}
	}
	Ans.resize(m + 1);
	int fac = 1;
	REP(i, 1, m) fac = 1ll * i * fac % MOD;
	cout << 1ll * fac * Ans[m] % MOD << endl;
	return 0;
}
