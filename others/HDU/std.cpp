#include<bits/stdc++.h>

#define fec(i, x, y) (int i = head[x], y = g[i].to; i; i = g[i].ne, y = g[i].to)
#define dbg(...) fprintf(stderr, __VA_ARGS__)
#define File(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define fi first
#define se second
#define pb push_back

template<typename A, typename B> inline char smax(A &a, const B &b) {return a < b ? a = b, 1 : 0;}
template<typename A, typename B> inline char smin(A &a, const B &b) {return b < a ? a = b, 1 : 0;}

typedef long long ll; typedef unsigned long long ull; typedef std::pair<int, int> pii;

template<typename I> inline void read(I &x) {
	int f = 0, c;
	while (!isdigit(c = getchar())) c == '-' ? f = 1 : 0;
	x = c & 15;
	while (isdigit(c = getchar())) x = (x << 1) + (x << 3) + (c & 15);
	f ? x = -x : 0;
}

const int N = 10000 + 7;
const int M = 50 + 7;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, k, m;
ll ans;
int a[N], s[N], q[N];
ll b[N], ss[N], dp[M][N];

inline void work1() {
	for (int i = 1; i <= n; ++i) b[i] = (ll)a[i] * (n - i + 1);
	std::sort(b + 1, b + n + 1, std::greater<ll>());
	for (int i = 1; i <= m; ++i) ans += b[i];
}

inline ll slope_y(const int &i, const int &j, const int &k) { return (dp[i - 1][k] - ss[k] + (ll)s[k] * k) - (dp[i - 1][j] - ss[j] + (ll)s[j] * j); }
inline ll slope_x(const int &j, const int &k) { return s[k] - s[j]; }

inline void work2() {
	for (int i = 1; i <= n; ++i) ss[i] = ss[i - 1] + s[i];
	for (int i = 1; i <= n; ++i) dp[0][i] = INF;
	for (int j = 1; j <= k; ++j) {
		int hd = 0, tl = 0;
		for (int i = 1; i <= n; ++i) {
			while (hd < tl && slope_y(j, q[tl], i) * slope_x(q[tl - 1], q[tl]) <= slope_y(j, q[tl - 1], q[tl]) * slope_x(q[tl], i)) --tl;
			q[++tl] = i;
			while (hd < tl && slope_y(j, q[hd], q[hd + 1]) <= i * slope_x(q[hd], q[hd + 1])) ++hd;
			dp[j][i] = dp[j - 1][q[hd]] + ss[i] - ss[q[hd]] - (ll)s[q[hd]] * (i - q[hd]);
		}
	}
	ans -= dp[k][n];
	std::cerr<<dp[k][n]<<std::endl;
}

inline void work() {
	work1();
	work2();
	printf("%lld\n", ans);
}

inline void cls() {
	memset(dp, 0, sizeof(dp));
	ans = 0;
}

inline void init() {
	cls();
	read(n), read(k), read(m), ++k;
	for (int i = 1; i <= n; ++i) read(a[i]), s[i] = s[i - 1] + a[i];
}

int main() {
	freopen("6619.in", "r", stdin);
	freopen("std.out", "w", stdout);
	int T;
	read(T);
	while (T--) {
		init();
		work();
	}
	fclose(stdin), fclose(stdout);
	return 0;
}
