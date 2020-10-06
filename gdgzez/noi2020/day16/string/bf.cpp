/*
	Problem:	string.cpp
	Time:		2020-06-18 08:00
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;
#define i64 long long
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
	const int maxn = ::maxn << 1;
	int ch[maxn][4], fail[maxn], len[maxn], cur = 1, last = 1;
	void extend(char c)
	{
		int u = ++cur, v = last;
		len[u] = len[v] + 1;
		for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
		if (!v) fail[u] = 1;
		else
		{
			int q = ch[v][c];
			if (len[q] == len[v] + 1) fail[u] = q;
			else
			{
				int New(++cur), Old(q);
				fail[New] = fail[Old];
				fail[Old] = fail[u] = New;
				len[New] = len[v] + 1;
				copy(ch[Old], ch[Old] + 4, ch[New]);
				for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
			}
		}
		last = u;
	}
	void output()
	{
		REP(i, 1, cur) printf("%d%c", fail[i], i == end_i ? '\n' : ' ');
		REP(i, 1, cur)
			REP(j, 0, 3) if (ch[i][j])
			printf("ch[%d][%c] = %d\n", i, j + 'A', ch[i][j]);
	}
}
int n, m, ans;
char T[maxn], p[maxn];
const int inf = 1e9;
inline bool chkmin(int &x, int y)
{
	if (x > y)
	{
		x = y;
		return 1;
	}
	return 0;
}
inline bool chkmax(int &x, int y)
{
	if (x < y)
	{
		x = y;
		return 1;
	}
	return 0;
}
int f[114][514];
void dfs(int x, int u = 1, int y = 0)
{
//	chkmax(f[x][u], y);
	if (x == n) chkmax(ans, y);
	else
	{
		x++;
		REP(j, 0, 3)
			if (SAM :: ch[u][j])		dfs(x, SAM :: ch[u][j], y + (u == 1));
			else if (SAM :: ch[1][j])	dfs(x, SAM :: ch[1][j], y + 1);
	}
}

int main()
{
#ifdef CraZYali
	freopen("string.in", "r", stdin);
	freopen("bf.out", "w", stdout);
#endif
	scanf("%d\n%s", &n, T + 1);
	m = strlen(T + 1);
	REP(i, 1, m) SAM :: extend(T[i] - 'A');
	dfs(0);
//	REP(i, 1, n) REP(j, 1, SAM :: cur) printf("%d%c", f[i][j], j == end_j ?'\n': ' ');
	cout << ans << endl;
	return 0;
}
