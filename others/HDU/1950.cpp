#define  REP(i, s, e) for (register int i = s; i <= e ; i++)
#define DREP(i, s, e) for (register int i = s; i >= e ; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 40000 + 10;

int arr[maxn], ans[maxn], len;

int search(int i)
{
	register int l = 1, r = len, res = 0;
	while (l <= r)
	{
		register int mid = l + r >> 1;
		if (ans[mid] >= arr[i])
		{
			res = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	return res;
}

int n, m, k;

int main()
{
#ifdef CraZYali
	freopen("1950.in", "r", stdin);
	freopen("1950.out", "w", stdout);
#endif
	int T;
	cin >> T;
	while(T--)
	{
		scanf("%d", &n);
		REP(i, 1, n) scanf("%d", arr + i);

		ans[1] = arr[1];
		len = 1;
		REP(i, 2, n)
			if (arr[i] > ans[len]) ans[++len] = arr[i];
			else ans[search(i)] = arr[i];
		printf("%d\n", len);
	}
	return 0;
}
