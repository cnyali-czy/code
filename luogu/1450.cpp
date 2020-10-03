/*
	Problem:	qaq.cpp
	Time:		2020-06-16 20:53
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
#define poly vector <i64> 
#define i64 long long
#define ui64 unsigned i64

inline int deg(const poly &a) {return a.size() - 1;}
inline poly operator * (poly a, poly b)
{
	int n = deg(a), m = deg(b);
	poly c(n + m + 1, 0);
	REP(i, 0, n) if (a[i])
		REP(j, 0, m)
		c[i + j] += a[i] * b[j];
	return c;
}
void output(poly a)
{
	REP(i, 0, (int)a.size() - 1) printf("%lld%c", a[i], i == end_i ? '\n' : ' ');
}
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

poly Inv(poly f)
{
	int n = deg(f);
	vector <int> v;
	REP(i, 0, n) if (f[i]) v.emplace_back(i);
	poly a(n + 1);a[0] = 1;
	REP(i, 1, n)
	{
		i64 tmp = 0;
		for(auto j : v) if (j <= i)
			tmp += f[j] * a[i - j];
		else break;
		a[i] = -tmp;
	}
	return a;
}

int c[5], n, d[5], s;

int main()
{
#ifdef CraZYali
	file("1450");
#endif
	REP(i, 1, 4) c[i] = read<int>(); n = read<int>();
	poly f1(c[1] + 1, 0);f1[0] = 1;f1[c[1]] = -1;
	poly f2(c[2] + 1, 0);f2[0] = 1;f2[c[2]] = -1;
	poly f3(c[3] + 1, 0);f3[0] = 1;f3[c[3]] = -1;
	poly f4(c[4] + 1, 0);f4[0] = 1;f4[c[4]] = -1;
	const int N = 1e5;
	poly f = f1 * f2 * f3 * f4;
	f.resize(N);
	f = Inv(f);
	while (n--)
	{
		REP(i, 1, 4) d[i] = read<int>();s = read<int>();
		i64 ans = 0;
		REP(S, 0, (1 << 4) - 1)
		{
			int qaq = 0;
			int sgn = 1;
			REP(i, 1, 4) if (S >> (i - 1) & 1)
			{
				sgn = -sgn;
				qaq += c[i] * (d[i] + 1);
			}
			if (qaq <= s) ans += sgn * f[s - qaq];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
