#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 40000 + 10, maxm = 100000 + 10;

int m, n, k;

int f[maxn];
int find(int x) {return f[x] == x ? f[x] : f[x] = find(f[x]);}
inline void uni(int x, int y) {f[find(x)] = find(y);}

pair <pair <int, int> , int> a[maxm];
bool cmp(pair<pair<int, int>, int> A, pair<pair<int, int> , int> B) {return A.second > B.second;}

int main()
{
#ifdef CraZYali
	freopen("1525.in", "r", stdin);
	freopen("1525.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, m) scanf("%d%d%d", &a[i].first.first, &a[i].first.second, &a[i].second);
	sort(a + 1, a + 1 + m, cmp);

	REP(i, 1, n << 1) f[i] = i;

	REP(i, 1, m)
		if (find(a[i].first.first) == find(a[i].first.second))
		{
			cout << a[i].second;
			return 0;
		}
		else
		{
			uni(a[i].first.first, a[i].first.second + n);
			uni(a[i].first.second, a[i].first.first + n);
		}
	cout << 0;
	return 0;
}
