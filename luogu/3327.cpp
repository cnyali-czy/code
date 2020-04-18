#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(3)
/*
	Problem:	3327.cpp
	Time:		2020-04-05 22:14
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i = s; i <= e; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkMin(a, b) (a > (b) ? a = (b) : a)

#include <math.h>
#include <stdio.h>
#define maxn (50001)
#define isdigit(c) ('0' <= c && c <= '9')
#define nc getchar
#ifndef CraZYali
#define getchar getchar_unlocked
#endif
int read()
{
	register int ans = 0;
	char c = nc();
	while (!isdigit(c)) c = nc();
	while (isdigit(c)) ans = (ans << 1) + (ans << 3) + (c ^ 48), c = nc();
	return ans;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

unsigned short Prime[5134], p_cnt;
char notp[maxn];

struct info
{
	unsigned short E;
	int s, smu;
	char mu;
}I[maxn];
void init(int n)
{
	I[1].mu = I[1].smu = 1;
	I[1].s = 1;
	for (register int i = 2; i <= n; i++)
	{
		if (!notp[i])
		{
			I[Prime[++p_cnt] = i].mu = -1;
			I[i].s = 2;
			I[i].E = 1;
		}
		REP(j, 1, p_cnt)
		{
			int tmp = i * Prime[j];if (tmp > n) break;
			notp[tmp] = 1;
			if (i % Prime[j])
			{
				I[tmp].mu = -I[i].mu;
				I[tmp].E = 1;
				I[tmp].s = I[i].s << 1;
			}
			else
			{
				I[tmp].E = I[i].E + 1;
				I[tmp].s = I[i].s / (I[i].E + 1) * (I[i].E + 2);
				break;
			}
		}
		I[i].smu = I[i-1].smu + I[i].mu;
		I[i].s += I[i-1].s;
	}
}
int n, m;
int Min(const int x, const int y) {return x < y ? x : y;}
void write(const long long x) {if (x / 10) write(x / 10);putchar(x % 10 + 48);}
int main()
{
#ifdef CraZYali
	file("3327");
#endif
	init(50000);
	register int T = read();
	while (T--)
	{
		int N = read(), M = read();
		if (N > M) N ^= M ^= N ^= M;
		const register int n = N, m = M;
		register long long ans = 0;
		register int mid = Min((int)sqrt(m + .5), n);
		REP(i, 1, mid) ans += (long long)I[i].mu * I[n / i].s * I[m / i].s;
		for (register int d = mid + 1, j; d <= n; d = j + 1)
		{
			j = Min(m / (m / d), n / (n / d));
			ans += (long long)(I[j].smu - I[d-1].smu) * I[n / d].s * I[m / d].s;
		}
		write(ans);putchar('\n');
	}
	return 0;
}
