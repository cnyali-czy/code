#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, MOD = 1e9 + 7;

int power_pow(long long base, int b)
{
	long long ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)
const int alpha = 26, inva = inv(alpha);

int fac[maxn], Inv[maxn];
long long bin25[maxn], bin26[maxn], Inv26[maxn];
struct __init__
{
	__init__(const int n = 1e5)
	{
		bin25[0] = bin26[0] = fac[0] = 1;
		REP(i, 1, n)
		{
			bin25[i] = bin25[i-1] * 25 % MOD;
			bin26[i] = bin26[i-1] * 26 % MOD;
			fac[i] = 1ll * fac[i-1] * i % MOD;
		}
		Inv[n] = inv(fac[n]);
		Inv26[n] = inv(bin26[n]);
		DREP(i, n-1, 0)
		{
			Inv[i] = 1ll * Inv[i+1] * (i + 1) % MOD;
			Inv26[i] = 26ll * Inv26[i+1] % MOD;
		}
	}
}__INIT__;
inline int C(int n, int m) {return n < m ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n-m] % MOD;}
#include <unordered_map>

int *sum[maxn];
bool vis[maxn];
int lst[maxn], qaq[maxn];
inline int calc(int n, int len)
{
	if (!vis[len])
	{
		vis[len] = 1;
		sum[len] = new int[100005];
		REP(i, 0, len - 1)
			sum[len][i] = 0;
		REP(i, len, 100000)
			sum[len][i] = (sum[len][i-1] + C(i-1, len-1) * bin25[i - len] % MOD * Inv26[i] % MOD) % MOD;
	}
	return (bin26[n] * sum[len][n] % MOD + MOD) % MOD;
}
int n;
char s[maxn];
int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	REP(i, 1, 100000) lst[i] = i-1;
	int m;
	cin >> m;
	scanf("%s", s);n = strlen(s);
	while (m--)
	{
		int opt;scanf("%d", &opt);
		if (opt == 1)
		{
			n = 0;
			char c = getchar();
			while (!isalpha(c)) c = getchar();
			while (isalpha(c)) c = getchar(), n++;
		}
		else
		{
			int len;scanf("%d", &len);
			printf("%d\n", len < n ? 0 : calc(len, n));
		}
	}
	return 0;
}
