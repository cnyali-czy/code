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
typedef long long ll;

ll n, k, buy, type, Less;

int main() {
#ifdef CraZYali
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin >> n >> k;
	Less = n;buy = n;
	REP(i, 1, k) {
		ll temp;
		cin >> temp;
		if (temp > n) continue;
		ll less = n % temp;
		if (less < Less) {
			Less = less;
			buy = n / temp;
			type = i;
		}
		else if (less == Less && buy > n / temp) {
			buy = n / temp;
			type = i;
		}
	}
	if (Less ^ n) cout << type << ' ' << buy;
	else cout << "1 0";
	return 0;
}
