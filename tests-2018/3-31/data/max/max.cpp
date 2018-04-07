#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

typedef long long LL;

const int Mod = 1e9 + 7;
const int N = 41, M = 11;

int P[N][M][4];
LL dp[N][1 << M][M * 3], f[1 << M][M * 3];
int n, m, c;

int main() {

	scanf("%d%d%d", &n, &m, &c);
	For(j, 0, m - 1) For(i, 1, n) For(k, 0, c) scanf("%d", &P[i][j][k]);

	dp[0][(1 << m) - 1][0] = 1;
	For(i, 1, n) {

		memset(f, 0, sizeof f);
		f[0][0] = 1;
		For(st, 0, (1 << m) - 1) {
			int s = __builtin_popcount(st);
			For(j, 0, m - 1) {
				if (st & (1 << j)) break;
				For(k, 0, c * s) For(d, 0, c)
					(f[st | (1 << j)][k + d] += f[st][k] * P[i][j][d]) %= Mod;
			}
		}

		For(st, 0, (1 << m) - 1) {
			int s = m - __builtin_popcount(st);
			For(j, 0, c * s) {
				LL val = dp[i - 1][st][j];
				for (int k = st; ; k = (k - 1) & st) {
					int lim = __builtin_popcount(k);
					For(d, 0, c * lim) (dp[i][st ^ k][max(j, d)] += val * f[k][d]) %= Mod;
					if (!k) break;
				}
			}
		}
	}

	LL ans = 0;
	For(i, 0, c * m) (ans += i * dp[n][0][i]) %= Mod;
	printf("%lld\n", ans);

	return 0;
}
