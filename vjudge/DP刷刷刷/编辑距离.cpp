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
const int maxn = 1000 + 10;

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
char s1[maxn], s2[maxn];
int d[maxn][maxn];

int main()
{
#ifdef CraZYali
	freopen("编辑距离.in", "r", stdin);
	freopen("编辑距离.out", "w", stdout);
#endif
	scanf("%s\n%s", s1 + 1, s2 + 1);
	int len1(strlen(s1 + 1)), len2(strlen(s2 + 1));
	REP(i, 0, len1) d[i][0] = i;
	REP(j, 0, len2) d[0][j] = j;
	REP(i, 1, len1)
		REP(j, 1, len2) d[i][j] = min(min(d[i][j - 1], d[i - 1][j]) + 1, d[i - 1][j - 1] + (s1[i] != s2[j]));
	cout << d[len1][len2];
	
	return 0;
}
