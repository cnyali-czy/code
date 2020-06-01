#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
#define int long long
#define i64 long long
inline int chkmin(int &x, int y) {if (x > y) {x = y;return 1;}return 0;}
template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

i64 n, s, x;

namespace bf
{
	const int N = 70;
	int f[65][N + 5], dig[70];
	inline int get(i64 x, int p) {return x >> p & 1;}
	inline void mark(i64 &x, int p) {x |= (1ll << p);}
	bool check(i64 M)
	{
		memset(f, 0x3f, sizeof f);
		const int inf = f[0][0];
		f[60][0] = 0;
		DEP(i, 60, 1)
		{
			int mi = get(M, i - 1);
			REP(j, 0, N) if (f[i][j] < inf)
			{
				int u = dig[i - 1] + f[i][j];
				if (!mi)
				{
					int v = 0;
					if (u > j)
					{
						int qaq = (u - j + 1) / 2;
						u -= 2 * qaq;
						v += 4 * qaq;
					}
					if (u < 0) continue;
					chkmin(f[i - 1][j], v);
				}
				else
				{
					if (j >= 3 && !f[i][j]) return 1;
					int v = 0;
					if (u > n)
					{
						int qaq = (u - n + 1) / 2;
						u -= 2 * qaq;
						v += 4 * qaq;
					}
					while (u >= 0)
					{
						int jj = n - max(u, j) + j;
						if (jj >= 3 && !v) return 1;
						if (jj <= N) chkmin(f[i - 1][jj], v);
						if (v > 0 && jj >= 5 && jj - j >= 2) break;
						u -= 2;v += 4;
					}
				}
			}
		}
		REP(i, 0, N) if (!f[0][i]) return 1;
		return 0;
	}
	int main()
	{
		register int T = read<int>();
		REP(Case, 1, T) 
		{
			n = read<i64>();s = read<i64>();x = read<i64>();
			if (s < x || (x & 1) != (s & 1)) {puts("-1");continue;}
			if (n == 1) {printf("%lld\n", s == x ? s : -1);continue;}
			REP(i, 0, 59) dig[i] = get(x, i) + 2 * get(s - x >> 1, i);
			if (n == 2)
			{
				i64 a = 0, b = 0;
				bool flag = 1;
				DEP(i, 59, 0)
				{
					if (dig[i] == 1) mark(b, i);
					else if (dig[i] == 2) mark(b, i), mark(a, i);
					else if (dig[i] == 3) flag = 0;
					if (a < b) swap(a, b);
				}
				printf("%lld\n", flag && a + b == s && (a ^ b) == x ? max(a, b) : -1);
				continue;
			}
			register i64 l = 0, r = s , ans = -1;
			while (l <= r)
			{
				i64 mid = l + r >> 1;
				if (check(mid))
				{
					ans = mid;
					r = mid - 1;
				}
				else l = mid + 1;
			}
			cout << ans << '\n';
		}
		return 0;
	}
}

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	return bf::main();
}
