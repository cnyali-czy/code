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
const int maxlen = 1e5 + 10;

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
char s[maxlen];

int main()
{
#ifdef CraZYali
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	int pos = 1;
	char now = 'a';
	while (pos <= n && now <= 'z')
	{
		while (pos <= n && s[pos] > now) pos++;
		s[pos++] = now++;
	}
	if (now <= 'z' && pos > n) cout << -1;
	else printf("%s", s + 1);
	
	
	return 0;
}
