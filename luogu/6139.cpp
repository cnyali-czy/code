/*
	Problem:	6139.cpp
	Time:		2020-06-14 20:36
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <cstring>
#include <iostream>
#include <cstdio>

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

long long ans;
namespace SAM
{
	const int maxn = ::maxn << 1;
	int ch[maxn][26], len[maxn], fail[maxn];
	int last = 1, cur = 1;
	void extend(int c)
	{
		int u = ++cur, v = last;
		len[u] = len[last] + 1;
		for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
		if (!v) fail[u] = 1;
		else
		{
			int q = ch[v][c];
			if (len[q] == len[v] + 1) fail[u] = q;
			else
			{
				int Old(q), New(++cur);
				len[New] = len[v] + 1;
				fail[New] = fail[Old];
				fail[u] = fail[Old] = New;
				copy(ch[Old], ch[Old] + 26, ch[New]);
				for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;
			}
		}
		last = u;
	}
	void work()
	{
		REP(i, 1, cur) ans += len[i] - len[fail[i]];
	}
}

int n;
char s[maxn];

int main()
{
#ifdef CraZYali
	file("6139");
#endif
	REP(Case, 1, read<int>())
	{
		SAM :: last = 1;
		scanf("%s", s + 1);
		n = strlen(s + 1);
		REP(i, 1, n) SAM :: extend(s[i] - 'a');
	}
	SAM :: work();
	cout << ans << endl;
	return 0;
}
