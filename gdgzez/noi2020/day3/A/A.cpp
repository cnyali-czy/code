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
const int maxn = 1e3 + 10;

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
int p[15][maxn];

void output(int ccc)
{
	REP(i, 0, ccc)
		REP(j, 1, n) printf("%d%c", p[i][j], j == n ? '\n' : ' ');
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	if (n == 1) return 0 * puts("1\n1");
	if (n == 2) return 0 * puts("-1");
	k = ceil(log2(n));
	int base = 1;
	REP(i, 0, k - 1)
	{
		REP(j, 1, n) p[i][j] = (j + base - 1) % n + 1;
		(base <<= 1) %= n;
	}
	if (n & 1)
	{
		cout << k << endl;
		output(k - 1);
	}
	else if (n % 4 == 0)
	{
		cout << k << endl;
		REP(i, 1, n / 4) printf("%d %d %d %d%c", 4 * i - 1, 4 * i, 4 * i - 2, 4 * i - 3, i == end_i ? '\n' : ' ' );
		output(k - 2);
	}
	else
	{
		cout << k + 1 << endl;
		printf("%d %d ", n - 1, 1);
		REP(i, 3, n - 2) printf("%d ", i);
		printf("%d %d\n", n, 2);
		REP(i, 1, n / 4) printf("%d %d %d %d ", 4 * i - 1, 4 * i, 4 * i - 2, 4 * i - 3);
		printf("%d %d\n", n - 1, n);
		output(k - 2);
	}
#ifdef CraZYali
	cerr << "-----Checker Start!-----\n";
	system("./checker");
	cerr << "-----Checker End!-----\n";
#endif
	return 0;
}
