/*
	Problem:	D.cpp
	Time:		2020-03-24 00:04
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10;

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

int n, p[maxn], c[maxn], stack[maxn], top;
bool vis[maxn];

bool ok[maxn];
bool check(int n, int m)
{
	const int mod = n / m;
	REP(i, 0, mod) ok[i] = 1;
	REP(i, 1, n) if (c[stack[i]] != c[stack[(i - 1) % mod + 1]]) ok[(i - 1) % mod + 1] = 0;
	REP(i, 1, mod) if (ok[i]) return 1;
	return 0;
}

int main()
{
#ifdef CraZYali
	file("D");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) p[i] = read<int>();
		REP(i, 1, n) c[i] = read<int>();
		REP(i, 1, n) vis[i] = 0;
		int ans = n;
		REP(i, 1, n) if (!vis[p[i]])
		{
			top = 0;
			int x = p[i];
			while (!vis[x])
			{
				vis[x] = 1;
				stack[++top] = x;
				x = p[x];
			}
			for (int j = 1; j * j <= top; j++) if (top % j == 0)
			{
				if (check(top, j)) chkmin(ans, top / j);
				if (check(top, top / j)) chkmin(ans, j);
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
