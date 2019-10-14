#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>
#define int long long 
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

int exgcd(int a, int b, int &x, int &y)
{
	if (!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int qaq = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return qaq;
}

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	int x, y, z, w, d, n, p;
	cin >> n >> p >> w >> d;
	int g = exgcd(w, d, x, y);
	if (p % g)
	{
		printf("-1\n");
		return 0;
	}
	x = (x % d + d) % d;
	y = (g - (long double)w * x) / d;
	if (x < 0 || y < 0)
	{
		printf("-1\n");
		return 0;
	}
	x *= p / g;
	y *= p / g;
	/*
	   int k;
	   k = y / w;
	   x = (long double)kk * d + x;
	   y = -(long double)kk * w + y;
	   z = n - x - y;
	   cout << x << ' ' << y <<  ' ' << z << endl;
	   if (x < 0 || y < 0 || z < 0)
	   {
	   printf("-1\n");
	   return 0;
	   }
	   if (fabs((long double)x * w + (long double)y * d - g) < 1e-8)
	   {
	   printf("%lld %lld %lld\n", x, y, z);
	   }
	   else printf("-1\n");
	   */
	int k = y / w;
	srand((unsigned long long)new char);
	REP(i, 1, 50000000)
	{
		int ccc = rand() % (k + 1);
		int xx = x + k * d;
		int yy = y - k * w;
		z = n - xx - yy;
		if (xx >= 0 && yy >= 0 && z >= 0)
		{
			cout << xx << ' ' << yy << ' ' << z << endl;
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}
