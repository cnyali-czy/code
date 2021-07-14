/*
	Problem:	C.cpp
	Time:		2021-07-13 15:51
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 2e5 + 10;
const double pi = acos(-1);

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

int n, x[maxn], y[maxn];
double s1[maxn], s2[maxn], s[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 1, n) x[i] = read<int>(), y[i] = read<int>();
	const int T = 100;
	for (int z = 0; z < T; z++)
	{
		const double t = 2 * pi / T * z, ct = cos(t), st = sin(t);
		static double pos[maxn];
		REP(i, 1, n) pos[i] = x[i] * ct + y[i] * st;
		static int id[maxn];
		REP(i, 1, n) id[i] = i;
		sort(id + 1, id + 1 + n, [&](int x, int y) {return pos[x] < pos[y];});
		REP(i, 2, n) s1[i] = s1[i - 1] + (i - 1) * (pos[id[i]] - pos[id[i - 1]]);
		DEP(i, n - 1, 1) s2[i] = s2[i + 1] + (n - i) * (pos[id[i + 1]] - pos[id[i]]);
		REP(i, 1, n) s[id[i]] += s1[i] + s2[i];
	}
	REP(i, 1, n) printf("%.10lf\n", s[i] / T * (2 * pi) / 4);
	return 0;
}
