#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 10000 + 10;

int n, l, w;

int p[maxn], r[maxn];

struct seg
{
	double l, r;
}a[maxn];
inline bool cmp(seg A, seg B) {return A.l < B.l || A.l == B.l && A.r < B.r;}

int main()
{
#ifdef CraZYali
	freopen("10382.in", "r", stdin);
	freopen("10382.out", "w", stdout);
#endif
	while (scanf("%d%d%d", &n, &l, &w) != EOF)
	{
		REP(i, 1, n)
			p[i] = read<int>(), r[i] = read<int>();
		REP(i, 1, n)
			if (r[i] * 2 <= w) continue;
			else
			{
				++m;
				a[m].l = p[i] - sqrt(r[i] * r[i] - pow(y - w * 1.0 / 2, 2));
				a[m].r = p[i] + sqrt(r[i] * r[i] - pow(y - w * 1.0 / 2, 2));
			}
		n = m;
		sort(a + 1, a + 1 + n, cmp);
		double now = a[1].r;
		int ans = 1;
		REP(i, 2, n)
			if (now < a[i].l)
			{
				now = a[i].l;
				ans++;
			}
		cout << ans << endl;
	}

	return 0;
}
