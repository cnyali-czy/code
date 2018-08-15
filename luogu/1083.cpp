#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e6 + 10, maxm = 1e6 + 10;

int m, n, k;
int r[maxn], d[maxm], s[maxm], t[maxm];

int tag[maxn];
bool flag;

int main()
{
#ifdef CraZYali
	freopen("1083.in", "r", stdin);
	freopen("1083.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) scanf("%d", r + i);
	REP(i, 1, m) scanf("%d%d%d", d + i, s + i, t + i);
	int L = 0;
	int R = m + 1;
	while (L + 1 < R)
	{
		register int mid = L + R >> 1;
		REP(i, 1, mid)
		{
			tag[s[i]] -= d[i];
			tag[t[i] + 1] += d[i];
		}
		register int temp = 0;
		REP(i, 1, n)
		{
			temp += tag[i];
			if (r[i] + temp < 0)
			{
				flag = 1;
				break;
			}
		}
		if (!flag) L = mid;
		else R = mid;
		flag = 0;
		memset(tag, 0, sizeof(tag));
	}
	if (L == m) cout << 0;
	else printf("-1\n%d", R);
	return 0;
}
