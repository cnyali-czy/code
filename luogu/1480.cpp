#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 5000 + 10;

int n, b;
char a[maxn], c[maxn];

int main()
{
#ifdef CraZYali
	freopen("1480.in", "r", stdin);
	freopen("1480.out", "w", stdout);
#endif
	scanf("%s\n%d", a + 1, &b);n = strlen(a + 1);
	int k = 0, x = 0, s = 0;
	REP(i, 1, n)
	{
		x = x * 10 + a[i] - '0';
		if (x / b != 0) s++;
		if (!s) continue;
		c[++k] = x / b;
		x %= b;
	}
	REP(i, 1, k) putchar(c[i] + '0');
	return 0;
}
