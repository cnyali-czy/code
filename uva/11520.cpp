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
const int maxn = 15;

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
int n, _case, d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
char a[maxn][maxn];

int main() {
#ifdef CraZYali
	freopen("11520.in", "r", stdin);
	freopen("11520.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T--) {
		n = read<int>();
		REP(i, 1, n) {
			REP(j, 1, n)
				a[i][j] = getchar();
			getchar();
		}
		REP(i, 1, n)
			REP(j, 1, n) if (a[i][j] == '.')
				for (register char c = 'A'; c <= 'Z';c++) {
					register bool flag = 1;
					REP(k, 0, 3)
						if (c == a[i + d[k][0]][j + d[k][1]]) {flag = 0;break;}
					if (flag) {a[i][j] = c;break;}
				}
		printf("Case %d:\n", ++_case);
		REP(i, 1, n) {
			REP(j, 1, n) putchar(a[i][j]);
			putchar('\n');
		}
	}

	return 0;
}
