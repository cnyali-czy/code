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
const int maxn = 20000 + 10;

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
int m, n, k;
int d[maxn], f[maxn];
inline int find(int x) {
	if (f[x] == x) return x;
	else {
		int fa = find(f[x]);
		d[x] += d[f[x]];
		return f[x] = fa;
	}
}

int main() {
#ifdef CraZYali
	freopen("3027.in", "r", stdin);
	freopen("3027.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T--) {
		n = read<int>();
		memset(d, 0, sizeof(d));
		REP(i, 1, n) f[i] = i;
		while (1) {
			char c = getchar();
			if (c == 'O') break;
			while (c ^ 'I' && c ^ 'E') {if (c == 'O') goto nomore;c = getchar();}
			if (c == 'I') {
				int u, v;
				u = read<int>();
				v = read<int>();
				d[u] = abs(u - v) % 1000;
				f[u] = v;
			}
			else {
				int u = read<int>();
				find(u);
				printf("%d\n", d[u]);
			}
		}
nomore:;
	}

	return 0;
}
