/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.31 19:55
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;
const int MOD = 998244353, maxn = 400 + 5;

int add() {return 0;}
template <typename ...T>
int add(int x, T... y)
{
	int res = x + add(y...);
	if (res >= MOD) res -= MOD;
	return res;
}

inline int sub(int x, int y)
{
	int res = x - y;
	if (res < 0) res += MOD;
	return res;
}

int mul() {return 1;}
template <typename ...T>
int mul(int x, T... y)
{
	long long res = (long long)x * mul(y...);
	if (res >= MOD) res %= MOD;
	return res;
}

int power_pow(int base, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)
template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);
namespace run
{
	int n, l, ans, res, a[maxn][maxn << 1], b[maxn][maxn];
	char s[maxn];
	int main()
	{
		n = read<int>();
		ans = 1;
		REP(i, 1, n)
			REP(j, 1, n) scanf("%1d", a[i] + j);
		REP(i, 1, n)
			REP(j, 1, n)
			{
				scanf("%1d", b[i] + j);
				b[i][j] &= a[i][j];
			}
		REP(i, 1, n)
			REP(j, 1, n) if (i ^ j)
			{
				a[i][i] = add(a[i][i], a[i][j]);
				a[i][j] = sub(0, a[i][j]);
				b[i][i] = add(b[i][i], b[i][j]);
				b[i][j] = sub(0, b[i][j]);
			}
		REP(i, 1, n - 1)
			a[i][i + n] = 1;
		REP(i, 1, n - 1)
		{
			int j;
			if (!a[i][i])
				REP(j, i + 1, n - 1) if (a[j][i])
				{
					ans = sub(0, ans);
					swap(a[i], a[j]);
					break;
				}
			ans = mul(ans, a[i][i]);
			int k = inv(a[i][i]);
			REP(j, i, n + n - 1) a[i][j] = mul(a[i][j], k);
			REP(j, 1, n - 1) if (j ^ i && a[j][i])
			{
				int tmp = a[j][i];
				REP(k, i, n + n - 1) a[j][k] = sub(a[j][k], mul(tmp, a[i][k]));
			}
		} 
		REP(i, 1, n - 1)
			REP(j, 1, n - 1)
			res = add(res, mul(a[j][i + n], b[i][j]));
		cout << mul(ans, res) << endl;
		return 0;
	}
}
int main()
{
#ifdef CraZYali
	file("C");
#endif
	return run::main();
}
