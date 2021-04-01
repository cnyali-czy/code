#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 300 + 5, M = 2520;

int n, a[maxn][maxn];
inline int read() {int x;scanf("%d", &x);return x;}

bool isprime(int x)
{
	if (x <= 2) return (x == 2);
	for (int i = 2; i * i <= x; i++) if (x % i == 0) return 0;
	return 1;
}
int p[maxn], p_cnt, pk_p[maxn], mx[maxn];
struct __init__
{
	__init__(const int n = 120)
	{
		mx[0] = 1;
		REP(i, 2, n) if (isprime(i))
		{
			p[++p_cnt] = i;
			for (int k = 1, pk = i; pk <= n; k++, pk *= i)
			{
				pk_p[pk] = p_cnt;
				mx[p_cnt] = pk;
			}
		}
	}
}__INIT__;
int calc(int R)
{
	int ans = 0;
	static int f[maxn][maxn];
	REP(i, 1, 120)
	{
		int m = 0;static int g[maxn];
		static bool vis[maxn];
		REP(j, 0, i - 1) vis[j] = 0;
		for (int j = R % i; !vis[j]; j = (j + M) % i)
		{
			vis[j] = 1;
			g[m++] = a[i][j];
		}
		int k = pk_p[m];
		REP(j, 0, mx[k] - 1) f[k][j] += g[j % m];
	}
	REP(i, 0, p_cnt)
	{
		int res = 0;
		REP(j, 0, mx[i] - 1) res = max(res, f[i][j]), f[i][j] = 0;
		ans += res;
	}
	return ans;
}
int main()
{
#ifdef CraZYali
	freopen("silence.in", "r", stdin);
	freopen("silence.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		int p = read();
		REP(j, 0, p - 1) a[p][j] += read();
	}
	int ans = 0;
	REP(i, 0, M - 1) ans = max(ans, calc(i));
	cout << ans << endl;
	return 0;
}
