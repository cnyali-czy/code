#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;
const int maxn = 2e5 + 10;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n;
int a[maxn], b[maxn];
long long k, ans;

inline bool judge(long long mid)
{
	long long k = ::k;
	REP(i, 1, n) if (1ll * a[i] * b[i] > mid)
	{
		long long dl = 1ll * a[i] * b[i] - mid;
		long long need = max(0ll, dl / b[i] + (dl % b[i] == 0 ? 0 : 1));
		if (k >= need) k -= need;
		else return 0;
	}
	return 1;
}

int main()
{
#ifdef CraZYali
	file("E");
#endif
	cin >> n >> k;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, n) b[i] = read<int>();
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + n, greater <int> ());
	long long l = 0, r = 1e12;
	while (l <= r)
	{
		long long mid = l + r >> 1;
		if (judge(mid)) r = mid - 1;
		else l = mid + 1;
	}
	cout << r + 1 << endl;
	return 0;
}
