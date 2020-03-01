/*
	Problem:	4424.cpp
	Time:		2020-03-01 10:13
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bitset>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5000 + 5, maxm = 5000 + 10, MOD = 1e9 + 7;

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

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

int n, m, q, bin[maxn];

char str[maxn];
int f[maxn], g[maxn], cnt[2], s[maxn], t[maxn];

struct __init__
{
	__init__(const int n = maxn - 10)
	{
		bin[0] = 1;
		REP(i, 1, n) bin[i] = add(bin[i-1], bin[i-1]);
	}
}__INIT__;

int main()
{
#ifdef CraZYali
	file("4424");
#endif
	n = read<int>();m = read<int>();q = read<int>();
	REP(i, 1, m) f[i] = i;
	REP(i, 1, n)
	{
		scanf("%s", str + 1);
		cnt[0] = 0;cnt[1] = m;
		REP(j, 1, m)
			if (str[j] == '1') inc(s[j], bin[i - 1]);
			else cnt[0]++;
		DEP(j, m, 1) g[cnt[str[f[j]] - '0']--] = f[j];
		swap(f, g);
	}
	REP(i, 1, m) t[i] = s[f[i]];
	t[m + 1] = bin[n];
	while (q--)
	{
		scanf("%s", str + 1);
		int l = 0, r = m + 1;
		REP(i, 1, m) if (str[f[i]] == '1') {r = i;break;}
		DEP(i, m, 1) if (str[f[i]] == '0') {l = i;break;}
		if (l > r) puts("0");
		else cout << sub(t[r], t[l]) << '\n';
	}
	return 0;
}
