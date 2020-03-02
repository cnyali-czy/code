/*
	Problem:	D.cpp
	Time:		2020-03-01 22:17
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10, maxm = 2e5 + 10;

vector <int> G[maxn];

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

int n, m, k, a[maxn];
int q[maxn], head, tail;
int dis[maxn], out[maxn];

int main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();m = read<int>();
	while (m--)
	{
		int x(read<int>()), y(read<int>());
		out[x]++;
//		G[x].emplace_back(y);
		G[y].emplace_back(x);
	}
	k = read<int>();
	REP(i, 1, k) a[i] = read<int>();
	REP(i, 1, n) dis[i] = -1;
	dis[q[0] = a[k]] = 0;
	while (head <= tail)
	{
		int u = q[head++];
		for (int v : G[u]) if (dis[v] == -1)
			dis[q[++tail] = v] = dis[u] + 1;
	}
	int Min(0), Max(0);
	if (k == 1)
	{
		puts("0 0");
		return 0;
	}
	REP(i, 1, k - 1)
		if (dis[a[i+1]] + 1 == dis[a[i]]) Max += out[a[i]] - 1;
		else Min++, Max++;
	cout << Min << ' ' << Max << endl;
	return 0;
}
