/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.31 20:45
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <tr1/unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, m, f, a[maxn], lastans;
int stack[2][maxn], top[2];

namespace bf
{
	inline void work()
	{
		REP(i, 1, m)
		{
			lastans *= f;
			int opt(read<int>());
			if (opt == 1)
			{
				int l(read<int>() ^ lastans), r(read<int>() ^ lastans), x(read<int>() ^ lastans);
				REP(i, l, r) a[i] = x;
			}
			else
			{
				int x(read<int>() ^ lastans), y(read<int>() ^ lastans);
				if (x == y)
				{
					printf("%d\n", lastans = 0);
					continue;
				}
				top[0] = top[1] = 0;
				REP(i, 1, n)
					if (a[i] == x) stack[0][++top[0]] = i;
					else if (a[i] == y) stack[1][++top[1]] = i;
				if (!top[0] || !top[1])
				{
					printf("-1\n");
					lastans = 0;
				}
				else
				{
					lastans = n + 100;
					int j;

					j = 1;
					REP(i, 1, top[0])
					{
						while (j < top[1] && stack[1][j + 1] <= stack[0][i]) j++;
						if (stack[0][i] >= stack[1][j]) chkmin(lastans, stack[0][i] - stack[1][j]);
						if (j == top[1]) break;
					}

					j = 1;
					REP(i, 1, top[0])
					{
						while (j < top[1] && stack[1][j] < stack[0][i]) j++;
						if (stack[1][j] >= stack[0][i]) chkmin(lastans, stack[1][j] - stack[0][i]);
						else break;
					}
					printf("%d\n", lastans);
				}
			}
		}
	}
}

namespace cheat
{
	vector <int> show[maxn];
	tr1::unordered_map <int, int> mem[maxn];

	inline void work()
	{
		REP(i, 1, n) show[a[i]].push_back(i);
		while (m--)
		{
			lastans *= f;
			read<int>();
			int x(read<int>() ^ lastans), y(read<int>() ^ lastans);
			if (mem[x].count(y) || mem[y].count(x))
			{
				printf("%d\n", lastans = mem[x][y]);
				continue;
			}
			if (show[x].empty() || show[y].empty())
			{
				printf("-1\n");
				lastans = 0;
				continue;
			}
			top[0] = top[1] = 0;
			for (int qaq : show[x]) stack[0][++top[0]] = qaq;
			for (int qaq : show[y]) stack[1][++top[1]] = qaq;
			lastans = n + 100;
			int j;

			j = 1;
			REP(i, 1, top[0])
			{
				while (j < top[1] && stack[1][j + 1] <= stack[0][i]) j++;
				if (stack[0][i] >= stack[1][j]) chkmin(lastans, stack[0][i] - stack[1][j]);
				if (j == top[1]) break;
			}

			j = 1;
			REP(i, 1, top[0])
			{
				while (j < top[1] && stack[1][j] < stack[0][i]) j++;
				if (stack[1][j] >= stack[0][i]) chkmin(lastans, stack[1][j] - stack[0][i]);
				else break;
			}
			printf("%d\n", mem[x][y] = mem[y][x] = lastans);
		}
	}
}
int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> m >> f;
	REP(i, 1, n) a[i] = read<int>();
	if (n <= 5000 && m <= 5000) bf::work();
	else cheat::work();
	return 0;
}
