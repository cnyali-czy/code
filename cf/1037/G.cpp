/*
	Problem:	G.cpp
	Time:		2020-10-21 20:54
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

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

char s[maxn];
int n, q, pre[maxn][26], suf[maxn][26];

int f[maxn][27], g[maxn], mem[27];
inline int mex(int x) {return __builtin_ctz(~x);}
void set(int &x, int y) {x |= (1 << y);}
int calc(int l, int r, int c, int flag)
{
	if (l > r) return 0;
	if (~mem[c]) return mem[c];
	int s = 0;
	REP(i, 0, 25)
	{
		int L = suf[l][i], R = pre[r][i];
		if (L <= R)
			set(s, g[L] ^ g[R] ^ (flag ? calc(l, L - 1, i, 1) : f[L - 1][c]) ^ (flag ? f[r][i] : calc(R + 1, r, i, 0)));
	}
	return mem[c] = mex(s);
}

int main()
{
#ifdef CraZYali
	file("G");
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	REP(i, 1, n)
	{
		REP(j, 0, 25) pre[i][j] = pre[i - 1][j];
		pre[i][s[i] - 'a'] = i;
	}
	REP(i, 0, 25) suf[n + 1][i] = n + 1;
	DEP(i, n, 1)
	{
		REP(j, 0, 25) suf[i][j] = suf[i + 1][j];
		suf[i][s[i] - 'a'] = i;
	}
	//f[i][j] : 字符j上一次出现的位置+1到i的这一段的sg值
	//g[i] : 
	REP(i, 1, n)
	{
		g[i] = f[i - 1][s[i] - 'a'] ^ g[pre[i - 1][s[i] - 'a']];
		memset(mem, -1, sizeof mem);
		REP(j, 0, 25) f[i][j] = calc(pre[i][j] + 1, i, j, 0);
	}
	REP(Case, 1, read<int>())
	{
		int l = read<int>(), r = read<int>();
		memset(mem, -1, sizeof mem);
		puts(calc(l, r, 26, 1) ? "Alice" : "Bob");
	}
	return 0;
}
