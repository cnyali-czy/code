#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in AINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1005, maxL = 2005, inf = 1e9;

template <typename T> T read() {
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int m, n, k, A[maxL];
bool G[maxn][maxn];

inline void Read() {
	n = read<int>();
	m = read<int>();
	memset(G, 0, sizeof(G));
	while (m--) {
		int x, y;
		x = read<int>();
		y = read<int>();
		G[x][y] = G[y][x] = 1;
	}
	REP(i, 1, n) G[i][i] = 1;
	k = read<int>();
	REP(i, 1, k) A[i] = read<int>();
}
int dp[maxn][maxn];

int main() {
#ifdef CraZYali
	freopen("4256.in", "r", stdin);
	freopen("4256.out", "w", stdout);
#endif
	register int T = read<int>();	
	while (T--) {
		Read();
		REP(i, 1, k)
			REP(j, 1, n)
				dp[i][j] = inf;
		REP(i, 1, k)
			REP(j, 1, n)
				REP(p, 1, n)
					if (G[j][p]) chkmin(dp[i][j], dp[i-1][p] + (A[i] != j));
		int ans = dp[k][1];
		REP(i, 2, n) chkmin(ans, dp[k][i]);
		printf("%d\n", ans);
	}

	return 0;
}
