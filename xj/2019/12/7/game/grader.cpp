#include "game.h"
#include<bits/stdc++.h>

namespace gg {

static const int N = 10005;

static int n, limit, a[N], b[N], times;

void work() {
	scanf("%d %d", &n, &limit);
	for(int i = 0; i < n; i ++) {
		scanf("%d", &a[i]);
		if(!(a[i] >= 1 && a[i] <= n)) {
			printf("The input is invalid.\n");
			assert(a[i] >= 1 && a[i] <= n);
		}
		b[a[i]] = i + 1;
	}
	for(int i = 1; i <= n; i ++) {
		if(!(b[i] != 0)) {
			printf("The input is invalid.\n");
			assert(b[i] != 0);
		}
	}
	std :: vector<int> ans = guess(n, limit);
	if(!(ans.size() == n)) {
		printf("Wrong answer.\n");
		//assert(ans.size() == n);
		exit(0);
	}
	for(int i = 0; i < n; i ++)
		if(!(ans[i] == a[i])) {
			printf("Wrong answer.\n");
			//assert(ans[i] == a[i]);
			exit(0);
		}
	printf("Accepted.\nYou use %d queries\n", times);
}
}

int count(std :: vector<int> c) {
	using namespace gg;
	times ++;
	if(!(times <= limit)) {
		printf("Too many queries.\n");
		//assert(times <= limit);
		exit(0);
	}
	int sum = 0;
	assert(c.size() == n);
	for(int i = 1; i <= n; i ++) b[i] = 0;
	for(int i = 0; i < n; i ++) {
		if(!(c[i] >= 1 && c[i] <= n)) {
			printf("The query is invalid.\n");
			assert(c[i] >= 1 && c[i] <= n);
		}
		sum += c[i] == a[i];
		b[c[i]] = i + 1;
	}
	for(int i = 1; i <= n; i ++) {
		if(!(b[i] != 0)) {
			printf("The query is invalid.\n");
			assert(b[i] != 0);
		}
	}
	return sum;
}

int main() {
	gg :: work();
	return 0;
}
