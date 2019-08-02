#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, b);

#include <iostream>
#include <cstring>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 64, MOD = 1e9 + 7;

int n, m, k, lim, ans;
struct Matrix
{
	int t[maxn][maxn];
	Matrix() {memset(t, 0, sizeof(t));}
	inline Matrix operator * (Matrix B)
	{
		Matrix A = *this, res;
		REP(i, 0, lim)
			REP(j, 0, lim)
				REP(k, 0, lim) (res.t[i][j] += A.t[i][k] * B.t[k][j] % MOD) %= MOD;
		return res;
	}
	inline Matrix operator *= (Matrix B) {return *this = *this * B;}
}res, base;
bool flag[64];
inline void work(int cur, int dep)
{
    flag[cur] = base.t[cur >> 1][cur] = 1;
	base.t[(cur >> 1) | (1 << m-1)][cur] |= (!!(dep ^ k) | !!(cur & 1));
}
void dfs(int x, int cur, int dep)
{
	if (x == m) work(cur, dep);
	else
	{
		x++;
		dfs(x, cur, dep);
		if (dep < k) dfs(x, cur | (1 << x - 1), dep + 1);
	}
}
void calc()
{
	bool first(1);
	while (n)
	{
		if (n & 1) first ? first = 0, res = base : res *= base;
		base *= base;
		n >>= 1;
	}
}
signed main()
{
#ifdef CraZYali
	freopen("1357.in", "r", stdin);
	freopen("1357.out", "w", stdout);
#endif
	cin >> n >> m >> k;
	lim = (1 << m) - 1;
	dfs(0, 0, 0);
	calc();
	REP(i, 0, lim) (ans += flag[i] * res.t[i][i]) %= MOD;
	cout << ans << endl;
	return 0;
}
