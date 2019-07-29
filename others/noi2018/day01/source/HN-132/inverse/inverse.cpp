#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;
const int MOD = 998244353, maxn = 266666 + 10;

int m, n, k;
int p[maxn], a[maxn], c[maxn];

int main()
{
	freopen("inverse.in", "r", stdin);
	freopen("inverse.out", "w", stdout);
	c[1] = 1;
	int pren = 1;
	int T;
	scanf("%d", &T);
	while (T --> 0)
	{
		scanf("%d", &n);
		if (n <= 10)
		{
			REP(i, 1, n) scanf("%d", p + i);
			int ans = 0;
			while (next_permutation(p + 1, p + 1 + n))
			{
				int need = 0;
				REP(i, 1, n) need += abs(i - p[i]);
				int cnt = 0;
				REP(i, 1, n)
					REP(j, i + 1, n)
						if (p[i] > p[j]) cnt++;
				if (cnt == need / 2) ans++;
				if (ans >= MOD) ans %= MOD;
			}
			printf("%d\n", ans);
		}
		else
		{
			REP(i, 1, n) scanf("%*d");
			REP(i, pren + 1, n) c[i] = (MOD + (c[i - 1] * (4ll * i - 2) / (i + 1))) % MOD;
			chkmax(pren, n);
			printf("%d\n", c[n] - 1);
			continue;
		}
		
	}

	return 0;
}
