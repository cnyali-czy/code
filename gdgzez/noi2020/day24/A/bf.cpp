#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;
#define i64 long long
const int maxn = 6.5e7;
const i64 block = 1e18;//block = 10000;
unsigned i64 a[maxn];

void write(__int128 x)
{
	if (x / 10) write(x / 10);
	putchar(x % 10 + 48);
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	char c = getchar();
	a[n = 1] = 0;
	while (isdigit(c))
	{
		REP(i, 1, n) a[i] *= 2;
		if (c == '1') a[1]++;
		n++;
		REP(i, 1, n) if (a[i] >= block)
		{
			a[i + 1] += a[i] / block;
			a[i] %= block;
		}
		while (!a[n]) n--;
		c = getchar();
	}
	int cnt = 0;
	while (n != 1 || a[1] != 1)
	{
//		__int128 x = 0;
//		DEP(i, n, 1) x = x * block + a[i];
//		write(x);puts("");
//		DEP(i, n, 1) printf("%d", a[i]);puts("");
		cnt++;
		if (a[1] & 1)//3n + 1
		{
			REP(i, 1, n) a[i] *= 3;
			a[1]++;
			n++;
			REP(i, 1, n) if (a[i] >= block)
			{
				a[i + 1] += a[i] / block;
				a[i] %= block;
			}
			while (!a[n]) n--;
		}
		else//n div 2
		{
			bool lst = 0;
			DEP(i, n, 1)
			{
				if (lst) a[i] += block;
				lst = a[i] & 1;
				a[i] >>= 1;
			}
			while (!a[n]) n--;
		}
	}
	cout << cnt << endl;
	return 0;
}
