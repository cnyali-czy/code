#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 5e4 + 10;
template <typename T> T read()
{
	T ans(0), p(1);
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

int n, q, a[maxn];

list <int> L;
list <int> :: iterator it;

inline void add(int d)
{
	REP(i, 1, d)
		if (it == L.end()) return;
		else it++;
}

int main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	q = read<int>();
	int l, r;
	while (q--)
	{
		l = read<int>();r = read<int>();
		int ans = 1;
		L.clear();
		REP(i, l, r) L.push_back(a[i]);
		ans++;
		int _chosed = 0, chosei = 1, __max = -1;
		REP(i, 1, L.size())
		{
			int _max = -1, chosed;
			list <int> :: iterator itttt;
			itttt = L.begin();
			REP(j, 2, i) itttt++;
			REP(d, 1, L.size() - i)
			{
				int now = *itttt, res = 0;
				for (it = itttt; it != L.end(); add(d))
					if (*it != now) break;
					else res++;
				if (res > _max) {_max = res;chosed = d;}
			}
			if (_max > __max) {chosei = i;_chosed = chosed;__max = _max;}
			else if (_max == __max && chosed < _chosed) {_chosed = chosed;chosei = i;}
		}
		for (it = L.begin(), add(chosei - 1); it != L.end(); add(_chosed))
			if (it != L.end()) L.erase(it);
		set <int> s;
		s.clear();
		for (it = L.begin(); it != L.end(); it++) s.insert(*it);
		printf("%d\n", ans + s.size());
	}
	return 0;
}
