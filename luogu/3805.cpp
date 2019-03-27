#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 11000000 + 10;

char t[maxn], s[maxn << 1];
int n, ans, p[maxn << 1];

int rb, mid;

int main()
{
#ifdef CraZYali
	freopen("3805.in", "r", stdin);
	freopen("3805.out", "w", stdout);
#endif
	scanf("%s", t + 1);
	n = strlen(t + 1);
	s[0] = '@';
	REP(i, 1, n * 2 + 1)
		if (i & 1) s[i] = '#';
		else s[i] = t[i >> 1];
	n = n << 1 | 1;
	REP(i, 1, n)
	{
		p[i] = i < rb ? min(p[(mid << 1) - i], rb - i) : 1;
		while (s[i - p[i]] == s[i + p[i]]) p[i]++;
		if (p[i] + i > rb) rb = p[mid = i] + i;
		chkmax(ans, p[i] - 1);
	}
	cout << ans << endl;
	return 0;
}
