#define DREP(i, s, e) for(register unsigned long long i = s; i >= e ;i--)
#define  REP(i, s, e) for(register unsigned long long i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;

#define int unsigned long long

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

signed main()
{
#ifdef CraZYali
	freopen("T48568.in", "r", stdin);
	freopen("T48568.out", "w", stdout);
#endif
	fread(buf, sizeof(buf) / sizeof(char) - 10, 1, stdin);
	T = read();
	while (T --> 0)
	{
		n = read();
		ans = 0;
//		REP(i, 1, n)
//			ans += n % i;
		i = 1;
		while (i <= n)
		{
			p = n / i;
			if(!p) j = n;
			else j = min(n / p, n);
			a1 = n % i , an = n % j;
			ans += (j - i + 1) * (a1 + an) /2;
			i = j + 1;
		} 
		write(ans);putchar(',');
	}
	/*	
		REP(i, 1, 100)
		write(100 % i), putchar( ' ');
		putchar(10);
		REP(i, 1, 250)
		write(250 % i), putchar( ' ');
		*/
	return 0;
}
