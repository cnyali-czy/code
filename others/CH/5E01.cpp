#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 350 + 5, maxm = 120 + 5, maxtot = 40 + 5;

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

int a[maxn], b[maxm], cnt[5];

int dp[maxtot][maxtot][maxtot][maxtot];

int main()
{
#ifdef CraZYali
	freopen("5E01.in", "r", stdin);
	freopen("5E01.out", "w", stdout);
#endif
	cin >> n >> m;
	
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, m) cnt[b[i] = read<int>()]++;

	REP(A, 0, cnt[1])
		REP(B, 0, cnt[2])
			REP(C, 0, cnt[3])
				REP(D, 0, cnt[4])
				{
					if (A) chkmax(dp[A][B][C][D], dp[A-1][B][C][D]);
					if (B) chkmax(dp[A][B][C][D], dp[A][B-1][C][D]);
					if (C) chkmax(dp[A][B][C][D], dp[A][B][C-1][D]);
					if (D) chkmax(dp[A][B][C][D], dp[A][B][C][D-1]);
					dp[A][B][C][D] += a[A + B * 2 + C * 3 + D * 4 + 1];
				}

	cout << dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]];	

	return 0;
}
