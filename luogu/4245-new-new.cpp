#pragma GCC optimize(2)
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
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
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
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
/*
 * File Name:	4245-new-new.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.31 20:08
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
const int maxn = 2e5 + 10;
inline char Getchar()
{
	static char buf[100000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template <typename T> inline T read()
{
	T ans(0);
	char c(Getchar());
	while (!isdigit(c)) c = Getchar();
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = Getchar();
	}
	return ans;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, m, MOD, f[maxn], g[maxn], ans[maxn];
inline int add(int x, int y)
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
inline void inc(int &x, int y)
{
	x += y;
	if (x >= MOD) x -= MOD;
}
inline void dec(int &x, int y)
{
	x -= y;
	if (x < 0) x += MOD;
}


__int128 tmp[maxn];
void solve(int *f, int *g, int *ans, int n)
{
	if (n <= 28)
	{
		REP(i, 0, n + n) tmp[i] = 0;
		REP(i, 0, n) if (f[i])
		{
			const __int128 ccc = f[i];
			REP(j, 0, n) tmp[i + j] += ccc * g[j];
		}
		REP(i, 0, n + n) inc(ans[i], tmp[i] % MOD);
		return;
	}
	const int nn = n / 2;
	solve(f, g, ans, nn);
	register int *ff, *gg, *ans2, *ans3;
	ff = new int[nn + 1];
	gg = new int[nn + 1];
	REP(i, 0, n - 1 - nn)
	{
		ff[i] = add(f[i], f[i + nn + 1]);
		gg[i] = add(g[i], g[i + nn + 1]);
	}
	REP(i, n - nn, nn) ff[i] = f[i], gg[i] = g[i];
	ans3 = new int[n + 1];
	REP(i, 0, n) ans3[i] = 0;
	solve(ff, gg, ans3, nn);

	ans2 = new int[n + 1];
	REP(i, 0, n) ans2[i] = 0;
	solve(f + nn + 1, g + nn + 1, ans2, n - nn - 1);

	REP(i, 0, n)
		dec(ans3[i], add(ans[i], ans2[i]));
	int pos3 = 0, pos2 = - nn - 1;
	REP(i, nn + 1, n + n)
	{
		if (pos3 <= n) inc(ans[i], ans3[pos3]);
		if (0 <= pos2) inc(ans[i], ans2[pos2]);
		pos3++;pos2++;
	}
}

signed main()
{
#ifdef CraZYali
	file("4245-new-new");
#endif
	n = read<int>();
	m = read<int>();
	MOD = read<int>();
	const int mod = MOD;
	REP(i, 0, n)
	{
		f[i] = read<int>();
		if (f[i] >= mod) f[i] %= mod;
	}
	REP(i, 0, m)
	{
		g[i] = read<int>();
		if (g[i] >= mod) g[i] %= mod;
	}
	int anslen = n + m;
	chkmax(n, m);
	solve(f, g, ans, n);
	REP(i, 0, anslen) cout << ans[i] << ' ';
	return 0;
}
