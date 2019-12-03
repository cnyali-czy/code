#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#define int long long

using namespace std;
const int maxn = 5e5 + 10;

int bg[maxn], ne[maxn], to[maxn], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int n, ans;
char s[maxn];
int st[maxn * 3], *stack = st + (int)(1.5 * maxn);
int top;

void dfs(int x, int res = 0)
{
	int tmp(0);
	if (s[x] == '(')
	{
		++stack[top];
		swap(stack[++top],tmp);
//		tmp=stack[++top];s
//		stack[++top] = 0;
	}
	else
	{
		stack[top]--;
		res += stack[--top];
	}
	ans ^= x * res;
	for (int i = bg[x]; i; i = ne[i])
		dfs(to[i], res);
	if (s[x] == '(') swap(stack[top],tmp),top--,stack[top]--;//stack[--top]--;
	else stack[++top]++;
}

signed main()
{
#ifdef CraZYali
	file("5658");
#endif
	cin >> n;
	scanf("%s", s + 1);
	REP(i, 2, n) add(read<int>(), i);
	dfs(1);
	cout << ans << endl;
	return 0;
}
