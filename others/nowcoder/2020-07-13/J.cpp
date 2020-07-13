#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#define int __int128

using namespace std;

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
void write(int x)
{
	if (x < 0) {putchar('-');write(-x);return;}
	if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int n, a1, b1, a2, b2, x;

int exgcd(int a, int b, int &x, int &y)
{
	if (!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int ans = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return ans;
}

signed main()
{
#ifdef CraZYali
	freopen("J.in", "r", stdin);
	freopen("J.out", "w", stdout);
#endif
	int n = read<int>(), b1 = read<int>(), a1 = read<int>(), lcm;
	x = a1;
	while (--n)
	{
		b2 = read<int>();a2 = read<int>();
		int k, temp, g(exgcd(b1, b2, k, temp));
		k *= (a2 - a1) / g;
		lcm = b1 * b2 / g;
		x = a1 = (b1 * k + a1) % lcm;
		b1 = lcm;
	}
	write((x + lcm) % lcm);
	return 0;
}
