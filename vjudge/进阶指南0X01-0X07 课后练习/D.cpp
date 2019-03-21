#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 200000 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n;
pair <int, int> A[maxn];
bool cmp(pair <int, int> A, pair <int, int> B) {return A.first < B.first || A.first == B.first && A.second < B.second;}

int Max[maxn], Min[maxn];

int main()
{
#ifdef CraZYali
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) A[i] = make_pair(read<int>(), i);
	sort(A + 1, A + 1 + n, cmp);
	int cnt(0);
	REP(i, 1, n)
		if (A[i].first != A[i-1].first || i == 1)
		{
			Max[cnt] = A[i-1].second;
			Min[++cnt] = A[i].second;
		}
	Max[cnt] = A[n].second;
	int h(2e9), ans(0);
	bool cur = 1;
	REP(i, 1, cnt)
		if (!cur)
			if (h > Max[i]) h = Min[i];
			else h = Max[i], cur ^= 1;
		else
			if (h < Min[i]) h = Max[i];
			else ans++, h = Min[i], cur ^= 1;
#ifdef CraZYali
	for (int i = 1; i <= cnt;i++)
		printf("%d %d\n", Max[i], Min[i]);
#endif
	cout << ans << endl;
	
	return 0;
}
