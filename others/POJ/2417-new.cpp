#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long

using namespace std;

int MOD, A, B, t;
int mod(int x) {if (x < 0) return (x % MOD + MOD) % MOD;return x >= MOD ? x % MOD : x;}

__gnu_pbds :: gp_hash_table <int, int> M;

int power_pow(int a, int b)
{
	int ans = 1, base = a % MOD;
	while (b)
	{
		if (b & 1) ans = mod(ans * base);
		base = mod(base * base);
		b >>= 1;
	}
	return mod(ans);
}

signed main()
{
#ifdef CraZYali
	freopen("2417-new.in", "r", stdin);
	freopen("2417-new.out", "w", stdout);
#endif
	while (scanf("%lld%lld%lld", &MOD, &A, &B) != EOF)
	{
		if (A == 0)
		{
			if (!B) printf("0\n");
			else printf("no solution\n");
			continue;
		}
		M.clear();
		t = ceil(sqrt(MOD));
		register int now = mod(B);
		REP(j, 0, t)
		{
			M[now] = j;
			now = mod(now * A);
		}
		now = power_pow(A, t);
		int kkk = 1, ans = 1ll << 60ll;bool flag = 0;
		REP(i, 0, t)
		{
			int temp = M[kkk];
			if (i * t - temp >= 0 && temp)
			{
				flag = 1;
				chkmin(ans, i * t - temp);
			}
			kkk = mod(kkk * now);
		}
		if (flag) printf("%lld\n", ans);
		else puts("no solution");
	}

	return 0;
}
