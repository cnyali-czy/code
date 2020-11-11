/*
	Problem:	F.cpp
	Time:		2020-11-07 09:11
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <map>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 3e5 + 10;

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

int n, m;
char s[maxn];

struct AC
{
	int ch[maxn][26], ch2[maxn][26], fail[maxn], t[maxn], s[maxn], cur;
	int rt[666], siz[666], top;
	AC()
	{
		memset(ch, 0, sizeof ch);
		memset(fail, 0, sizeof fail);
		memset(t, 0, sizeof t);
		memset(s, 0, sizeof s);
		memset(siz, 0, sizeof siz);
		cur = top = 0;
	}
	void merge(int &x, int y)
	{
		if (!x || !y) x |= y;
		else
		{
			t[x] += t[y];
			REP(i, 0, 25) merge(ch[x][i], ch[y][i]);
		}
	}
	void build(int p)
	{
		static int q[maxn];
		int head = 0, tail = -1;
		REP(i, 0, 25)
		{
			s[ch[p][i]] = 0;
			if (ch[p][i])
			{
				fail[ch[p][i]] = p;
				ch2[p][i] = ch[p][i];
				q[++tail] = ch[p][i];
			}
			else ch2[p][i] = p;
		}
		while (head <= tail)
		{
			int x = q[head++];
			REP(i, 0, 25)
				if (ch[x][i])
				{
					ch2[x][i] = ch[x][i];
					fail[ch2[x][i]] = ch2[fail[x]][i];
					q[++tail] = ch2[x][i];
				}
				else ch2[x][i] = ch2[fail[x]][i];
			s[x] = t[x] + s[fail[x]];
		}
	}
	void ins()
	{
		++top;
		rt[top] = ++cur;
		siz[top] = 1;
		int p = cur;
		REP(i, 1, n)
		{
			int c = ::s[i] - 'a';
			if (!ch[p][c]) ch[p][c] = ++cur;
			p = ch[p][c];
		}
		t[p]++;
		while (siz[top] == siz[top - 1])
		{
			siz[top - 1] += siz[top];
			merge(rt[top - 1], rt[top]);
			top--;
		}
		build(rt[top]);
	}
	i64 query()
	{
		i64 ans= 0;
		REP(i, 1, top)
		{
			int p = rt[i];
			REP(j, 1, n)
			{
				p = ch2[p][::s[j] - 'a'];
				ans += s[p];
			}
		}
		return ans;
	}
}A, B;

int main()
{
#ifdef CraZYali
	file("F");
#endif
	m = read<int>();
	while (m--)
	{
		int opt;
		scanf("%d %s", &opt, s + 1);
		n = strlen(s + 1);
		if (opt == 1) A.ins();
		else if (opt == 2) B.ins();
		else cout << A.query() - B.query() << endl;
	}
	return 0;
}
