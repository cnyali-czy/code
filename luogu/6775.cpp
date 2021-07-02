/*
	Problem:	6775.cpp
	Time:		2021-07-02 15:36
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bitset>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 500 + 5, maxk = 5000 + 5;

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

int n, m, k, a[maxn];

bool ist2;
bool del[maxn];int deled;

namespace greedy
{
	struct cmp
	{
		inline bool operator () (int x, int y) {return a[x] > a[y];}
	};
	multiset <int, cmp> s;
	void work()
	{
		int sum = 0;REP(i, 1, n) if (!del[i]) sum += a[i];
		if (sum != m * k) cerr << ist2 << endl, DEBUG;
		s.clear();REP(i, 1, n) if (!del[i]) s.emplace(i);
		REP(i, n - deled, m)
		{
			int x = *s.begin();s.erase(s.begin());
			printf("%d %d\n", x, k);
			a[x] -= k;
			if (a[x]) s.emplace(x);
		}
		REP(i, 1, n - deled - 1)
		{
			int x = *s.begin();s.erase(s.begin());
			if (s.size())
			{
				int y = *(--s.end());s.erase(--s.end());
				printf("%d %d %d %d\n", x, k - a[y], y, a[y]);
				a[x] -= k - a[y];a[y] = 0;
				if (a[x]) s.emplace(x);
			}
			else
			{
				printf("%d %d\n", x, k);
				a[x] -= k;
				if (a[x]) s.emplace(x);
			}
		}
	}
}

const int N = maxn * maxk - 5;
bitset <N + N + 10> f[maxn];

signed main()
{
#ifdef CraZYali
	file("6775");
#endif
	register int T = read<int>();
	REP(Case, 1, T)
	{
		n = read<int>();m = read<int>();k = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		if (m >= n - 1) ist2 = 0, greedy :: work();
		else
		{
			ist2 = 1;
			if (n <= 3) {puts("-1");continue;}
			f[0][N] = 1;
			REP(i, 1, n) f[i].reset();
			REP(i, 1, n)
			{
				if (a[i] >= k) f[i] = f[i - 1] | (f[i - 1] << (a[i] - k));
				else f[i] = f[i - 1] | (f[i - 1] >> (k - a[i]));
			}
			REP(i, 1, n) if (f[i][N - k])
			{
				vector <int> vec;
				int x = -k;
				static bool vis[maxn];
				REP(i, 1, n) vis[i] = 0;
				DEP(j, i, 1) if (x - (a[j] - k) + N >= 0 && f[j - 1][x - (a[j] - k) + N])
				{
					vis[j] = 1;
					vec.emplace_back(j);
					x -= (a[j] - k);
				}

				for (auto i : vec) del[i] = 1, deled++;
				m = n - deled - 1;
				greedy :: work();
				REP(i, 1, n) del[i] = 0;deled = 0;

				vec.clear();
				REP(i, 1, n) if (!vis[i]) vec.emplace_back(i);

				for (auto i : vec) del[i] = 1, deled++;
				m = n - deled - 1;
				greedy :: work();
				REP(i, 1, n) del[i] = 0;deled = 0;

				goto ok;
			}
gg:			puts("-1");
ok:;
		}
	}
	return 0;
}
