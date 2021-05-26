#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 4e5 + 10;

int n, ans, m;
int a[maxn], b[maxn], ta[maxn], tb[maxn], tot0, data[maxn], fa[maxn];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
inline void uni(int x, int y) {fa[find(x)] = find(y);}

int rename(int val) {return lower_bound(data + 1, data + m + 1, val) - data;}

int main()
{
#ifdef CraZYali
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%d", a + i), a[n+1] ^= a[i];
	REP(i, 1, n) scanf("%d", b + i), b[n+1] ^= b[i];
	n++;
	copy(a + 1, a + 1 + n, ta + 1);
	copy(b + 1, b + 1 + n, tb + 1);
	sort(ta + 1, ta + n + 1);
	sort(tb + 1, tb + n + 1);
	REP(i, 1, n - 1) if (ta[i] ^ tb[i]) return puts("-1"), 0;

	REP(i, 1, n) 
		if(a[i] ^ b[i] || i == n)
		{
			data[++m] = a[i];
			data[++m] = b[i];
			if(i < n) ans++;
		}
	if(ans == 0) return puts("0"), 0;
	sort(data + 1, data + m + 1);
	m = unique(data + 1, data + m + 1) - data - 1;
	REP(i, 1, m) fa[i] = i;
	REP(i, 1, n) uni(rename(a[i]), rename(b[i]));
	REP(i, 1, m) ans += (i == fa[i]);
	cout << ans - 1 << endl;
	return 0;
}
