/*
	Problem:	E.cpp
	Time:		2020-02-24 23:44
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5000 + 10;

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

int n, fa[maxn], deg[maxn], son[maxn], dep[maxn];

bool bad[maxn];
unordered_set <int> des[maxn], goodleave;

int main()
{
#ifdef CraZYali
	file("E");
#endif
	register int T = read<int>();
	while (T--)
	{
		int n = read<int>(), d = read<int>();
		int s = 0;
		goodleave.clear();
		goodleave.emplace(n);
		REP(i, 1, n)
		{
			bad[i] = 0;
			fa[i] = i - 1;
			son[i] = i < n;
		}
		REP(i, 0, n) des[i].clear();
		des[dep[1] = 0].emplace(1);
		REP(i, 2, n) des[dep[i] = i - 1].emplace(i);
		int sd = n * (n - 1) / 2, ld = 0, cd = 0;
		REP(i, 1, n)
		{
			if (!(i & (i - 1))) cd++;
			ld += cd - 1;
		}
		if (d > sd || d < ld)
		{
			puts("NO");
			continue;
		}
		while (sd != d)
		{
			int Min = 1e9, c = -1, d = 114514;
			for (int i : goodleave) if (!son[i])
				if (dep[i] < Min && dep[i] >= 2)
				{
					Min = dep[i];
					c = i;
				}
/*
					bool flag = 0;
					for (int j : des[dep[i] - 2]) if (son[j] < 2)
					{
						flag = 1;
						c = i;
						d = j;
						Min = dep[i];
						break;
					}
					if (!flag)
					{
						neederase.emplace_back(i);
						bad[i] = 1;
					}
					*/
			if (c == -1) break;
			else
			{
				bool flag = 0;
				for (int j : des[dep[c] - 2]) if (son[j] < 2)
				{
					flag = 1;
					d = j;
					break;
				}
				if (!flag)
				{
					bad[c] = 1;
					goodleave.erase(c);
					continue;
				}
				son[fa[c]]--;
				if (!son[fa[c]] && !bad[fa[c]]) goodleave.emplace(fa[c]);
				fa[c] = d;
				if (!son[fa[c]] && goodleave.find(fa[c]) != goodleave.end()) goodleave.erase(fa[c]);
				son[fa[c]]++;
				des[dep[c]].erase(c);
				dep[c]--;
				des[dep[c]].emplace(c);
				sd--;
			}
		}
		if (sd == d)
		{
			puts("YES");
			REP(i, 2, n) printf("%d%c", fa[i], i == n ? '\n' : ' ');
		}
		else puts("NO");
	}
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
