#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <unordered_map>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e6 + 10, MOD = 998244353;

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		if (b >>= 1) (base *= base) %= MOD;		
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

int n, m, a[maxn];

int read()
{
	char c = getchar();int res = 0;
	while (!isdigit(c)) c = getchar();
	while ( isdigit(c)) res = res * 10 + (c - 48), c = getchar();
	return res;
}
int bin[maxn], fac[maxn];
void init(int n)
{
	bin[0] = fac[0] = 1;
	REP(i, 1, n)
	{
		bin[i] = 1ll * m * bin[i - 1] % MOD;
		fac[i] = 1ll * i * fac[i - 1] % MOD;
	}
}
void turn(int origin[], int result[], int len)
{
	unordered_map <int, int> id;int N = 0;
	REP(i, 1, len)
	{
		if (!id[origin[i]]) id[origin[i]] = ++N;
		result[i] = id[origin[i]];
	}
}

namespace Hash
{
	const int base = 19491001;
	int lst[maxn], app[maxn];
	int H[maxn], M[maxn], bin[maxn], Inv[maxn];
	void init()
	{
		bin[0] = 1;REP(i, 1, n) bin[i] = 1ll * base * bin[i - 1] % MOD;
		Inv[n] = inv(bin[n]);DEP(i, n - 1, 0) Inv[i] = 1ll * base * Inv[i + 1] % MOD;
		REP(i, 1, n)
		{
			lst[i] = app[a[i]];
			app[a[i]] = i;

			i64 h = 0;
			if (lst[i]) h = i - lst[i];
			H[i] = (H[i - 1] + bin[i] * h) % MOD;
		}
		REP(i, 1, n) app[a[i]] = 0;

		i64 res = 0;
		DEP(i, n, 1)
		{
			if (app[a[i]])	(res -= 1ll * (app[a[i]] - i) * bin[app[a[i]]]) %= MOD;
			if (lst[i])		(res += 1ll * (i - lst[i]) * bin[i]) %= MOD;
			app[a[i]] = i;
			M[i] = res;
		}
	}	
	int get(int l, int r)
	{
		i64 res = ((i64)H[r] - H[l - 1] - M[l]) * Inv[l] % MOD;
		return (res + MOD) % MOD;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> m >> n;
	REP(i, 1, n) a[i] = read();
	init(max(n, m));
	turn(a, a, n);
	Hash :: init();

	static bool vis[maxn];
	i64 ans = 0, n0 = 0;
	REP(i, 1, n)
	{
		if (!vis[a[i]]) {vis[a[i]] = 1;n0++;}
		/*
		static int b[maxn];
		turn(a + n - i, b, i);
		bool ok = 1;
		REP(j, 1, i) if (a[j] != b[j]) {ok = 0;break;}
		*/
		if (Hash :: get(1, i) == Hash :: get(n - i + 1, n)) (ans += 1ll * fac[m - n0] * bin[i]) %= MOD;
	}
	cout << ans * inv(fac[m]) % MOD << endl;
	return 0;
}
