#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
#define int long long
const int maxn = 100 + 10;
int MOD, inv2;

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

int n;
bool vis[maxn];
int a[maxn], bin[maxn * maxn], fac[maxn], invs[maxn], Inv[maxn];

int power_pow(int base, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)
int k;
void dfs(int x)
{
	if (vis[x]) return;
	vis[x] = 1;
	dfs(a[x]);
	k++;
}
int qaq[maxn], top, G[maxn][maxn], cnt[maxn];
__int128 ans;
void calc()
{
	REP(i, 1, top) cnt[qaq[i]]++;
	int way = fac[n], res = 0;
	REP(i, 1, top)
	{
		if (cnt[qaq[i]])
		{
			(way *= Inv[cnt[qaq[i]]]) %= MOD;
			cnt[qaq[i]] = 0;
		}
		(way *= invs[qaq[i]]) %= MOD;
		res += qaq[i] / 2;
		REP(j, i + 1, top) res += G[qaq[i]][qaq[j]];
	}
	ans += way * bin[res] % MOD; 
}
void split(int less, int lst = 1)
{
	qaq[++top] = less;
	calc();
	top--;
	REP(i, lst, less / 2)
	{
		qaq[++top] = i;
		split(less - i, i);
		top--;
	}
}

signed main()
{
#ifdef CraZYali
	file("4128");
#endif
	n = read<int>();
	int base = read<int>();
	MOD = read<int>();inv2 = (MOD + 1) / 2;
	bin[0] = fac[0] = invs[0] = invs[1] = a[1] = fac[1] = Inv[0] = Inv[1] = 1;
	REP(i, 2, n)
	{
		a[i] = i;
		fac[i] = i * fac[i - 1] % MOD;
		invs[i] = (MOD - MOD / i) * invs[MOD % i] % MOD;
		Inv[i] = invs[i] * Inv[i - 1] % MOD;
	}
	REP(i, 1, n * n) bin[i] = 1ll * bin[i - 1] * base % MOD;
	REP(i, 1, n) REP(j, i, n) G[i][j] = G[j][i] = __gcd(i, j);
	split(n);
	cout << (int)(ans % MOD * inv(fac[n]) % MOD) << endl;
	return 0;
}
