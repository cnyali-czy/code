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
unsigned f[maxn], F[maxn], tmp[maxn];

bitset <maxn> G[maxn], T[maxn], Tmp[maxn], res[maxn], base[maxn];

void turn_matrix()
{
	REP(i, 1, n) Tmp[i].reset();
	REP(i, 1, n)
		REP(j, 1, n)
		if ((T[i] & G[j]).count() & 1) Tmp[i].set(j);
	REP(i, 1, n) T[i] = Tmp[i];
}
void turn()
{
	REP(i, 1, n) tmp[i] = F[i];
	REP(i, 1, n)
	{
		unsigned res = 0;
		REP(j, 1, n) if (G[i].test(j)) res ^= tmp[j];
		F[i] = res;
	}
}

bitset <maxn> bin[40][maxn];

void power_pow(unsigned k)
{
	k--;
	REP(i, 1, n) res[i] = base[i] = G[i];
	for (int ccc = 0; k; k >>= 1, ccc++) if (k & 1)
	{
		REP(i, 1, n) Tmp[i].reset();
		REP(i, 1, n)
			REP(j, 1, n)
			if ((res[i] & bin[ccc][j]).count() & 1) Tmp[i].set(j);
		REP(i, 1, n) res[i] = Tmp[i];
	}
	/*
	while (k)
	{
		//		REP(i,1,n)REP(j,i+1,n)assert(base[i].test(j)==base[j].test(i));
		//		REP(i,1,n)REP(j,i+1,n)assert(res[i].test(j)==res[j].test(i));
		if (k & 1)
		{
			//res *= base
			REP(i, 1, n) Tmp[i].reset();
			REP(i, 1, n)
				REP(j, 1, n)
				if ((res[i] & base[j]).count() & 1) Tmp[i].set(j);
			REP(i, 1, n) res[i] = Tmp[i];
		}
		//base *= base
		REP(i, 1, n) Tmp[i].reset();
		REP(i, 1, n)
			REP(j, 1, n)
			if ((base[i] & base[j]).count() & 1) Tmp[i].set(j);
		REP(i, 1, n) base[i] = Tmp[i];
		k >>= 1;
	}
	*/
}

int main()
{
	file("magic");
	n = read<int>();m = read<int>();q = read<int>();
	REP(i, 1, n) F[i] = f[i] = read<unsigned>();
	while (m--)
	{
		int u(read<int>()), v(read<int>());
		G[u].set(v);G[v].set(u);
	}
	/*
	   REP(i, 1, n) T[i] = G[i];
	   FILE *tst = fopen("tst.out", "w");
	   REP(i, 1, 1000)
	   {
	   turn();
	   REP(i, 1, n) printf("%d%c", F[i], i == n ? '\n' : ' ');
	   REP(i, 1, n)
	   {
	   int res = 0;
	   REP(j, 1, n) if (T[i].test(j)) res ^= f[j];
	   fprintf(tst, "%d%c", res, i == n ? '\n' : ' ');
	   }
	   turn_matrix();
	   }
	   */
	REP(i, 1, n) bin[0][i] = G[i];
	REP(ccc, 1, 33)
	{
		REP(i, 1, n)
			REP(j, 1, n)
			if ((bin[ccc - 1][i] & bin[ccc - 1][j]).count() & 1) bin[ccc][i].flip(j);
	}
	REP(Case, 1, q)
		//	while (q--)	
	{
		unsigned a = read<unsigned>();
		if (!a)
		{
			cout << f[1] << '\n';
			continue;
		}
		power_pow(a);
		unsigned ans = 0;
		REP(i, 1, n) if (res[1].test(i)) ans ^= f[i];
		cout << ans << '\n';
	}
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	return 0;
}
