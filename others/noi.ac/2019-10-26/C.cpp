/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.26 15:09
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;
const int maxn = 5e5 + 10;

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

priority_queue <long long, vector<long long>, greater<long long> > q;
int n;
struct qaq
{
	long long v, w;
	inline bool operator < (const qaq &B) const {return w < B.w;}
}a[maxn];

bool flag;
long long sum, s, ans(-1);
inline void add(long long v, long long w)
{
	q.push(v);
	sum += v;
	s++;
	if (sum >= w)
	{
		long long tmp(0);
		while(sum >= w)
		{
			s--;
			tmp = q.top();
			sum -= tmp;
			q.pop();
		}
		q.push(tmp);
		sum += tmp;
		s++;
		ans = s;
		flag = 1;
	}
}
inline void dda(long long v, long long w)
{
	long long tmp = q.top();
	if (tmp < v)
	{
		sum -= tmp - v;
		q.pop();
		q.push(v);
	}
	if (sum >= w)
	{
		while (sum >= w)
		{
			tmp = q.top();
			sum -= tmp;
			ans--;
			q.pop();
		}
		q.push(tmp);
		sum += tmp;
		ans++;
	}
}
int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n;
	REP(i, 1, n)
	{
		register long long x(read<long long>()), y(read<long long>());
		a[i] = qaq{x, x + y};
	}
	sort(a + 1, a + 1 + n);
	REP(i, 1, n) if (a[i].v)
		if (!flag) add(a[i].v, a[i].w);
		else dda(a[i].v, a[i].w);
	cout << ans << endl;
	return 0;
}
