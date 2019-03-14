#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 1000 + 10;
const double eps = 1e-8;

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

int n, d, Case;
pair <double, double> s[maxn];
bool cmp(pair<double, double> A, pair<double, double> B) {return A.second < B.second || A.second == B.second && A.first < B.first;}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &d) != EOF && (n + d))
	{
		printf("Case %d: ", ++Case);
		bool flag = 1;
		REP(i, 1, n)
		{
			int x(read<int>()), y(read<int>());
			if (abs(y) > d) flag = 0;
			else s[i] = make_pair(x - sqrt(d * d - y * y), x + sqrt(d * d - y * y));
		}
		if (!flag) printf("-1\n");
		else
		{
			sort(s + 1, s + 1 + n, cmp);
			int ans = 1;
			double nowr = s[1].second;
			REP(i, 2, n)
				if (s[i].first > nowr) ans++, nowr = s[i].second;
			printf("%d\n", ans);
		}
	}
	return 0;
}
