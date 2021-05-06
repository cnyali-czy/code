/*
	Problem:	B.cpp
	Time:		2021-05-03 18:59
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
#define int long long

using namespace std;
const int maxn = 2e6 + 10;

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

int n, t, a, b, c;
int x[4], y[4], z[4];

char s[maxn << 1];
inline int sum(int l, int r) {return (l + r) * (r - l + 1) / 2;}
bool ok(int X, int Y)
{
	REP(i, 0, 3)
	{
		int hp = z[i] - abs(X - x[i]) - abs(Y - y[i]);
		int tx = X, ty = Y;
		if (tx < x[i])
		{
			hp -= sum(0, x[i] - tx - 1) + (x[i] - tx) * abs(ty - y[i]);
			tx = x[i];
		}
		if (ty < y[i])
		{
			hp -= sum(0, y[i] - ty - 1) + (y[i] - ty) * abs(tx - x[i]);
			ty = y[i];
		}
        hp -= sum(tx - x[i] + 1, n - x[i]) + (n - tx) * (ty - y[i]);
        hp -= sum(ty - y[i] + 1, n - y[i]) + (n - x[i]) * (n - ty);
		if (hp < 0) return 0;
	}
	return 1;
}
signed main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> t >> a >> b >> c;
	x[0] = a;y[0] = b;
	x[1] = a + c - 1;y[1] = b;
	x[2] = a + c - 1;y[2] = b + c - 1;
	x[3] = a;y[3] = b + c - 1;
	z[0] = z[1] = z[2] = z[3] = t;
	int X = 1, Y = 1;
	REP(i, 1, n + n - 2)
	{
		if (X < n && ok(X + 1, Y))
		{
			X++;
			s[i] = 'R';
		}
		else
		{
			Y++;
			if (!ok(X, Y))
			{
				puts("Again");
				return 0;
			}
			s[i] = 'U';
		}
		REP(i, 0, 3) z[i] -= abs(X - x[i]) + abs(Y - y[i]);
	}
	puts(s + 1);
	return 0;
}
