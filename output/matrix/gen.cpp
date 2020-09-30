/*
	Problem:	gen.cpp
	Time:		2020-09-30 16:15
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <vector>
#include <random>
#include <iostream>
#include <cstdio>
#include <ctime>
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
const int maxn = 5000 + 10;
int G[maxn][maxn];
mt19937 hh;
int LIM;
int randint(int l, int r) {return hh() % (r - l + 1) + l;}
int fa[maxn];
vector <pair <int, int> > v;

int main()
{
	freopen("matrix5.in", "w", stdout);
	hh = mt19937(time(0));
	int n = 2000;
	cout << n << endl;
	auto LIM = (1ll << 32) - 1;
	const double alpha = 0.2;
	REP(i, 2, n)
	{
		fa[i] = hh() % (i - 1) + 1;
		G[fa[i]][i] = 1;
	}
	DEBUG;
	REP(i, 2, n)
		for (int x = fa[i]; x; x = fa[x])
			v.emplace_back(x, i);
	DEBUG;
	shuffle(v.begin(), v.end(), hh);
	DEBUG;
	REP(i, 0, v.size() * .5)
		G[v[i].first][v[i].second] = 1;
	DEBUG;
	cerr<<endl;
	REP(i, 1, 10000)
	{
		int x = hh() % n + 1, y = hh() % n + 1;
		if (x == y) continue;
		if(x<y)swap(x,y);
		G[x][y] = 1;
	}
	DEBUG;
	REP(i, 1, n)
	{
		REP(j, 1, n)
		printf("%.3lf%c", G[i][j] ? hh() * 1. / LIM : .0, j == end_j ? '\n' : ' ');
		if (i%50==0)cerr<<i<<endl;
	}
	DEBUG;
	return 0;
}
