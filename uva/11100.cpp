#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define chkmax(a, b) a = max(a, b)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;
const int maxn = 10010;

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
int n, a[maxn];
vector <int> v[maxn];

int main() {
#ifdef CraZYali
	freopen("11100.in", "r", stdin);
	freopen("11100.out", "w", stdout);
#endif
	bool first = 1;
	while (scanf("%d", &n) != EOF) {
		if (!n) return 0;
		if (first) first = 0;
		else putchar('\n');
		map <int, int> s;s.clear();
		int cnt(0), pos(1);

		REP(i, 1, n)
			chkmax(cnt, ++s[a[i] = read<int>()]);

		printf("%d\n", cnt);
		REP(i, 1, cnt) v[i].clear();
		sort(a + 1, a + 1 + n);
		REP(i, 1, n) {
			v[pos++].push_back(a[i]);
			if (pos > cnt) pos = 1;
		}
		REP(i, 1, cnt) {
			int siz = v[i].size() - 1;
			REP(j, 0, siz) printf("%d%c", v[i][j], j ^ siz ? ' ' : '\n');
		}
	}

	return 0;
}
