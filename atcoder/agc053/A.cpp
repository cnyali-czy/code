/*
	Problem:	A.cpp
	Time:		2021-06-30 11:18
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int maxn = 100 + 5;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n;
char s[maxn];
int a[maxn], b[maxn], c[maxn];

inline bool chkmax(int &x, int y) {if (x < y) {x = y;return 1;}return 0;}
bool judge(int mid)
{
	REP(i, 0, n) c[i] = a[i] - (b[i] + mid);
	REP(i, 0, n) if (c[i] < 0) return 0;
	bool flg = 1;
	REP(i, 1, n)
	{
		if (s[i] == '<') flg &= (c[i - 1] < c[i]);
		else flg &= (c[i - 1] > c[i]);
	}
	return flg;
}

int in[maxn];
vector <int> G[maxn];
inline void add(int x, int y)
{
	G[x].emplace_back(y);
	in[y]++;
}
int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	scanf("%s", s + 1);
	REP(i, 0, n) a[i] = read<int>();

	REP(i, 0, n) b[i] = 0;
	REP(i, 1, n) if (s[i] == '<')
		add(i - 1, i);
	else
		add(i, i - 1);
	/*
	REP(i, 1, n) if (s[i] == '<') chkmax(b[i], b[i - 1] + 1);
	DEP(i, n - 1, 0) if (s[i + 1] == '>') chkmax(b[i], b[i + 1] + 1);*/
	static int que[maxn];int head = 0, tail = -1;
	REP(i, 0, n) if (!in[i]) que[++tail] = i;
	while (head <= tail)
	{
		int x = que[head++];
		for (int y : G[x])
		{
			b[y] = max(b[y], b[x] + 1);
			if (!(--in[y])) que[++tail] = y;
		}
	}

	vector <vector <int> > ans;
	while (1)
	{
		int ok = -1;
		REP(i, 0, 1e4) if (judge(i)) {ok = i;break;}
		if (ok == -1) break;
		vector <int> vec(n + 1);
		REP(i, 0, n) vec[i] = b[i] + ok, a[i] -= vec[i];
		ans.emplace_back(vec);
	}
	cout << ans.size() + 1 << endl;
	for (auto vec : ans) REP(i, 0, n) printf("%d%c", vec[i], i == end_i ? '\n' : ' ');
	REP(i, 0, n) printf("%d%c", a[i], i == end_i ? '\n' : ' ' );

	return 0;
}
