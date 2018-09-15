#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 105;

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

char s1[maxn], s2[maxn];
long long f[maxn][32];

int main()
{
#ifdef CraZYali
	freopen("5702.in", "r", stdin);
	freopen("5702.out", "w", stdout);
#endif
	register long long n1, n2;
	while (scanf("%s %lld\n%s %lld\n", s2, &n2, s1, &n1) == 4)
	{
		long long m = 0;
		register int len1 = strlen(s1);
		register int len2 = strlen(s2);
		for (register int i = 0; i < len1; i++)
		{
			register int pos = i;
			f[i][0] = 0;
			for (register int j = 0 ; j < len2;j++)
			{
				register int cnt = 0;
				while (s1[pos] != s2[j])
				{
					pos = (pos + 1) % len1;
					if (++cnt >= len1)
					{
						printf("0\n");
						goto school;
					}
				}
				pos = (pos + 1) % len1;
				f[i][0] += cnt + 1;
			}
		}
		REP(j, 1, 30)
			for (register int i = 0; i < len1;++i)
				f[i][j] = f[i][j-1] + f[(i + f[i][j-1]) % len1][j-1];
		for (register int st = 0 ; st < len1;st++)
		{
			long long x = st, ans = 0; 
			for (register int k = 30; k >= 0;k--)
				if (x + f[x % len1][k] <= len1 * n1)
				{
					x += f[x % len1][k];
					ans += 1 << k;
				}
			chkmax(m , ans);
		}
		printf("%lld\n", m / n2);
school:;
	}
	
	return 0;
}
