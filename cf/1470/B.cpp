/*
	Problem:	B.cpp
	Time:		2021-01-07 11:10
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <random>
#include <map>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 1e6 + 10;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn];

int prime[maxn], p_cnt;
bool notp[maxn];
const int MOD = 1000000000000000003;
int bin[maxn];
mt19937 hh;
void init(int n)
{
	REP(i, 2, n)
	{
		if (!notp[i]) prime[++p_cnt] = i;
		REP(j, 1, p_cnt)
		{
			int t = i * prime[j];
			if (t > n) break;
			notp[t] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	REP(i, 0, n)
		bin[i] = (unsigned int)(hh()) * hh() % MOD;
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	init(1e6);
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		map <int, int> cnt;
		REP(i, 1, n)
		{
			int x = a[i], y = 0;
			REP(j, 1, p_cnt)
			{
				int p = prime[j], k = 0;
				if (p * p > x) break;
				while (x % p == 0) x /= p, k++;
				if (k & 1) (y += bin[p]) %= MOD;
			}
			if (x > 1) (y += bin[x]) %= MOD;
			cnt[y]++;
		}
		int ans[2] = {0};
		for (auto i : cnt) ans[0] = max(ans[0], i.second);
		int all = 0;
		for (auto i : cnt)
			if (i.second % 2 == 0 || !i.first) all += i.second;
			else ans[1] = max(ans[1], i.second);
		ans[1] = max(ans[1], all);
		int q = read<int>();
		while (q--)
		{
			int x;scanf("%lld", &x);x = min(x, 1ll);
			printf("%lld\n", ans[x]);
		}
	}
	return 0;
}
