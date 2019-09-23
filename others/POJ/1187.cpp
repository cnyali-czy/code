#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 10 + 5, MOD = 11380;

int L1, L2, L3, D;
int f[15][15][15][35];

#define file(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)

int main()
{
#ifdef CraZYali
	file("1187");
#endif
	cin >> L1 >> L2 >> L3 >> D;
	if (L1 + L2 + L3 > 0 && !D)
	{
		cout << 0 << endl;
		return 0;
	}
	REP(i, 0, D) f[0][0][0][i] = 1;
	int sum = L1 + L2 + L3;

	REP(k, 1, sum)
		REP(l1, 0, L1)
		REP(l2, 0, min(k - l1, L2))
		{
			int l3 = k - l1 - l2;
			if (l3 > L3) continue;
			REP(d, 1, D)
			{
				int &cur = f[l1][l2][l3][d];
				cur = 0;
				REP(ii, 1, l1)
					REP(jj, 0, l2)
					REP(kk, 0, l3)
					(cur += f[ii-1][jj][kk][d-1] * f[l1-ii][l2-jj][l3-kk][d]) %= MOD;
				REP(jj, 1, l2)
					REP(kk, 0, l3)
					(cur += f[0][jj-1][kk][d-1] * f[l1][l2-jj][l3-kk][d]) %= MOD;
				REP(kk, 1, l3)
					(cur += f[0][0][kk-1][d-1] * f[l1][l2][l3-kk][d]) %= MOD;
			}
		}
	cout << (f[L1][L2][L3][D] - f[L1][L2][L3][D-1] + MOD) % MOD  << endl;
	return 0;
}
