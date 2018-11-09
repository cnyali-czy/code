#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 10000 + 10;

bool bigger(char a[], int lena, char b[], int lenb)
{
	if (lena > lenb) return 1;
	else if (lena < lenb) return 0;
	else
	{
		int len = lena;
		REP(i, 1, len)
			if (a[i] > b[i]) return 1;
			else if (a[i] < b[i]) return 0;
		return 0;
	}
}
void reverse(char s[], int len)
{
	register int l = 1, r = len;
	while (l < r) swap(s[l++], s[r--]);
}

int n, m;
char a[maxn], b[maxn];

int main()
{
#ifdef CraZYali
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	scanf("%s\n%s", a + 1, b + 1);
	n = strlen(a + 1);m = strlen(b + 1);
	if (bigger(b, m, a, n)) swap(a, b), swap(n, m), putchar('-');
	REP(i, 1, n) a[i] -= '0';REP(i, 1, m) b[i] -= '0';
	reverse(a, n);reverse(b, m);
	REP(i, 1, n)
	{
		a[i] -= b[i];
		if (a[i] < 0)
		{
			a[i] += 10;
			a[i + 1]--;
		}
	}
	while (n > 1 && a[n] == 0) n--;
	DREP(i, n, 1) putchar(a[i] + '0');

	return 0;
}
