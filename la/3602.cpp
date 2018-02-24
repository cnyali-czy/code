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
const int maxn = 60, maxlen = 1010;

int n, len;
map <char, int> a[maxlen];
char ans[maxlen], d[] = "CGTA";

int main() {
#ifdef CraZYali
	freopen("3602.in", "r", stdin);
	freopen("3602.out", "w", stdout);
#endif
	int T;
	scanf("%d\n", &T);
	while (T--) {
		memset(ans, 0, sizeof(ans));
		scanf("%d %d\n", &n, &len);
		REP(i, 1, len) a[i].clear();
		REP(i, 1, n) {
			char c;
			REP(j, 1, len)
				a[j][c = getchar()]++;
			c = getchar();
		}
		REP(i, 1, len) {
			ans[i] = 'A';
			int _max = a[i]['A'];
			REP(j, 0, 2)
				if (a[i][d[j]] > _max) {
					_max = a[i][d[j]];
					ans[i] = d[j];
				}
		}
		int sum = 0;
		REP(i, 1, len)
			REP(j, 0, 3)
				if (ans[i] ^ d[j]) sum += a[i][d[j]];
		printf("%s\n%d\n", ans + 1, sum);
	}

	return 0;
}
