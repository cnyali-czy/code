#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 20;

int n, a[maxn];
bool vis[maxn], flag;

inline bool check(int x) {
	if (x < 2) return 0;
	for (register int i = 2; i * i <= x; i++)
		if (x % i == 0) return 0;
	return 1;
}

inline void print() {
	flag = 1;
	REP(i, 1, n)
		printf("%d%c", a[i], i ^ n ? ' ' : '\n');
}

inline void dfs(int x) {
	if (x == n) {
		if (check(a[n] + 1)) print();
		return;
	}
	x++;
	REP(i, 2, n)
		if (!vis[i] && check(i + a[x - 1])) {
			vis[a[x] = i] = 1;
			dfs(x);
			vis[i] = 0;
		}
}
int _case;

int main() {
#ifdef CraZYali
	freopen("524.in", "r", stdin);
	freopen("524.out", "w", stdout);
#endif
	vector <int> v;
	while (scanf("%d", &n) != EOF) v.push_back(n);
	register int size = v.size() - 2;
	REP(i, 0, size) {
		n = v[i];
		memset(vis, 0, sizeof(vis));
		printf("Case %d:\n", ++_case);
		a[vis[1] = 1] = 1;
		dfs(1);
		if (flag) putchar('\n');
	}
	n = v[size + 1];
	memset(vis, 0, sizeof(vis));
	printf("Case %d:\n", ++_case);
	a[vis[1] = 1] = 1;
	dfs(1);
	return 0;
}
