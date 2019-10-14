#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 100000 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e, deg[maxn];
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	deg[x]++;
}

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
int cost[maxn][4];

int q[maxn], head, tail, dfn[maxn];

#include <vector>
vector <int> V[4], vv[4];
int id[4], color[maxn];

int main()
{
#ifdef CraZYali
	file("D");
#endif
	cin >> n;
	REP(j, 1, 3) 
		REP(i, 1, n)
		cost[i][j] = read<int>();
	REP(i, 2, n)
	{
		register int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	REP(i, 1, n) if (deg[i] > 2)
	{
		printf("-1\n");
		return 0;
	}
	REP(i, 1, n) if (deg[i] == 1)
	{
		q[tail] = i;
		dfn[i] = 1;
		while (head <= tail)
		{
			int x = q[head++];
			for (register int i = bg[x]; i; i = ne[i]) if (!dfn[to[i]])
				dfn[q[++tail] = to[i]] = dfn[x] + 1;
		}
		REP(i, 1, n)
			V[dfn[i] % 3 + (dfn[i] % 3 == 0 ? 3 : 0)].push_back(i);
		REP(i, 1, 3) id[i] = i;
		long long Min = 1e18, times = -1, bst(-1);
		do
		{
			times++;
			long long res(0);
			REP(i, 1, 3)
				for (int j : V[id[i]]) res += cost[j][i];
			if (res < Min)
			{
				Min = res;
				bst = times;
			}
		}while (next_permutation(id + 1, id + 4));
		cout << Min << endl;
		REP(i, 1, 3) id[i] = i;
		while (bst--) next_permutation(id + 1, id + 4);
		REP(i, 1, 3) for (int j : V[id[i]]) color[j] = i;
		REP(i, 1, n) printf("%d%c", color[i], i == n ? '\n' : ' ');
		return 0;
	}
	return 0;
}
