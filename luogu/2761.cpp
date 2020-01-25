/*
 * File Name:	2761.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.25 16:44
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 20 + 5, maxm = 100 + 5, maxS = 1 << 20;
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

int n, m, f[maxS], q[maxS], head, tail;

int t[maxm], must[maxm], mustn[maxm], fix[maxm], add[maxm];
char s[maxn];
bool vis[maxS];

int main()
{
#ifdef CraZYali
	file("2761");
#endif
	cin >> n >> m;
	REP(i, 1, m)
	{
		t[i] = read<int>();
		scanf("%s", s);
		REP(j, 0, n - 1)
			if (s[j] == '+') must[i] |= (1 << j);
			else if (s[j] == '-') mustn[i] |= (1 << j);
		scanf("%s", s);
		REP(j, 0, n - 1)
			if (s[j] == '-') fix[i] |= (1 << j);
			else if (s[j] == '+') add[i] |= (1 << j);
	}
	memset(f, 0x3f, sizeof f);
	const int T = (1 << n) - 1;
	const int inf = f[T];
	f[q[0] = T] = 0;
	while (head <= tail)
	{
		int S = q[head++];
		vis[S] = 0;
		REP(i, 1, m)
			if (((S & must[i]) == must[i]) && !(S & mustn[i]))
			{
				int to = ((S | add[i]) ^ fix[i]) & (T ^ fix[i]);
				if (f[to] > f[S] + t[i])
				{
					f[to] = f[S] + t[i];
					if (!vis[to])
					{
						vis[to] = 1;
						q[++tail] = to;
					}	
				}
			}
	}
	printf("%d\n", f[0] < inf ? f[0] : 0);
	return 0;
}
