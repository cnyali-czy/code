/*
	Problem:	B.cpp
	Time:		2021-02-16 21:08
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cstdio>
#define i64 long long 

using namespace std;
const int maxn = 1e6 + 10, maxN = maxn << 1;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

i64 tot;
int ch[maxN][2], fail[maxN], len[maxN], pos[maxN], lst, cur;
void init()
{
	tot = 0;
	REP(i, 1, cur) ch[i][0] = ch[i][1] = fail[i] = len[i] = pos[i] = 0;
	lst = cur = 1;
}
void extend(char c)
{
	int u = ++cur, v = lst;lst = u;
	len[u] = len[v] + 1;
	for (; v && !ch[v][c]; v = fail[v]) ch[v][c] = u;
	if (!v) fail[u] = 1;
	else if (len[ch[v][c]] == len[v] + 1) fail[u] = ch[v][c];
	else
	{
		int New(++cur), Old(ch[v][c]);
		ch[New][0] = ch[Old][0];ch[New][1] = ch[Old][1];
		fail[New] = fail[Old];
		len[New] = len[v] + 1;
		fail[Old] = fail[u] = New;
		for (; v && ch[v][c] == Old; v = fail[v]) ch[v][c] = New;			
	}
	tot += len[u] - len[fail[u]];
}

char str[maxn];
int n;
vector <int> q[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	scanf("%s", str + 1);
	n = strlen(str + 1);
	init();
	DEP(i, n, 1) extend(str[i] - 48);
	for (int p = 1, i = n; i >= 1; i--)
	{
		p = ch[p][str[i] - 48];
		for (int x = p; x && !pos[x]; x = fail[x]) pos[x] = i;
	}
	REP(i, 2, cur) q[pos[i] + len[i] - 1].emplace_back(pos[i] + len[fail[i]]);
	i64 ans = 0;
	REP(i, 1, n)
	{
		init();
		sort(q[i].begin(), q[i].end(), greater <int> ());
		int cur = i;
		for (int j : q[i])
		{
			while (cur >= j) extend(str[cur--] - 48);
			ans += tot;
		}
	}
	cout << ans << endl;
	return 0;
}
