/*
	Problem:	4770.cpp
	Time:		2020-07-31 21:40
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e5 + 10;

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

namespace SAM
{
	const int maxn = ::maxn;
	bool vis[maxn];
	int stk[maxn], top;
	int ch[maxn][26], fail[maxn], len[maxn], last = 1, cur = 1;
	void extend(int c)
	{
		int u = ++cur, v = last;
		len[u] = len[v] + 1;
		for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
		if (!v) fail[u] = 1;
		else
		{
			int Old(ch[v][c]);
			if (len[Old] == len[v] + 1) fail[u] = Old;
			else
			{
				int New(++cur);
				len[New] = len[v] + 1;
				fail[New] = fail[Old];
				fail[Old] = fail[u] = New;
				copy(ch[Old], ch[Old] + 26, ch[New]);
				for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
			}
		}
		last = u;
	}
}
using SAM :: vis;
using SAM :: stk;
using SAM :: top;
using SAM :: len;

int n;
char s[maxn];

int main()
{
#ifdef CraZYali
	file("4770");
#endif
	scanf("%s", s + 1);
	REP(i, 1, strlen(s + 1)) SAM :: extend(s[i] - 'a');
	REP(Case, 1, read<int>())
	{
		scanf("%s", s + 1);
		int l = read<int>(), r = read<int>();
		int p = 1;
		n = strlen(s + 1);
		long long ans = 1ll * n * (n - 1) / 2;
		REP(i, 1, n)
		{
			while (p && !SAM :: ch[p][s[i] - 'a']) p = SAM :: fail[p];
			if (!p) break;
			p = SAM :: ch[p][s[i] - 'a'];
			for (int x = p; x && !vis[x]; x = SAM :: fail[x])
			{
				ans -= len[x] - len[SAM :: fail[x]];
				vis[x] = 1;
				stk[++top] = x;
			}
		}
		printf("%lld\n", ans);
		REP(i, 1, top) vis[stk[i]] = 0;top = 0;
	}
	return 0;
}
