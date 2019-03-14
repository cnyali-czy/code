#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 100000 + 10, maxm = 100000 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
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

int n, m, v[100 + 5];
bool cmp(pair <int, int> A, pair <int, int> B) {return A.first > B.first || A.first == B.first && A.second > B.second;}
pair <int, int> A[maxn], B[maxn];

signed main()
{
#ifdef CraZYali
	freopen("F.in", "r", stdin);
	freopen("F.out", "w", stdout);
#endif
	while (scanf("%lld%lld", &n, &m) != EOF)
	{
		REP(i, 0, 100) v[i] = 0;
		REP(i, 1, n)
		{
			int x(read<int>()), y(read<int>());
			A[i] = make_pair(x, y);
		}
		REP(i, 1, m)
		{
			int x(read<int>()), y(read<int>());
			B[i] = make_pair(x, y);
		}
		sort(A + 1, A + 1 + n, cmp);
		sort(B + 1, B + 1 + m, cmp);
		int cur = 1, cnt(0), ans(0);
		REP(i, 1, m)
		{
			while (cur <= n && A[cur].first >= B[i].first) v[A[cur++].second]++;
			REP(k, B[i].second, 100)
				if (v[k])
				{
					cnt++;
					ans += (500ll * B[i].first + 2ll * B[i].second);
					v[k]--;
					break;
				}
		}
		printf("%lld %lld\n", cnt, ans);
	}
	return 0;
}
