#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10;

template <typename T> T read()
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

int m, n, k;

struct rubbish
{
	int ti, ad, hi;
}r[maxn];

inline bool cmp(rubbish L, rubbish K) {return L.ti < K.ti;}
int dp[maxn];

int main()
{
#ifdef CraZYali
	freopen("1156.in", "r", stdin);
	freopen("1156.out", "w", stdout);
#endif
	m = read<int>();
	n = read<int>();
	REP(i, 1, n)
		r[i] = (rubbish){read<int>(), read<int>(), read<int>()};
	sort(r + 1, r + 1 + n, cmp);
	dp[0] = 10;
	REP(i, 1, n)
		DREP(j, m, 0)
			if (dp[j] >= r[i].ti)
			{
				if (j + r[i].hi >= m)
				{
					cout << r[i].ti;
					return 0;
				}
				chkmax(dp[j + r[i].hi], dp[j]);
				dp[j] += r[i].ad;
			}
	cout << dp[0];
	return 0;
}
