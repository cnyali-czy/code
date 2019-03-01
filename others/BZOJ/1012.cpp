#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 200000 + 10, maxblock = 450;

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

int m, MOD, lastans;

int n, a[maxn], Max[maxblock], Left[maxblock], block_siz, block_cnt, nowsiz;

int main()
{
#ifdef CraZYali
	freopen("1012.in", "r", stdin);
	freopen("1012.out", "w", stdout);
#endif
	cin >> m >> MOD;
	nowsiz = block_siz = sqrt(m);
	while (m --> 0)
	{
		char c = getchar();
		while (c ^ 'A' && c ^ 'Q') c = getchar();
		if (c == 'A')
		{
			a[++n] = (lastans + read<int>()) % MOD;
			if (nowsiz < block_siz) chkmax(Max[block_cnt], a[n]), nowsiz++;
			else
			{
				nowsiz = 1;
				++block_cnt;
				Max[block_cnt] = a[Left[block_cnt] = n];
			}
		}
		else
		{
			int l = read<int>(), ans = a[n];
			if (l < block_siz) DREP(i, n - 1, n - l + 1) chkmax(ans, a[i]);
			else
			{
				DREP(i, block_cnt, 1)
					if (n - Left[i] + 1 <= l) chkmax(ans, Max[i]);
					else
					{
						DREP(j, Left[i + 1] - 1, n - l + 1) chkmax(ans, a[j]);
						break;
					}
			}
			printf("%d\n", lastans = ans);
		}
	}
	return 0;
}
