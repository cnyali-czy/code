#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 200000 + 10;

int m, n, k;

int c[maxn];
inline void add(int x, int y) {
	while (x <= n) {
		c[x] += y;
		x += x & -x;
	}
}
inline int sum(int x) {
	int res = 0;
	while (x > 0) {
		res += c[x];
		x -= x & -x;
	}
	return res;
}
int _case;

int main() {
#ifdef CraZYali
	freopen("2191.in", "r", stdin);
	freopen("2191.out", "w", stdout);
#endif
	ios::sync_with_stdio(0);
	bool first = 1;
	while (cin >> n) {
		if (!n) return 0;
		else
			if (!first) cout << '\n';
			else first = 0;
		memset(c, 0, sizeof(c));
		REP(i, 1, n) {
			cin >> k;
			add(i, k);
		}
		cout << "Case " << ++_case << ":\n";
		string s;
		int x, y;
		while (cin >> s)
			if (s == "END") break;
			else {
				cin >> x >> y;
				if (s == "M") cout << sum(y) - sum(x - 1) << endl;
				else add(x, y - sum(x) + (sum(x - 1)));
			}
	}
	return 0;
}
