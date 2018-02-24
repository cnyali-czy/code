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
const int maxn = 51;

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
string a[maxn];

inline bool cmp(string a, string b) {
	int lena, lenb, _min = min(lena = a.size() - 1, lenb = b.size() - 1);
	REP(i, 0, _min)
		if (a[i] < b[i]) return 0;
		else if (a[i] > b[i]) return 1;
	if (lena == lenb) return 1;
	if (lena > lenb) return cmp(a.substr(lenb + 1, (a.size() - b.size())), b);
	else return cmp(a, b.substr(lena + 1, (b.size() - a.size())));
}

int main() {
#ifdef CraZYali
	freopen("10905.in", "r", stdin);
	freopen("10905.out", "w", stdout);
#endif
	ios::sync_with_stdio(0);
	while (cin >> n && n) {
		REP(i, 1, n) cin >> a[i];
		sort(a + 1, a + 1 + n, cmp);

		REP(i, 1, n) cout << a[i];
		cout << endl;
	}

	return 0;
}
