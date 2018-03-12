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

inline int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
inline int lcm(int a, int b) {return a * b / gcd(a, b);}

int main()
{
#ifdef CraZYali
	freopen("11388.in", "r", stdin);
	freopen("11388.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int T, G, L, temp;
	cin >> T;
	while (T--)
	{
		cin >> G >> L;
		if (L % G) cout << "-1\n";
		else
		{
			temp = L / G;
			for (register int x = 1; x * x <= temp ;x++)
				if (temp % x == 0)
				{
					cout << x * G << ' ' << L / x << endl;
					break;
				}
		}
	}
	return 0;
}
