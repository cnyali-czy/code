/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.29 14:12
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cassert>
#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 20 + 5, MOD = 998244353, maxm = 2000 + 10;

int add(int x, int y)
{
	int res = x + y;
	if (res >= MOD) res -= MOD;
	return res;
}
inline int sub(int x, int y)
{
	int res = x - y;
	if (res < 0) res += MOD;
	return res;
}
inline int mul(int x, int y)
{
	long long res = (long long)x * y;
	if (res >= MOD) res %= MOD;
	return res;
}

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
int n, len[maxn], bin[maxm];
char s[100];
int pop[(1 << 20) + 5], lg[(1 << 20) + 5], stack[maxn], top;

struct __init__
{
	__init__(const int n = maxm - 10)
	{
		bin[0] = 1;
		REP(i, 1, n) bin[i] = mul(bin[i-1], 2);
		REP(i, 1, 20) lg[1 << i] = i;
		REP(i, 1, (1 << 20)) pop[i] = pop[i >> 1] + (i & 1);
	}
}__INIT__;

int z[100], o[100];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	int ask = 0;
	REP(i, 0, n - 1)
	{
		scanf("%s", s);
		int u = (1 << i);
		REP(j, 0, (len[i] = strlen(s)) - 1)
			if (s[j] == '?') ask++;
			else if (s[j] == '1') o[j] |= u;
			else z[j] |= u;
	}
	int ans = 0;
	REP(S, 1, (1 << n) - 1)
	{
		int Min = 1e9, flag = MOD - 1, hd = 0;
		top = 0;
		for (int x = S; x; x &= (x - 1))
		{
			int j = lg[x & -x];
			chkmin(Min, len[j]);
			flag = MOD - flag;
		}
		ans = add(ans, mul(flag, bin[ask]));
		REP(j, 0, Min - 1)
		{
			int c0 = pop[z[j] & S], c1 = pop[o[j] & S];
			hd += pop[S] - c0 - c1 - (!c0 && !c1);
			if (c0 && c1) break;
			if (ask >= hd) ans = add(ans, mul(flag, bin[ask - hd]));
			else break;
		}
	}
	cout << ans << endl;
	return 0;
}
