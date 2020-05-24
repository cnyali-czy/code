/*
	Problem:	sequence.cpp
	Time:		2020-05-24 10:31
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10, MOD = 1e9 + 7;

inline int add(int x, int y) {return (x += y) >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {return (x -= y) <    0 ? x + MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}

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

int n, a[maxn];

const int N = 4e6;
int phi[N + 5], prime[N + 5], p_cnt;
bool notp[N + 5];
struct __init__
{
	__init__()
	{
		phi[1] = 1;
		REP(i, 2, N)
		{
			if (!notp[i]) phi[prime[++p_cnt] = i] = i - 1;
			REP(j, 1, p_cnt)
			{
				int tmp = i * prime[j];
				if (tmp > N) break;
				notp[tmp] = 1;
				if (i % prime[j]) phi[tmp] = phi[i] * (prime[j] - 1);
				else
				{
					phi[tmp] = phi[i] * prime[j];
					break;
				}
			}
		}
	}
}__INIT__;
long long ans = 1;
int Max;
namespace small
{
	bool good[1 << 20];
	int LG[1 << 21];
	void main()
	{
		const int lim = (1 << n) - 1;
		REP(i, 1, 20) LG[1 << i] = i;
		good[0] = 1;
		REP(S, 1, lim) if (good[S & (S - 1)])
		{
			int j = LG[S & -S] + 1;
			bool flag = 1;
			int sum = a[j];
			for (int x = S & (S - 1); x; x &= (x - 1))
			{
				int i = LG[x & -x] + 1;
				sum += a[i];
				if (a[i] & a[j]) {flag = 0;break;}
			}
			if (flag)
			{
				good[S] = 1;
				ans += phi[1 + sum];
			}
		}
	}
}
namespace WA
{
	const int maxa = 2e5 + 10;
	int dp[1 << 18], LG[1 << 20], cnt[maxa], bin[maxa];
	void main()
	{
		int lim = (1 << (int)ceil(log2(Max))) - 1;
		REP(i, 1, n) cnt[a[i]]++;
		bin[0] = 1;
		REP(i, 1, n) bin[i] = (bin[i - 1] << 1) % MOD;
		dp[0] = 1;
		REP(i, 1, n) if (!a[i]) inc(dp[0], dp[0]);
		REP(i, 1, 19) LG[1 << i] = i;
		REP(S, 1, lim)
		{
			for (int x = S & (S - 1); ; x = (x - 1) & S)
			{
				inc(dp[S], 1ll * dp[x] * bin[cnt[S - x]] % MOD);
				if (!x) break;
			}
		}
		ans = 0;
		REP(i, 0, lim) ans += 1ll * dp[i] * phi[i + 1] % MOD;
	}
}
int main()
{
	file("sequence");
	n = read<int>();
	Max = 0;
	REP(i, 1, n) a[i] = read<int>(), chkmax(Max, a[i]);
	if (Max == 1) ans = 1;
	else if (n <= 20) small::main();
	else WA::main();
	cout << ans % MOD << endl;
	return 0;
}
