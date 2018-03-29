/*------------------------------------------------------|
|   Copyright (C) 2018 All rights reserved.
|   
|   Filename:1120.cpp
|   Author  :CraZYali
|   Date    :2018年03月25日 星期日 18时58分21秒
|
|*-----------------------------------------------------*/
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100;

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

int m, n, k, sum, Min = 100, Max = -1;
int cnt[maxn];

void dfs(int need, int target, int already, int now)
{
	if (!need)
	{
		cout << target;
		exit(0);
	}
	if (already == target) dfs(need - 1, target, 0, Max);
	DREP(i, now, Min)
		if (cnt[i] && i + already <= target)
		{
			cnt[i]--;
			dfs(need, target, i + already, i);
			cnt[i]++;
			if (!already || i + already == target) break;
		}
}

int main()
{
#ifdef CraZYali
	freopen("1120.in", "r", stdin);
	freopen("1120.out", "w", stdout);
#endif
	m = read<int>();	
	while (m --> 0)
	{
		k = read<int>();
		if (k <= 50)
		{
			chkmin(Min, k);
			chkmax(Max, k);
			sum += k;
			cnt[k]++;
		}
	}
	REP(i, Min, sum >> 1)
		if (sum % i == 0) dfs(sum / i, i, 0, Max);
	cout << sum;
	return 0;
}
