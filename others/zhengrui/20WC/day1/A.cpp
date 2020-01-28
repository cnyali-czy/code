/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.27 22:15
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxm = 5 * maxn;

int bg[maxn], ne[maxm], to[maxm], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int n, m, k, a[maxn], in[maxn];
struct node
{
	int x, y;
	node(int x = 0, int y = 0) : x(x), y(y) {}
	inline bool operator < (const node &B) const {return y < B.y;}
};
priority_queue <node> q;
bool vis[maxn];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> m >> k;
	REP(i, 1, n)
	{
		in[i] = k;
		q.emplace(i, a[i] = read<int>());
	}
	while (m--) add(read<int>(), read<int>());
	while (!q.empty())
	{
		int x = q.top().x;q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		for (int i = bg[x]; i; i = ne[i])
			if (a[to[i]] < a[x] && in[to[i]]-- <= 0)
			{
				a[to[i]] = a[x];
				q.emplace(to[i], a[to[i]]);
			}
	}
	REP(i, 1, n) cout << a[i], putchar(10);
	return 0;
}
