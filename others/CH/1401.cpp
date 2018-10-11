#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

#define int unsigned long long
using namespace std;
const int maxn = 1000000 + 10;

template <typename T> inline T read()
{
	T ans(0), p(1);
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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;
char s[maxn];

int H[maxn], power[maxn];

int Hash(int l, int r) {return H[r] - H[l - 1] * power[r - l + 1];}

signed main()
{
#ifdef CraZYali
	freopen("1401.in", "r", stdin);
	freopen("1401.out", "w", stdout);
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);

	REP(i, 1, n) H[i] = H[i - 1] * 19260817 + s[i] - 'a' + 1;
	power[0] = 1;
	REP(i, 1, n) power[i] = power[i-1] * 19260817;
	
	cin >> m;
	while ( m --> 0 )
	{
		register int l1 = read<int>(), r1 = read<int>(), l2 = read<int>(), r2 = read<int>();
		if (Hash(l1, r1) == Hash(l2, r2)) printf("Yes\n");
		else printf("No\n");
	}

	return 0;
}
