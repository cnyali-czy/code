/*
	Problem:	gen.cpp
	Time:		2020-06-08 11:12
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;


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
#include <ctime>
inline long long Rand(){return 1ll*rand()*rand();}
const int maxn = 1e5 + 10;
int son[maxn], ch[maxn][3];
int main()
{
	freopen("B.in", "w", stdout);
	int n = 5, m = 5000;
	srand(time(0));
	cout << n << ' ' << m << endl;
	REP(i, 2, n)
	{
		int fa = rand() % (i - 1) + 1;
		while (son[fa] == 2) fa = rand() % (i - 1) + 1;
		ch[fa][++son[fa]] = i;
	}
	const int N = 100;
	REP(i, 1, n) printf("%d %d %d\n", Rand() % N + 1, ch[i][1], ch[i][2]);
	while (m--)
	{
		int opt = rand() & 1, x = rand() % n + 1;
		if (!opt) printf("%d %d %d\n", 1, x, Rand() % N + 1);
		else printf("%d %d\n", 3, x);
	}
	return 0;
}
