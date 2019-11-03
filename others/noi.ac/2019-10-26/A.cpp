/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.26 13:48
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;
const int maxn = 1e5 + 10, maxm = 3e4 + 10, maxk = 10;

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

int n, m, k;
int a[maxn][maxk];

struct node
{
	int id, n;
	long long v;
	inline bool operator < (const node &B) const {return v > B.v;}
};
priority_queue <node> Q;

inline long long f(int id, int n)
{
	long long res(0);
	DREP(i, k, 0) res = res * n + a[id][i];
	return res;
}
int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> m >> k;
	REP(i, 1, m)
	{
		REP(j, 0, k) a[i][j] = read<int>();
		Q.push(node{i, 1, f(i, 1)});
	}
	while (--n)
	{
		node qaq(Q.top());
		Q.pop();
		qaq.n++;
		qaq.v = f(qaq.id, qaq.n);
		Q.push(qaq);
	}
	cout << Q.top().v << endl;
	return 0;
}
