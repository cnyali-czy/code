/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.30 21:05
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 20 + 5;
template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int w[maxn], n, N;
pair <int, int> a[1 << 20];
bool vis[1 << 20];
int lg[1 << 20];
vector <int> v;

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n;
	N = 1 << n;
	REP(i, 0, n - 1) w[i] = read<int>();
	REP(S, 1, N - 1)
	{
		if (S > 1) lg[S] = lg[S >> 1] + 1;
		a[S].second = S;
		for (int x = S; x; x &= (x - 1))
			a[S].first ^= w[lg[x & -x]];
	}
	sort(a + 1, a + N, greater <pair <int, int> >());
	long long ans = 0;
	vis[0] = 1;
	int ard = 0;
	REP(i, 1, N - 1)
		REP(j, 1, N - 1) if (!vis[a[j].second ^ ard])
		{
			ard ^= a[j].second;
			vis[ard] = 1;
			ans += a[j].first;
			v.emplace_back(ard);
			break;
		}
	cout << ans - a[1].first << endl;
	for (auto i : v) printf("%d ", i);
	return 0;
}
