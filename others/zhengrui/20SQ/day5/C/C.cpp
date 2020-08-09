/*
	Problem:	C.cpp
	Time:		2020-08-08 23:18
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cstring>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 1e6 + 10;

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

int ch[maxn][26], fail[maxn], len[maxn], s[maxn], last = 1, cur = 1;

void extend(int c)
{
	int u = ++cur, v = last;
	s[u] = 1;
	len[u] = len[v] + 1;
	for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
	if (!v) fail[u] = 1;
	else if (len[ch[v][c]] == len[v] + 1) fail[u] = ch[v][c];
	else
	{
		int Old(ch[v][c]), New(++cur);
		len[New] = len[v] + 1;
		fail[New] = fail[Old];
		copy(ch[Old], ch[Old] + 26, ch[New]);
		fail[Old] = fail[u] = New;
		for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
	}
	last = u;
}

int n;
char str[maxn];

int c[maxn], rk[maxn];

i64 dp[maxn], ans;

inline void chkmax(i64 &x, i64 y) {if (x < y) x = y;}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	scanf("%s", str + 1);
	n = strlen(str + 1);
	REP(i, 1, n) extend(str[i] - 'a');
	REP(i, 1, cur) c[len[i]]++;
	REP(i, 1, n) c[i] += c[i - 1];
	DEP(i, cur, 1) rk[c[len[i]]--] = i;
	DEP(i, cur, 1) s[fail[rk[i]]] += s[rk[i]];
	REP(i, 1, cur)
	{
		int x = rk[i];
		chkmax(dp[x], dp[fail[x]] + 1ll * s[x] * (len[x] - len[fail[x]]));
		chkmax(ans, dp[x]);
		REP(j, 0, 25) if (ch[x][j])
		{
			int y = ch[x][j];
			chkmax(dp[y], dp[x] + 1ll * s[y] * (len[y] - len[x]));
		}
	}
	cout << ans << endl;
	return 0;
}
