//test
/*
	Problem:	A.cpp
	Time:		2020-05-24 21:06
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long
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

char s[maxn];
int n, q, nxt[maxn][26], f[maxn][26], Lim[maxn], al;
#define i64 long long
i64 g[maxn][26], sum[maxn];
const i64 inf = 0x3f3f3f3f3f3f3f3f;
inline void limit(i64 &x)
{
	if (x > inf) x = inf;
}
vector <pair <int, int> > Ans;
char t[maxn];
void Solve(i64 k, int l)
{
	Ans.clear();
	int Al = 0;
	for (int i=1;--k;++i)
	{
		int p(-1), ns(1);
		REP(j, 0, 25)
			if (k > sum[nxt[i][j] + 1]) k -= sum[nxt[i][j] + 1];
			else
			{
				p = j;
				break;
			}
		if (!~p) return void(puts("-1"));
		DEP(j, Lim[i = nxt[i][p]], 0)
			if (k > g[i][j] && k <= g[i][j] + sum[f[i][j] + 1])
			{
				k -= g[i][j];
				ns += (1 << j);
				i = f[i][j];
			}
		Ans.emplace_back(p, ns);
		Al += ns;
	}
	reverse(Ans.begin(), Ans.end());
	chkmin(l, Al);
	t[l] = 0;
	for (auto i : Ans)
		for(int j = i.second;l && j--;t[--l] = 'a' + i.first);//DEBUG;
	puts(t);
}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	scanf("%s", s + 1);n = strlen(s + 1);
	REP(i, 0, 25) nxt[n + 1][i] = f[n + 1][i] = n + 1;
	sum[n + 1] = 1;
	DEP(i, n, 1)
	{
		copy(nxt[i + 1], nxt[i + 1] + 26, nxt[i]);
		int c = s[i] - 'a';
		f[i][0] = nxt[i][c];
		g[i][0] = 1;
		REP(j, 0, c - 1) limit(g[i][0] += sum[nxt[i][j] + 1]);
		limit(sum[nxt[i][c] = i] = sum[i + 1] * 2 - sum[f[i][0] + 1]);
		Lim[i] = -1;
		REP(j, 1, 25)
		{
			f[i][j] = f[f[i][j - 1]][j - 1];
			limit(g[i][j] = g[i][j - 1] + g[f[i][j - 1]][j - 1]);
			if (f[i][j] == n + 1 && Lim[i] == -1) Lim[i] = j - 1;
		}
	}
	q = read<int>();
	while (q--)
	{
		int k(read<int>()), p(read<int>());
		Solve(k + 1, p);
		fflush(stdout);
	}
	return 0;
}
