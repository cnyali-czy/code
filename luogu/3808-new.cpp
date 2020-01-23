/*
 * File Name:	3808-new.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.23 16:11
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 1e6 + 10;

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

int fail[maxn], ch[maxn][26], cur = 1, rt = 1, mark[maxn];

void insert(char s[])
{
	int n = strlen(s + 1);
	int u = rt;
	REP(i, 1, n)
	{
		int c = s[i] - 'a';
		if (!ch[u][c]) ch[u][c] = ++cur;
		u = ch[u][c];
	}
	mark[u]++;
}
int q[maxn], head, tail;
void build()
{
	head = 1;
	REP(i, 0, 25) if (ch[1][i]) fail[q[++tail] = ch[1][i]] = 1;
	while (head <= tail)
	{
		int p = q[head++];
		REP(c, 0, 25)
			if (ch[p][c]) fail[q[++tail] = ch[p][c]] = ch[fail[p]][c];
			else ch[p][c] = ch[fail[p]][c];
	}
}

char s[maxn];

int main()
{
#ifdef CraZYali
	file("3808-new");
#endif
	int n = read<int>();
	REP(i, 1, n)
	{
		scanf("%s", s + 1);
		insert(s);
	}
	build();
	scanf("%s", s + 1);
	n = strlen(s + 1);
	int u = rt, ans = 0;
	REP(i, 1, n)
	{
		int c = s[i] - 'a';
		u = ch[u][c];
		for (int x = u; x && ~mark[x]; x = fail[x])
		{
			ans += mark[x];
			mark[x] = -1;
		}
	}
	cout << ans << endl;
	return 0;
}
