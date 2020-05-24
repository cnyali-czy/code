/*
	Problem:	magic.cpp
	Time:		2020-05-24 08:51
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <bitset>

using namespace std;
const int maxn = 100 + 5;

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

int n, m, q;
unsigned f[maxn];

bitset <maxn> G[maxn], Tmp[maxn];

bitset <maxn> bin[40][maxn], qaq;
bool Qaq[maxn];

void power_pow(unsigned k)
{
	k--;
	qaq = G[1];
//	REP(i, 1, n) qaq[i] = G[1][i];
	for (int ccc = 0; k; k >>= 1, ccc++) if (k & 1)
	{
		REP(i, 1, n)
			Qaq[i] = (qaq & bin[ccc][i]).count() & 1;
		REP(i, 1, n) qaq[i] = Qaq[i];
	}
}

int main()
{
	file("magic");
	n = read<int>();m = read<int>();q = read<int>();
	REP(i, 1, n) f[i] = read<unsigned>();
	while (m--)
	{
		int u(read<int>()), v(read<int>());
		G[u].set(v);G[v].set(u);
	}
	REP(i, 1, n) bin[0][i] = G[i];
	REP(ccc, 1, 34)
	{
		REP(i, 1, n)
			REP(j, 1, n)
			if ((bin[ccc - 1][i] & bin[ccc - 1][j]).count() & 1) bin[ccc][i].flip(j);
	}
	REP(Case, 1, q)
	{
		unsigned a = read<unsigned>();
		if (!a)
		{
			cout << f[1] << '\n';
			continue;
		}
		power_pow(a);
		unsigned ans = 0;
		REP(i, 1, n) if (qaq.test(i)) ans ^= f[i];
		cout << ans << '\n';
	}
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	return 0;
}
