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

int m, n, k;

namespace run
{
	const int MOD = 1e9 + 7, inv2 = MOD + 1 >> 1;
	inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
	const int maxn = 2000 + 10;
#define i64 long long
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
	int f[maxn][maxn], nex[maxn], val[maxn];
	int main()
	{
		n = read<int>();k = read<int>();
		f[n][(k - 1) % n + 1] = 1; 
		DEP(i, n, 2)
		{
			REP(j, 1, i) nex[(j + k - 1) % i + 1] = j, val[j] = 0;
//			REP(i, 0, n) printf("%d%c", nex[i],i==n?'\n':' ');
			REP(j, 1, i) if (!val[j])
			{
				int nex = run :: nex[j], num = f[i][j], p = inv2;
				do
				{
					inc(num, 1ll * p * f[i][nex] % MOD);
					p = 1ll * p * inv2 % MOD;
					nex = run :: nex[nex];
//					cout << nex << ' ' << num << ' '<<p<<endl;
				} while (nex ^ j);
//				cout<<p<<endl;
				val[j] = 1ll * inv(MOD + 1 - p) * num % MOD;
//				cout << val[j] << endl;
				nex = j;
				while (run :: nex[nex] ^ j)
				{
					val[run :: nex[nex]] = 2ll * (MOD + val[nex] - f[i][nex]) % MOD;
					nex = run :: nex[nex];
				}
			}
			REP(j, 2, i)
			{
				int nex = (j + (k % (i - 1)) - 1) % i + 1;
				if (nex >= j) -- nex;
				f[i - 1][nex] = 1ll * val[j] * inv2 % MOD;
			}
		}
//		REP(i,0,n)REP(j,0,n)printf("%lld%c",(f[i][j]+MOD)%MOD,j==n?'\n':' ');
		cout << f[1][1] << endl;
		return 0;
	}
}
int main()
{
#ifdef CraZYali
	file("C");
#endif
	return run :: main();
}
