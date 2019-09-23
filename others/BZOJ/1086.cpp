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
const int maxn = 1000 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
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

int n, B;

int cur, belong[maxn], province[maxn];
bool flag = 1;

int stack[maxn], top;

void dfs(int x, int fa = -1)
{
	int qaq = top;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs(to[i], x);
		if (top - qaq >= B)
		{
			province[++cur] = x;
			while (top ^ qaq) belong[stack[top--]] = cur;
		}
	}
	stack[++top] = x;
}

int main()
{
#ifdef CraZYali
	file("1086");
#endif
	cin >> n >> B;
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);
		add(y, x);
	}
	dfs(1);
	if (top)
	{
		province[cur] = stack[top];
		while (top) belong[stack[top--]] = cur;
	}
	printf("%d\n", cur);
	REP(i, 1, n) printf("%d%c", belong[i], i == n ? '\n' : ' ');
	REP(i, 1, cur) printf("%d%c", province[i], i == cur ? '\n' : ' ');
	return 0;
}
