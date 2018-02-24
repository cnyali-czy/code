#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define chkmin(a, b) a = min(a, b)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 100010;

int n, k;
int s[maxn], a[maxn];

int main() {
#ifdef CraZYali
	freopen("2678.in", "r", stdin);
	freopen("2678.out", "w", stdout);
	freopen("2678.debug", "w", stderr);
#endif
	while (scanf("%d %d", &n, &k) != EOF) {
		s[0] = 0;
		REP(i, 1, n) {
			scanf("%d", a + i);
			s[i] = a[i] + s[i - 1];
		}
		register int ans = n + 1;
		REP(i, 1, n)
			if (s[n] - s[i - 1] >= k) {
				register int L, R, mid, lmid;
				L = i;R = n;
				while (L < R) {
					lmid = mid;
					mid = (L + R) >> 1;
					if (s[mid] - s[i - 1] >= k) R = mid;
					else L = mid + 1;
				}
				chkmin(ans, R - i + 1);
			}
			else break;
		printf("%d\n", ans != n + 1 ? ans : 0);
	}

	return 0;
}
