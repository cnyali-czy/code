#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;

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
typedef unsigned long long ull;
int m, n, k;

int main() {
#ifdef CraZYali
	freopen("11538.in", "r", stdin);
	freopen("11538.out", "w", stdout);
#endif
	ull n, m;
	while (cin >> n >> m) {
		if (!n && !m) return 0;
		if (n > m) swap(n, m);
		cout << n * m * (n + m - 2) + n * (n - 1) * (3 * m - n - 1) * 2 / 3 << endl;
	}
}
