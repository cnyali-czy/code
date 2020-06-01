#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1000 + 10;

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;
vector <int> a;
vector <vector <int> > v;

int pick[maxn], to[maxn][maxn];
bool vis[maxn][maxn];
void calc()
{
	memset(vis, 0, sizeof vis);
	REP(S, 0, (1 << k) - 1)
	{
		REP(i, 1, k)
		{
			vector <int> cur;
			if (S & (1 << i - 1)) cur = v[pick[i]];
			else
			{
				cur.resize(n);
				REP(j, 0, n - 1) cur[v[pick[i]][j]] = j;
			}
			REP(j, 0, n - 1) to[i][j] = cur[j];
		}
		REP(i, 0, n - 1)
		{
			int x = i;
			REP(j, 1, k) x = to[j][x];
			vis[i][x] = 1;
		}
	}
	REP(i, 0, n - 1) REP(j, 0, n - 1) if (!vis[i][j])
	{
		printf("FUCK! (%d, %d) GG!\n", i + 1, j + 1);
		exit(0);
	}
}

void dfs(int x, int lst = -1)
{
	if (x == k) calc();
	else
	{
		x++;
		REP(i, lst + 1, v.size() - 1)
		{
			pick[x] = i;
			dfs(x, i);
		}
	}
}

int main()
{
DEBUG;
	freopen("A.in", "r", stdin);
	n = read<int>();
	freopen("A.out", "r", stdin);
	k = read<int>();
	assert(k <= 1 + ceil(log2(n)));
	REP(i, 1, k) pick[i] = i - 1;
	REP(i, 1, k)
	{
		vector <int> x;
		REP(j, 1, n) x.emplace_back(read<int>() - 1);
		v.emplace_back(x);
	}
DEBUG;
	calc();
DEBUG;
	puts("NICE WORK!");
	return 0;
}
