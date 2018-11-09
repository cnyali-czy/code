#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e6 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, ne[maxn];
char a[maxn], b[maxn];

int main()
{
#ifdef CraZYali
	freopen("3375-new.in", "r", stdin);
	freopen("3375-new.out", "w", stdout);
#endif
	scanf("%s\%s", a + 1, b + 1);
	n = strlen(a + 1);m = strlen(b + 1);
	int k = 0;
	REP(i, 2, m)
	{
		while (k > 0 && b[k + 1] != b[i]) k = ne[k];
		ne[i] = k += (b[k + 1] == b[i]);
	}
	k = 0;
	REP(i, 1, n)
	{
		while (k > 0 && b[k + 1] != a[i]) k = ne[k];
		if (b[k + 1] == a[i]) k++;
		if (k == m) printf("%d\n", i - m + 1);
	}
	REP(i, 1, m) printf("%d ", ne[i]);
	return 0;
}
