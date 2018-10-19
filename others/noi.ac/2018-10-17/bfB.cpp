#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

#define int long long
using namespace std;
const int maxn = 2000 + 10;

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

int cnt, a[maxn];
bool is[maxn];

bool check(int T)
{
	REP(i, 1, n - T)
		if (s[i] ^ s[i + T]) return 0;
	return 1;
}

signed main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("std.out", "w", stdout);
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	
	REP(i, 1, n)
		REP(X, 1, 26)
		{
			register char temp = 'a' + X - 1;
			if (temp == s[i]) continue;
			else
			{
				swap(s[i], temp);

				REP(T, 1, n - 1)
					if (!is[T] && check(T))
					{
						is[T] = 1;
						a[++cnt] = T;
					}
				swap(s[i], temp);
			}
		}

	cout << cnt << endl;
	int c = cnt / 100000 + (cnt % 100000 ? 1 : 0), now = c;

	sort(a + 1, a + cnt + 1);
	while (now <= cnt)
	{
		printf("%lld ", a[now]);
		now += c;
	}

	return 0;
}
