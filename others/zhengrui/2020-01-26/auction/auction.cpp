/*
 * File Name:	auction.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.26 11:32
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkMax(a, b) (a < (b) ? a = (b) : a) 
#define chkMin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;
const int Maxn = 5000 + 10;

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

int n, q;
char s[Maxn];
bool vis[Maxn][Maxn][2];
char mem[Maxn][Maxn][2];
inline char Max(char a, char b) {return a > b ? a : b;}
inline char Min(char a, char b) {return a < b ? a : b;}
char dfs(int x, int less, int flag, char last)
{
	if (!less || x == n + 1) return last;
	chkMin(less, n - x + 1);
	int Flag = flag + 1 >> 1;
	if (vis[x][less][Flag]) return mem[x][less][Flag] + last;
	vis[x][less][Flag] = 1;
	char &ans = mem[x][less][Flag];
	if (s[x] == '1') return (ans = dfs(x + 1, less - 1, -flag, flag)) + last;
	else
		if (less == 1) return (ans = 0) + last;
		else if (flag == 1) return (ans = Max(dfs(x + 1, less - 1, -flag, 0), Min(dfs(x + 1, less, flag, 0), dfs(x + 1, less - 1, flag, 0)))) + last;
		else				return (ans = Min(dfs(x + 1, less - 1, -flag, 0), Max(dfs(x + 1, less, flag, 0), dfs(x + 1, less - 1, flag, 0)))) + last;
}

int main()
{
#ifdef CraZYali
	file("auction");
#endif
	cin >> n >> q;
	scanf("%s", s + 1);
	while (q--)
		printf("%d\n", dfs(1, read<int>(), 1, 0));
	return 0;
}
