#include "game.h"

std :: vector<int> guess(int n, int limit) {
	std :: vector<int> ans;
	ans.resize(n);
	for(int i = 1; i <= n; i ++)
		ans[i - 1] = i;
	return ans;
}
