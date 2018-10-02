#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 11;

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

int n;
long long a[maxn], m[maxn];

long long exgcd(long long a, long long b, long long &x, long long &y)
{
	if (!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	register long long temp = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return temp;
}

int main()
{
#ifdef CraZYali
	freopen("3B04.in", "r", stdin);
	freopen("3B04.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) cin >> m[i] >> a[i];
	register long long M = m[1], A = a[1];
	REP(i, 2, n)
	{
		register long long x, y, g;
		if ((a[i] - A) % (g = exgcd(M, m[i], x, y)))
		{
			cout << "Impossible!";
			return 0;
		}
		x = (a[i] - A) / g * x % (m[i] / g);
		A += M * x;
		M = M / g * m[i];
		A %= M;
	}
	
	cout << (A + M) % M;
	return 0;
}
