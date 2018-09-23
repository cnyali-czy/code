#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxs = 5e5 + 10, maxq = 5e5 + 10, maxn = maxs;
const long long inf = 1ll << 60ll;

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

long long m, n, k, s, q;

struct node
{
	long long x;
	int d;
}Q[maxn << 1];

bool cmp(node AAA, node BBB) {return AAA.x < BBB.x;}

int main()
{
#ifdef CraZYali
	freopen("4885.in", "r", stdin);
	freopen("4885.out", "w", stdout);
#endif
	cin >> n >> m >> s >> q;
	register long long A = m - 1, B = 0, C = 0, D = m - 1;
	register int sz = 0;

	REP(i, 1, s)
	{
		register long long a, b, x, y;
		a = read<long long>();
		b = read<long long>();
		x = (a - 1) % m;
		y = m - b + a - 1;
		if (y >= x)
		{
			Q[++sz] = (node){y - x + 1, 1};
			Q[++sz] = (node){m - x, -1};
		}
		else
		{
			chkmax(C, m - x);
			chkmax(D, D + y - x);
		}
	}
	Q[++sz] = (node){-inf, 1};
	Q[++sz] = (node){C, -1};
	Q[++sz] = (node){D + 1, 1};
	Q[++sz] = (node){inf, -1};

	sort(Q + 1, Q + sz + 1, cmp);
	long long L = -inf, R, sum = 0, ans = 0;
	for (register int i = 1; i<=sz; )
	{
		if(sum <= 0) ans += Q[i].x - L, k = L;
		L = Q[i].x;
		for (;Q[i].x == L && i <= sz; i++)
			sum += Q[i].d;
	}
	if (ans == 0)
		cout << "Impossible!";
	else if (ans > 1)
		cout << "Uncertain!";
	else
	{
		k++;
		long long anss = 0;
		REP(i, 1, q)
		{
			register long long t = read<long long>();
			register long long x = (k + t - 2) / m + 1;
			register long long y = (k + t - 2) % m + 1;
			if (x < 1 || x > n || y < 1 || y > m) continue;
			anss ^= x ^ y;
		}
		cout << anss;
	}
	return 0;
}
