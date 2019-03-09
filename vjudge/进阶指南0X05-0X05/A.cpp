#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 200000 + 10, maxm = 200000 + 10;

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

int n, a[maxn], m, b[maxm], c[maxm];
map <int, int> cnt;

struct movie
{
	int v1, v2, pos;
	movie(){}
	movie(int _v1, int _v2, int _pos) : pos(_pos), v1(_v1), v2(_v2){}
}M[maxm];
bool cmp(movie A, movie B) {return A.v1 > B.v1 || A.v1 == B.v1 && A.v2 > B.v2; }

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) cnt[a[i] = read<int>()]++;
	cin >> m;
	REP(i, 1, m)
	{
		int x = read<int>(), y = read<int>();
		M[i] = movie(cnt[x], cnt[y], i);
	}
	sort(M + 1, M + 1 + m, cmp);
	cout << M[1].pos << endl;
	return 0;
}
