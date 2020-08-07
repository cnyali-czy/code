/*
	Problem:	B.cpp
	Time:		2020-08-06 09:12
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1 << 12;

const int N = 1 << 12;
int cnt[maxn], id[maxn], n;
void init()
{
	REP(i, 1, N - 1)
	{
		cnt[i] = cnt[i >> 1] + (i & 1);
		if (cnt[i] == 6) id[++n] = i;
	}
}
bool in(int x, int p) {return x >> p & 1;}
int helpAlice(int x, int y)
{
	x = id[x];y = id[y];
	REP(i, 1, 12)
		if (in(x, i - 1) && !in(y, i - 1)) return i;
}
int helpBob(int z, int k)
{
	z = id[z];
	return in(z, k - 1);
}
