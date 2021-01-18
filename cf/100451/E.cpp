#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 1e5 + 10, maxN = 1e6 + 10;

inline int to(char c)
{
	if (c == 'A') return 0;
	if (c == 'G') return 1;
	if (c == 'C') return 2;
	return 3;
}

long long ans;
int n, m, u[maxn], v[maxn];

int ch[maxN][4], cur = 1;
vector <int> vec[maxN];

void dfs(int x, int d = 0)
{
	REP(i, 0, 3)
	{
		int y = ch[x][i];
		if (!y) continue;
		dfs(y, d + 1);
		if (vec[y].size()) vec[x].emplace_back(vec[y][0]);
	}
	while (vec[x].size() > 1)
	{
		ans += d;
		++m;
		u[m] = vec[x].back();vec[x].pop_back();
		v[m] = vec[x].back();vec[x].pop_back();
	}
}

int main()
{
#ifdef CraZYali
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		char c = getchar();
		while (!isalpha(c)) c = getchar();
		int p = 1;
		while (isalpha(c))
		{
			c = to(c);
			if (!ch[p][c]) ch[p][c] = ++cur;
			p = ch[p][c];
			if ((c = getchar()) == EOF) break;
		}
		vec[p].emplace_back(i);
	}
	dfs(1);
	cout << ans << endl;
	REP(i, 1, n / 2) printf("%d %d\n", u[i], v[i]);
	return 0;
}
