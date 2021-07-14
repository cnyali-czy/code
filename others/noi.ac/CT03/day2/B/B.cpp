/*
	Problem:	B.cpp
	Time:		2021-07-12 10:08
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <random>
#include <ctime>
#include <algorithm>
#include <bitset>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64

using namespace std;
const int maxn = 5e4 + 10;

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

int n, q;
vector <int> c[maxn];

namespace bf
{
	const int maxn = 1200 + 5, maxk = 100 + 5;
	bitset <maxn> b[maxn], bas[maxn];
	int main()
	{
		REP(i, 1, n)
			if (c[i].empty()) b[i][i] = 1;
			else for (auto j : c[i]) b[i] ^= b[j];
		while (q--)
		{
			vector <int> v(read<int>());
			for (auto &i : v) i = read<int>();
			random_shuffle(v.begin(), v.end());
			static bool had[maxn];
			vector <int> toclr;
			int ans = 0;
			for (auto i : v)
			{
				auto x = b[i];
				bool in = 1;
				for (int j = x._Find_first(); j <= n; j = x._Find_next(j))
				{
					if (!had[j])
					{
						in = 0;
						toclr.emplace_back(j);
						had[j] = 1;
						bas[j] = x;
						break;
					}
					else x ^= bas[j];
				}
				if (in)
				{
					ans = 1;
					break;
				}
			}
			putchar(48 + ans);
			for (auto i : toclr) had[i] = 0;
		}
		return 0;
	}
}
namespace cheat
{
	bitset <maxn> b[maxn];
	u64 bas[100], val[100];
	int main()
	{
		mt19937 hh(rand());
		REP(i, 1, n)
			if (c[i].empty()) b[i][i] = 1;
			else for (auto j : c[i]) b[i] ^= b[j];
		while (q--)
		{
			int k = read<int>();
			static int v[100];
			REP(i, 1, k) v[i] = read<int>();
			random_shuffle(v + 1, v + 1 + k);
			vector <int> sb;

			int ans = 1;//假设相关，rand来看看是否无关
			REP(T, 1, 50000)
			{
				REP(i, 1, k) val[i] = 0;
				REP(i, 0, 63)
				{
					bas[i] = 0;
					int x = hh() % n + 1;
					REP(j, 1, k) if (b[v[j]][x]) val[j] |= (1llu << i);
				}
				REP(i, 1, k)
				{
					bool in = 1;
					u64 x = val[i];
					REP(j, 0, 63) if (x >> j & 1)
						if (!bas[j])
						{
							bas[j] = x;
							in = 0;
							break;
						}
						else x ^= bas[j];
					if (in) goto cs;
				}
				ans = 0;
				goto gg;
cs:;
			}
gg:			putchar(ans + 48);
		}
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	srand(time(0));
	n = read<int>();q = read<int>();
	REP(i, 1, n)
	{
		c[i].resize(read<int>());
		for (auto &j : c[i]) j = read<int>();
	}
	if (0 && n <= 1200 && q <= 1200) return bf :: main();
	return cheat :: main();
}
