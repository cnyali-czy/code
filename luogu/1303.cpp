#define  REP(i, s, e) for(register int i = s; i <= e; i++)
#define DREP(i, s, e) for(register int i = s; i >= e; i--)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2000 + 10;

void reverse(char s[], int len)
{
	register int l = 1, r = len;
	while (l < r) swap(s[l++], s[r--]);
}

bool flag = 0;
char a[maxn], b[maxn], c[maxn << 1], d[maxn];
int n, m, k;

int main()
{
#ifdef CraZYali
	freopen("1303.in", "r", stdin);
	freopen("1303.out", "w", stdout);
#endif
	scanf("%s\n%s", a + 1, b + 1);
	n = strlen(a + 1);m = strlen(b + 1);
	reverse(a, n);reverse(b, m);
	if (a[n] == '-') n--, flag ^= 1;
	if (b[m] == '-') m--, flag ^= 1;
	if (flag) putchar('-');
	REP(i, 1, n) a[i] -= '0';REP(i, 1, m) b[i] -= '0';
	REP(i, 1, n)
	{
		memset(d, 0, sizeof(d));
		REP(j, 1, m)
		{
			d[j] += a[i] * b[j];
			d[j + 1] += d[j] / 10;
			d[j] %= 10;
		}
		k = m + 1;
		while (k > 1 && !d[k]) k--;
		REP(j, 1, k)
		{
			c[i + j - 1] += d[j];
			c[i + j] += c[i + j - 1] / 10;
			c[i + j - 1] %= 10;
		}
	}
	k = n + m + 3;
	while (k > 1 && !c[k]) k--;
	DREP(i, k, 1) putchar(c[i] + '0');
	return 0;
}
