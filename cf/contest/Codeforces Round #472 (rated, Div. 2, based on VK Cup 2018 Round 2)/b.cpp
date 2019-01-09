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
const int maxn = 55, maxm = 55;

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
int m, n;
char s[maxn][maxm];
bool visX[maxn], visY[maxm];

int main()
{
#ifdef CraZYali
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	n = read<int>();
	m = read<int>();
	REP(i, 1, n) scanf("%s", s[i] + 1);
	REP(i, 1, n)
		REP(j, 1, m)
			if (s[i][j] == '#')
			{
				set <int> X, Y;
				set <int> :: iterator it;
				REP(k, 1, m)
					if (s[i][k] == '#')
					{
						Y.insert(k);
						if (visY[k])
						{
//							DEBUG;
							cout << "No";
							return 0;
						}
					}
				REP(k, 1, m)
					if (s[i][k] == '#') visY[k] = 1;
				REP(k, 1, n)
					for (it = Y.begin(); it != Y.end(); it++)
						if (s[k][*it] == '#')
						{
							X.insert(k);
							if (visX[k])
							{
//								DEBUG;
								cout << "No";
								return 0;
							}
						}
				REP(k, 1, n)
					for (it = Y.begin(); it != Y.end(); it++)
						if (s[k][*it] == '#')
						{
							visX[k] = 1;
							s[k][*it] = '.';
						}

			}
	REP(i, 1, n)
		REP(j, 1, m)
			if (s[i][j] == '#' && !(visX[i] * visY[j]))
			{
//				DEBUG;
				cout << "No";
				return 0;
			}
	cout << "Yes";
	return 0;
}
