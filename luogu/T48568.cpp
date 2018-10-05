#define DREP(i, s, e) for(register unsigned long long i = s; i >= e ;i--)
#define  REP(i, s, e) for(register unsigned long long i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e7 + 5;

#define int unsigned long long

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

char buf[110000000], *inf = buf;

int read()
{
	register int ans = 0;
	while (!isdigit(*inf)) inf++;
	while (isdigit(*inf))
	{
		ans = ans * 10 + *inf - '0';
		inf++;
	}
	return ans;
}

int T, n, ans, i, p, j, a1, an;

bool notprime[maxn];
int prime[maxn], p_cnt;

int d[maxn], sp[maxn];

signed main()
{
#ifdef CraZYali
	freopen("T48568.in", "r", stdin);
	freopen("T48568.out", "w", stdout);
#endif
	fread(buf, sizeof(buf) / sizeof(char) - 10, 1, stdin);
	T = read();

	n = 1e7;
	d[1] = 1;

	REP(i, 2, n)
	{
		if (!notprime[i]) d[prime[++p_cnt] = i] = sp[i] = (int)1 + i;
		REP(j, 1, p_cnt)
		{
			if (prime[j] > i || prime[j] * i > n) break;
			notprime[prime[j] * i] = 1;
			if (i % prime[j]) d[i * prime[j]] = d[i] * d[prime[j]], sp[i * prime[j]] = prime[j] + 1;
			else
			{
				sp[i * prime[j]] = sp[i] * prime[j] + 1;
				d[i * prime[j]] = d[i] / sp[i] * sp[i * prime[j]];
				break;
			}
		}
	}

	REP(i, 2, n) d[i] += d[i-1];

	while (T --> 0)
	{
		n = read();
		write(n * n - d[n]);putchar(10);
	}
	return 0;
}
