#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

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

using namespace std;

const int maxn = 305, MOD = 1e9;

int n, d[maxn][maxn];
char a[maxn];

inline int dp(int s, int t) {//
	if (s == t) return 1;
	if (a[s] ^ a[t]) return 0;
	int &res = d[s][t];
	if (res >= 0) return res;
	res = 0;
	REP(i, s + 2, t)
		if (a[s] == a[i] && a[i] == a[t]) res = (res + (long long)dp(s + 1, i - 1)  * (long long)dp(i, t)) % MOD;
	return res;
}

int main() {
#ifdef CraZYali
	freopen("3516.in", "r", stdin);
	freopen("3516.out", "w", stdout);
#endif
	while (scanf("%s", a + 1) != EOF) {
		n = strlen(a + 1);
		memset(d, -1, sizeof(d));
		printf("%d\n", dp(1, n));
	}

	return 0;
}
