#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10, maxm = 15;

template <typename T> inline T read()
{
	T ans(0), p(1);
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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k, q;

int a[maxm], x[maxn], le[maxn];

void calc(int i)
{
	le[i] = 0;
	register int l = 1, r = m;
	while (l <= r)
	{
		register int mid = l + r >> 1;
		if (x[i] >= a[mid])
		{
			le[i] = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
}
namespace bf
{
	void work()
	{
		REP(i, 1, n) calc(i);
		while (q --> 0)
		{
			register int opt = read<int>();
			if (opt == 1)
			{
				register int l = read<int>(), r = read<int>(), _x = read<int>();
				REP(i, l, r) x[i] += _x, calc(i);
			}
			else if (opt == 2)
			{
				register int p = read<int>();
				x[p] = read<int>();calc(p);
			}
			else
			{
				register int l = read<int>(), r = read<int>(), ret = 0;
				REP(i, l, r)
					ret += le[i];
				printf("%d\n", ret);
			}
		}
	}
}

namespace cheat
{
	int tot[maxn];
	void add(int x, int y)
	{
		while (x <= n)
		{
			tot[x] += y;
			x += x & -x;
		}
	}
	int sum(int x)
	{
		register int y = 0;
		while (x > 0)
		{
			y += tot[x];
			x -= x & -x;
		}
		return y;
	}

	void work()
	{
		REP(i, 1, n)
		{
			calc(i);
			add(i, le[i]);
		}
		register bool is1 = 0, is2 = 0;
		while (q --> 0)
		{
			register int opt = read<int>();
			if (opt == 1)
			{
				is1 = 1;
			}
			else if (opt == 2)
			{
				is2 = 1;
				register int p = read<int>(), _x = read<int>();
				add(p, -le[p]);
				x[p] = _x;
				calc(p);
				add(p, le[p]);
			}
			else {register int l = read<int>(), r = read<int>();printf("%d\n", sum(r) - sum(l - 1));}
		}
	}
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n >> m >> q;
	REP(i, 1, m) scanf("%d", a + i);
	REP(i, 1, n) scanf("%d", x + i);
	if (n <= 1000 && q <= 1000) bf::work();
	else cheat::work();
	return 0;
}
