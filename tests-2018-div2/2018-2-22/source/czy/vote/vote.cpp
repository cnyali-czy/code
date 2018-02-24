#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;

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

int n, k;
set <int> S;
set <int> :: iterator it;
map <int, int> cnt;
vector <int> v;

int main()
{
	freopen("vote.in", "r", stdin);
	freopen("vote.out", "w", stdout);
	n = read<int>();
	REP(i, 1, n)
	{
		S.insert(k = read<int>());
		cnt[k]++;
	}
	for (it = S.begin(); it != S.end(); it++)
		if (cnt[*it] > n / 4) 
			v.push_back(*it);
	if (v.size())
	{
		int siz = v.size() - 1;
		REP(i, 0, siz) printf("%d%c", v[i], i ^ siz ? ' ' : '\n');
	}
	else printf("No such person.\n");
	return 0;
}
