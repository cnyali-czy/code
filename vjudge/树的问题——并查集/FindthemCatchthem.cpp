#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>

using namespace std;
const int maxn = 100000 + 10;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int m, n, k;

int f[maxn];
int find(int x) {return f[x] == x ? x : f[x] = find(f[x]);}
inline void uni(int x, int y) {f[find(x)] = find(y);}
inline bool judge(int x, int y) {return find(x) == find(y);}

int cet[maxn];
map< pair<int, int> , bool> _not;

int main()
{
#ifdef CraZYali
	freopen("FindthemCatchthem.in", "r", stdin);
	freopen("FindthemCatchthem.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		n = read<int>();
		m = read<int>();

		_not.clear();
		REP(i, 1, n) f[i] = i;
		memset(cet, 0, sizeof(cet));
		
		while (m --> 0)
		{
			register char c = getchar();
			while (c ^ 'D' && c ^ 'A') c = getchar();
			register int x(read<int>()), y(read<int>());
			if (c == 'A')
				if (_not[make_pair(x, y)]) printf("In different gangs.\n");
				else if (judge(x, y)) printf("In the same gang.\n");
				else printf("Not sure yet.\n");
			else
			{
				_not[make_pair(x, y)] = _not[make_pair(y, x)] = 1;
				if (cet[x]) uni(cet[x], y);
				else cet[x] = y;
				if (cet[y]) uni(x, cet[y]);
				else cet[y] = x;
			}
		}
	}

	return 0;
}
