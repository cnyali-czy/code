/*
	Problem:	D.cpp
	Time:		2021-01-18 21:51
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
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

int k;
int n;
vector <pair <int, int> > E;
void add(int x, int y) {E.emplace_back(x, y);}
void build()
{
	int x = ++n;
	REP(i, 1, k - 1)
	{
		n++;
		add(n, x);
	}
	REP(i, 1, k - 1)
	{
		n++;
		REP(j, x + 1, x + k - 1) add(n, j);
		if (i & 1) add(n, n + 1);
	}
}

int main()
{
#ifdef CraZYali
	file("D");
#endif
	k = read<int>();
	if (k % 2 == 0) return 0 * puts("NO");
	puts("YES");
	
	build();
	add(1, n + 1);
	build();

	cout << n << ' ' << E.size() << endl;
	for (auto i : E) printf("%d %d\n", i.first, i.second);
	
	return 0;
}
