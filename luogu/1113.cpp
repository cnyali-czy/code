#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 10000 + 10, maxm = maxn * 100;

int bg[maxn], ne[maxm], to[maxm], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int n, ans;

int len[maxn], in[maxn], dp[maxn];
bool done[maxn];

void dfs(int x)
{
	for (register int i = bg[x]; i ; i = ne[i])
	{
		chkmax(dp[to[i]], dp[x] + len[to[i]]);
		if (in[to[i]])
		{
			in[to[i]]--;
			if (!in[to[i]]) dfs(to[i]);
		}
	}
}
int main()
{
#ifdef CraZYali
	freopen("1113.in", "r", stdin);
	freopen("1113.out", "w", stdout);
#endif
	n = read<int>();
	REP(i, 1, n)
	{
		read<int>();
		len[i] = read<int>();
		while (1)
		{
			int k = read<int>();
			if (k)
			{
				add(k, i);
				in[i]++;
			}
			else break;
		}
	}
#ifdef CraZYali
	REP(i, 1, n) fprintf(stderr, "%d%c", i, i ^ n ? ' ' : '\n');
#endif
	int root;
	REP(i, 1, n)
		if (!in[i])
		{
			root = i;
			break;
		}
	dp[root] = len[root];
	dfs(root);
	REP(i, 1, n) chkmax(ans, dp[i]);
	cout << ans;
	return 0;
}
