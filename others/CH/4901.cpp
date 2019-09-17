/*
 * File Name:	4901.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.14 19:26
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;
const int maxn = 20000 + 10, maxm = 100000 + 10;

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

int n, m;

int c[maxm];
pair <int, pair <int, int> > p[maxm];

vector <int> G[maxn];

inline void add(int x, int y)
{
	G[x].push_back(y);
	G[y].push_back(x);
}

int col[maxn];
int q[maxn], head, tail;

inline bool judge(int mid)
{
	REP(i, 1, n) G[i].clear();
	REP(i, 1, mid) add(p[i].second.first, p[i].second.second);
	memset(col, -1, sizeof(col));
	REP(start, 1, n)
		if (!G[start].empty() && col[start] == -1)
		{
			col[q[head = tail = 1] = start] = 0;
			while (head <= tail)
			{
				int u = q[head++];
				for (int v : G[u])
					if (col[v] == -1) col[q[++tail] = v] = col[u] ^ 1;
			}
		}
	REP(u, 1, n)
		for (int v : G[u]) if (col[u] == col[v]) return 1;
	return 0;
}

int main()
{
#ifdef CraZYali
	file("4901");
#endif
	cin >> n >> m;
	REP(i, 1, m)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		p[i] = make_pair(-z, make_pair(x, y));
	}
	sort(p + 1, p + 1 + m);

	int l(1), r(m);
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (judge(mid)) r = mid - 1;
		else l = mid + 1;
	}
	cout << -p[r+1].first << endl;
	return 0;
}
