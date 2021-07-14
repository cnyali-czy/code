/*
	Problem:	A.cpp
	Time:		2021-07-12 08:49
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <algorithm>
#include <vector>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <cstdio>

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

int n, a[maxn], pos[maxn], xs[maxn];
unsigned len[maxn], bin[10];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();const unsigned MOD = read<int>();
	REP(i, 1, 9) len[i] = 1;
	REP(i, 10, 99) len[i] = 2;
	REP(i, 100, 999) len[i] = 3;
	REP(i, 1000, 9999) len[i] = 4;
	len[10000] = 5;
	bin[0] = 1;REP(i, 1, 9) bin[i] = bin[i - 1] * 10 % MOD;
	REP(i, 1, n) pos[a[i] = read<int>()] = i, xs[i] = bin[len[a[i]]];
	srand(time(0));
	const int B = 15;
	REP(T, 0, n <= B ? (1 << n) - 1 : 40000000 / n)
	{
		int x = 0;
		unsigned num = 0;
		static bool b[maxn];
		if (n > B) REP(i, 1, n)
		{
			if (b[i] = (rand() & 1))
			{
				x ^= a[i];
				num = (num * xs[i] + a[i]) % MOD;
				if (1 <= x && x <= n && pos[x] > i && !b[pos[x]] && (num * xs[pos[x]] + x) % MOD == 0)
				{
					puts("Yes");
					vector <int> v;
					REP(j, 1, i) if (b[j]) v.emplace_back(j);
					v.emplace_back(pos[x]);
					cout << v.size() << '\n';
					for (auto i : v) printf("%d ", i);

#ifdef CraZYali
					x = 0;num = 0;
					for (auto i : v)
					{
						x ^= a[i];
						num = (num * xs[i] + a[i]) % MOD;
					}
					if (x || num)
					{
						cerr << "GG: " << x << ' ' << num << endl;
						while (1);
					}
					cerr << "ok\n";
#endif

					return 0;
				}
			}
		}
		else REP(i, 1, n) 
		{
			if (b[i] = (T >> (i - 1) & 1))
			{
				x ^= a[i];
				num = (num * xs[i] + a[i]) % MOD;
				if (1 <= x && x <= n && pos[x] > i && !b[pos[x]] && (num * xs[pos[x]] + x) % MOD == 0)
				{
					puts("Yes");
					vector <int> v;
					REP(j, 1, i) if (b[j]) v.emplace_back(j);
					v.emplace_back(pos[x]);
					cout << v.size() << '\n';
					for (auto i : v) printf("%d ", i);

#ifdef CraZYali
					x = 0;num = 0;
					for (auto i : v)
					{
						x ^= a[i];
						num = (num * xs[i] + a[i]) % MOD;
					}
					if (x || num)
					{
						cerr << "GG: " << x << ' ' << num << endl;
						while (1);
					}
					cerr << "ok\n";
#endif

					return 0;
				}
			}
		}
	}
	puts("No");
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;

	return 0;
}
