#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxlen = 1000;

inline void reverse(char s[], int len)
{
	int l(1), r(len);
	while (l < r) swap(s[l++], s[r--]);
}

char a[maxlen], b[maxlen], c[maxlen];
int lena, lenb;

int main()
{
#ifdef CraZYali
	freopen("1601.in", "r", stdin);
	freopen("1601.out", "w", stdout);
#endif

	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));

	scanf("%s\n%s", a + 1, b + 1);
	lena = strlen(a + 1);
	lenb = strlen(b + 1);
	
	reverse(a, lena);
	reverse(b, lenb);

	int lenc = max(lena, lenb) + 1;

	REP(i, 1, lenc - 1)
	{
		c[i] += (i <= lena ? a[i] : '0') + (i <= lenb ? b[i] : '0') - '0' - '0';
		while (c[i] > 9) {c[i] -= 10;c[i + 1]++;}
	}

	while (lenc > 1 && c[lenc] == 0) lenc--;
	DREP(i, lenc, 1) putchar(c[i] + '0');

	return 0;
}
