#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2000 + 10;

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

char s[maxn];
int k;

int main()
{
#ifdef CraZYali
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif
	while (scanf("%s %d", s + 1, &k) != EOF)
	{
		int n = strlen(s + 1);
		if (n <= k) {putchar('0');putchar(10);continue;}
		while (k)
		{
			bool flag = 0;
			REP(i, 1, n - 1)
				if (s[i] > s[i+1])
				{
					REP(j, i, n - 1) s[j] = s[j+1];
					flag = 1;
					break;
				}
			if (!flag) break;
			n--;
			k--;
		}
		n -= k;
		int f = 1;
		while (f < n && s[f] == '0')f++;
		REP(i, f, n) putchar(s[i]);putchar(10);
	}
	return 0;
}
