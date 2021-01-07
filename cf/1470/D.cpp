/*
	Problem:	D.cpp
	Time:		2021-01-07 19:20
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <queue>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 3e5 + 10;

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

int n, m;
int fa[maxn], c[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
vector <int> G[maxn];

vector <int> ans;
queue <int> que;
bool insed[maxn];
void ins(int x)
{
	if (insed[x]) return;
	insed[x] = 1;
	for (int y : G[x]) if (!c[y])
		que.emplace(y);
}

int main()
{
#ifdef CraZYali
	file("D");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();
		REP(i, 1, n) fa[i] = i, G[i].clear();
		while (m--)
		{
			int u = read<int>(), v = read<int>();
			fa[find(u)] = find(v);
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		bool ok = 1;
		REP(i, 1, n) if (find(i) != find(1))
		{
			puts("NO");
			ok = 0;
			break;
		}
		if (!ok) continue;
		REP(i, 1, n) c[i] = insed[i] = 0;
		puts("YES");
		ans.clear();
		c[1] = 1;
		for (int x : G[1])
		{
			c[x] = 2;
			ins(x);
		}
		ans.emplace_back(1);
		while (que.size())
		{
			int x = que.front();que.pop();
			if (c[x]) continue;
			ans.emplace_back(x);
			c[x] = 1;
			for (int y : G[x]) if (!c[y])
			{
				c[y] = 2;
				ins(y);
			}
		}
		printf("%d\n", ans.size());
		sort(ans.begin(), ans.end());
		REP(i, 0, ans.size() - 1) printf("%d%c", ans[i], i == end_i ? '\n' : ' ');
	}
	return 0;
}
