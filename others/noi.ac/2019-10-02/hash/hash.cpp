#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>
#include <cstring>
#include <bits/extc++.h>

#define chkmax(a, b) a = max(a, b)

using namespace std;
const int maxn = 2e6 + 10, MOD = 998244353, split = 2000, P = 233333333;

int n, Hash[maxn], bin[maxn], Inv[maxn];
char s[maxn];

namespace bf
{
	inline void work()
	{
		int ans(0);
		REP(i, 1, n)
		{
			int H(0);
			REP(j, i, n)
			{
				(H += 1ll * (s[j] - 'a' + 1) * bin[j-i] % MOD) %= MOD;
				chkmax(ans, (H + MOD) % MOD);
			}
		}
		printf("%d\n", ans);
	}
}

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

inline void init(const int N = 2e6)
{
	bin[0] = 1;
	REP(i, 1, N) bin[i] = 1ll * bin[i-1] * P % MOD;
	Inv[N] = power_pow(bin[N], MOD - 2);
	DREP(i, N - 1, 0) Inv[i] = 1ll * Inv[i+1] * P % MOD;
}

__gnu_pbds::gp_hash_table <int,int> qaq;

inline int get_hash(int l, int r)
{
	int res(1ll*(Hash[r]-Hash[l-1])%MOD*Inv[l-1]%MOD);
	return (res+MOD)%MOD;
}

inline bool judge(int c)
{
	/*
	REP(l, 1, n)
		REP(r, l, n)
		{
			int ccc = get_hash(l, r);
			if(ccc==c)return 1;
		}return 0;
	*/
	REP(i, 1, n)
	{
		int q = (Hash[i-1] + 1ll * c * bin[i-1] % MOD) % MOD;
		q = (q + MOD) % MOD;
		if (qaq.find(q) != qaq.end() && qaq[q] >= i) return 1;
	}
	return 0;
}

int main()
{
#ifdef CraZYali
	freopen("hash.in", "r", stdin);
	freopen("hash.out", "w", stdout);
#endif
	init();
	int T;
	cin >> T;
	while (T--)
	{
		scanf("%s", s + 1);
		n = strlen(s + 1);
		if (n <= split) bf::work();
		else
		{
			REP(i, 1, n) Hash[i] = (Hash[i-1] + 1ll * (s[i] - 'a' + 1) * bin[i-1] % MOD) % MOD;
//			bf::work();
//			REP(i,1,n)REP(j,i,n)fprintf(stderr,"%d %d %d\n",i,j,get_hash(i,j));cerr<<"================\n";
			qaq.clear();
			REP(i, 1, n)
				qaq[(MOD + Hash[i]) % MOD] = i;
			/*
			   REP(i,1,n)
			   REP(j,i,n)
			   {
			   REP(k,i,j)putchar(s[k]);
			   printf(" :%d\n",get_hash(i,j));
			   }
			   */
			DREP(i, MOD-1, 0)
				//					MOD - 1, 0)
				if (judge(i))
				{
					printf("%d\n", i);
					break;
				}
		}
	}
	return 0;
}
