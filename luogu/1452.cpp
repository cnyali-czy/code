/*
 * File Name:	1452.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.22 17:19
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

using namespace std;
const int maxn = 50000 + 10;

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

struct vector
{
	int x, y;
	vector(int x = 0, int y = 0) : x(x), y(y) {}
	inline vector operator - (vector B) {return vector(x - B.x, y - B.y);}
	inline int operator * (vector B) {return x * B.y - y * B.x;}
}p[maxn], s[maxn];
inline bool cmp(vector A, vector B)
{
	int tmp = (A - p[1]) * (B - p[1]);
	if (tmp > 0) return 1;
	if (tmp < 0) return 0;
	return A.x < B.x || A.x == B.x && A.y < B.y;
}
inline int dist(vector A, vector B) {return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);}
int n, top, ans;

int main()
{
#ifdef CraZYali
	file("1452");
#endif
	cin >> n;
	REP(i, 1, n)
	{
		int x(read<int>()), y(read<int>());
		p[i] = vector(x, y);
		if (y < p[1].y || y == p[1].y && x < p[1].x) swap(p[i], p[1]);
	}
	srand(time(0));
	random_shuffle(p + 2, p + 1 + n);
	sort(p + 2, p + 1 + n, cmp);
	s[++top] = p[1];
	s[++top] = p[2];
	REP(i, 3, n)
	{
		while (top >= 2 && (s[top] - s[top-1]) * (p[i] - s[top]) <= 0) top--;
		s[++top] = p[i];
	}
	n = top;
	s[n + 1] = s[1];
	int j = 2;
	REP(i, 1, n)
	{
		while (abs((s[j] - s[i]) * (s[i + 1] - s[i])) < abs((s[j + 1] - s[i]) * (s[i + 1] - s[i])))
		{
			j++;
			if (j == n + 1) j = 1;
		}
		chkmax(ans, dist(s[j], s[i]));
		chkmax(ans, dist(s[j], s[i+1]));
	}
#ifdef CraZYali
	REP(i, 1, n) printf("%d %d\n", s[i].x, s[i].y);
#endif
	cout << ans << endl;
	return 0;
}
