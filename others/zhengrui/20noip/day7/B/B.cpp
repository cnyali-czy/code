#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, MOD = 1e9 + 7;

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

int n, q;
int opt[maxn], l[maxn], r[maxn];
namespace fen
{
	int s[maxn];
	void add(int x, int y)
	{
		while (x <= q)
		{
			s[x] = (s[x] + y) % MOD;
			x += x & -x;
		}
	}
	void add(int l, int r, int y)
	{
		add(l, y);
		add(r + 1, MOD - y);
	}
	int sum(int x)
	{
		long long y = 0;
		while (x > 0)
		{
			y += s[x];
			x &= (x - 1);
		}
		return y % MOD;
	}
}
int s[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();q = read<int>();
	REP(i, 1, q)
	{
		opt[i] = read<int>();
		l[i] = read<int>();
		r[i] = read<int>();
	}
	DEP(i, q, 1)
	{
		int t = fen :: sum(i) + 1;
		if (opt[i] == 1)
		{
			s[l[i]] = (s[l[i]] + t) % MOD;
			s[r[i] + 1] = (s[r[i] + 1] + MOD - t) % MOD;
		}
		else fen :: add(l[i], r[i], t);
	}
	REP(i, 1, n)
	{
		s[i] = (s[i - 1] + s[i]) % MOD;
		printf("%d%c", s[i], i == end_i ? '\n' : ' ');
	}
	return 0;
}
