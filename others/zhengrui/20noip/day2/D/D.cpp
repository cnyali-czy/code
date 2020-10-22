#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 5000 + 10;
const int inf = 1e15;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
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

inline bool chkmax(int &x, int y)
{
	if (x <= y)
	{
		x = y;
		return 1;
	}
	return 0;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, a[maxn], s[maxn];
int dp[maxn][maxn], g[maxn], f[maxn];
int sum(int l, int r) {return s[r] - s[l - 1];}
int M;

struct Vector
{
	int x, y;
	Vector(int x = 0, int y = 0) : x(x), y(y) {}
	inline Vector operator - (Vector B) {return Vector(x - B.x, y - B.y);}
	inline int operator * (Vector B) {return x * B.y - y * B.x;}
};
Vector p[maxn], stk[maxn];
int top;

pair <int, int*> todo[maxn];
int tN;

int id[maxn], X[maxn];
int N;

inline int Y(int j) {return g[j] + s[j - 1] * M;}

void solve(int m)
{
	M = s[m - 1];

	REP(i, 1, tN)
	{
		if (i == 1) tN = 0;
		if (todo[i].first != m - 1) todo[++tN] = todo[i];
	}

	bool flag = 0;
	REP(i, 1, N)
		if (s[id[i] - 1] < s[m - 2]) continue;
		else 
		{
			++N;
			DEP(j, N, i + 1) id[j] = id[j - 1];
			id[i] = m - 1;
			flag = 1;
			break;
		}
	if (!flag) id[++N] = m - 1;
	int NN = 0;
	for (int i = 1, j; i <= N; i = j + 1)
	{
		j = i;
		int ymax = Y(id[i]);
		while (j < N && s[id[j + 1] - 1] == s[id[i] - 1])
		{
			j++;
			ymax = max(ymax, Y(id[j]));
		}
		p[++NN] = Vector(s[id[i] - 1], ymax);
	}
	
	stk[top = 1] = p[1];
	REP(i, 2, NN)
	{
		while (top > 1 && (p[i] - stk[top]) * (stk[top - 1] - stk[top]) > 0) top--;
		stk[++top] = p[i];
	}

	int j = 1;
	REP(I, 1, tN)
	{
		int i = todo[I].first;
		while (j < top && (stk[j + 1].y - stk[j].y) >= s[i] * (stk[j + 1].x - stk[j].x)) j++;
		int sj = stk[j].x, gj = stk[j].y - M * sj;
		*todo[I].second = gj + (M - sj) * (s[i] - M);
	}
}

signed main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();
	REP(i, 1, n) s[i] = s[i - 1] + (a[i] = read<int>());
	tN = n;
	REP(i, 1, n) todo[i] = make_pair(i, f + i);
	sort(todo + 1, todo + 1 + n, [&](pair <int, int*> x, pair <int, int*> y) {return s[x.first] > s[y.first];});
	REP(i, 1, n) X[i] = s[i - 1];
	int ans = 0;
	REP(i, 2, n)
	{
		REP(j, 1, i - 1) g[j] = dp[j][i - 1];
		solve(i);
		REP(j, i, n) dp[i][j] = f[j];
		chkmax(ans, f[n]);
	}
	cout << ans << endl;
	return 0;
}
