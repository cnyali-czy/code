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
const int maxlen = 1000000 + 10;

int m, n, k;
char s1[maxlen], s2[maxlen];
int len1, len2;

int nxt[maxlen];

int main()
{
#ifdef CraZYali
	freopen("3375.in", "r", stdin);
	freopen("3375.out", "w", stdout);
#endif
	scanf("%s\n%s", s1 + 1, s2 + 1);
	len1 = strlen(s1 + 1);
	len2 = strlen(s2 + 1);

	register int j = 0;
	REP(i, 2, len2)
	{
		while (j > 0 && s2[i] ^ s2[j + 1]) j = nxt[j];
		if (s2[i] == s2[j + 1]) ++j;
		nxt[i] = j;
	}

	j = 0;
	REP(i, 1, len1)
	{
		while (j > 0 && s1[i] ^ s2[j + 1]) j = nxt[j];
		if (s1[i] == s2[j + 1]) j++;
		if (j == len2) printf("%d\n", i - len2 + 1);
	}

	REP(i, 1, len2) printf("%d ", nxt[i]);

	return 0;
}
