/*
	Problem:	3052.cpp
	Time:		2020-03-03 21:49
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <queue>
#include <ext/pb_ds/priority_queue.hpp>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 2e5 + 10;

int bg[maxn], ne[maxn], to[maxn], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int n;
int m[maxn];

priority_queue <int> q[maxn];

int siz[maxn], stack[maxn], top;

void dfs(int u)
{
	for (int i = bg[u], v = to[i]; i; v = to[i = ne[i]])
	{
        dfs(v);
		if (siz[v] > siz[u])
		{
			swap(q[u], q[v]);
			swap(siz[u], siz[v]);
		}
		top = 0;
		while (!q[v].empty())
		{
			stack[++top] = max(q[u].top(), q[v].top());
			q[u].pop();q[v].pop();
        }
		REP(i, 1, top) q[u].push(stack[i]);
    }
	q[u].push(m[u]);
	siz[u]++;
}
int main()
{
#ifdef CraZYali
	file("3052");
#endif
	n = read<int>();
	REP(i, 1, n) m[i] = read<int>();
	REP(i, 2, n) add(read<int>(), i);
	dfs(1);
	i64 ans = 0;
	while (!q[1].empty())
	{
		ans += q[1].top();
		q[1].pop();
	}
	cout << ans << '\n';
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
