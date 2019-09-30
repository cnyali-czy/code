/*
 * File Name:	3157.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.30 09:43
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 100000 + 10 << 1;

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

int n, a[maxn], pos[maxn];
vector <int> P[maxn], N[maxn];

long long ans;

bool vis[maxn];
int s[maxn];
inline void add(int x, int y = 1)
{
	while (x <= n + n)
	{
		s[x] += y;
		x += x & -x;
	}
}
inline int sum(int x)
{
	int res(0);
	while (x > 0)
	{
		res += s[x];
		x -= x & -x;
	}
	return res;
}

int main()
{
#ifdef CraZYali
	file("3157");
#endif
	n = read<int>();
	REP(i, 1, n + n)
	{
		int x(read<int>());
		if (x < 0) N[-x].push_back(i);
		else P[x].push_back(i);
	}
	REP(i, 1, n)
		REP(j, 0, (int)N[i].size() - 1)
		{
			pos[N[i][j]] = P[i][j];
			pos[P[i][j]] = N[i][j];
			ans += N[i][j] > P[i][j];
		}
	REP(i, 1, n + n) add(i);
	REP(i, 1, n + n) if (!vis[i])
	{
		add(i, -1);
		add(pos[i], -1);
        vis[i] = vis[pos[i]] = 1;
        ans += sum(pos[i]);
	}
	cout << ans << endl;
	return 0;
}
