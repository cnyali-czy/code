#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
inline int read() {int x;scanf("%d", &x);return x;}

const int maxn = 1e5 + 10, maxm = 2e5 + 10;

int n, m, A, B, C;
vector <int> G[maxn];
inline int id(int x, int y) {return (x - 1) * n + y;}
int col[maxn];
bool dfs(int x)
{
	bool flg = 1;
	for (int y : G[x])
		if (!col[y])
		{
			col[y] = 3 - col[x];
			flg &= dfs(y);
		}
		else flg &= (col[y] == 3 - col[x]);
	return flg;
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	n = read();m = read();
	REP(i, 1, m)
	{
		int x = read(), y = read();
		G[x].emplace_back(y);
		G[y].emplace_back(x);
	}
	REP(i, 1, n) if (!col[i])
		if (!G[i].size()) C++;
		else
		{
			col[i] = 1;
			if (dfs(i)) B++;
			else A++;
		}
	i64 ans = 0, s = 0;
	REP(i, 1, A)
	{
		ans += 1 + 2 * s;
		s++;
	}
	REP(i, 1, B)
	{
		ans += (1 + s << 1);
		s += 2;
	}
	s = n - C;
	REP(i, 1, C)
	{
		ans += 1 + 2 * s;
		s++;
	}
	cout << ans << endl;
	return 0;
}
