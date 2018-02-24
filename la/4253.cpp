#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 5010;

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

int W, n;

struct seg {
	double y, x1, x2;
}a[maxn];

int main() {
#ifdef CraZYali
	freopen("4253.in", "r", stdin);
	freopen("4253.out", "w", stdout);
#endif
	register int T;
	cin >> T;
	while (T--) {
		scanf("%d%d", &W, &n);
		REP(i, 1, n) scanf("%lf%lf%lf", &a[i].y, &a[i].x1, &a[i].x2);
		double L(0), R(W * 1.0);
		REP(i, 1, n)
			REP(j, 1, n) if (i ^ j){
				double k, b;
				//y = kx + b
				//b = y - kx
				//kx + b = 0
				//x = - b / k;
				
				if (a[i].x1 ^ a[j].x1) {
					k = (a[i].y - a[j].y) / (a[i].x1 - a[j].x1);
					b = a[i].y - a[i].x1 * k;
					chkmax(L, -b / k);
				}
				else chkmax(L, a[i].x1);

				if (a[i].x1 ^ a[j].x2) {
					k = (a[i].y - a[j].y) / (a[i].x1 - a[j].x2);
					b = a[i].y - a[i].x1 * k;
				}
			}
	}
	return 0;
}
