#define   REP(i, s, e) for(register long long i = s; i <= e ;i++)
#define  DREP(i, s, e) for(register long long i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const long long MOD = 100000007;

inline double getans(double a, double b, double c)
{
	double D = b * b - 4 * a * c;
	if (D < 0) return -1;
	return (-b + sqrt(D)) / (2 * a);
}

inline bool IsNum(double c)
{
	return c == (long long)c;
}

map <double, bool> vis;

int main()
{
#ifdef CraZYali
	freopen("11490.in", "r", stdin);
	freopen("11490.out", "w", stdout);
#endif
	bool first = 1;
	long long S;
	while (scanf("%lld", &S) != EOF && S)
	{
		if (clock() / CLOCKS_PER_SEC >= 10) return 0;
		if (first) first = 0;
		else putchar(10);
		bool flag = 0;
		vis.clear();
		DREP(r, sqrt(S) * 50, 1)
		{
			double c = getans(8, -25 * r, 18 * r * r + S);
			if (c > 0 && IsNum(c) && !vis[c])
			{
				vis[c] = 1;
				printf("Possible Missing Soldiers = %lld\n", (long long)(r * c) - S);
				flag = 1;
			}
		}
		if (!flag) printf("No Solution Possible\n");
	}

	return 0;
}
