#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

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
const int maxn = 100010;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;

int main()
{
#ifdef CraZYali
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	register long long a, b;
	cin >> a >> b;
	/*
	while (1)
	{
		if (!a || !b) break;
		else
		{
			if (a >= b * 2ll)
			{
				a -= b * 2ll;
				continue;
			}
			else
			{
				if (b >= a * 2ll)
				{
					b -= a * 2ll;
					continue;
				}
				else break;
			}
		}
	}
	*/
	while (1)
	{
		if (!a || !b) break;
		if (a >= b * 2ll)
		{
			a -= (a / (b * 2ll)) * b * 2ll;
			continue;
		}
		else if (b >= a * 2ll) b -= (b / (a * 2ll)) * (a * 2ll);
		else break;
	}
	cout << a << ' ' << b;
	//16070163 19353945
	return 0;
}
