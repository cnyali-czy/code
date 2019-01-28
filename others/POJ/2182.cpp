
#include <stdio.h>
int s[100000], ans[100000];
struct seg{
	int l, r;
	int len;
}cow[100000];

void build(int v, int l, int r)
{
	cow[v].l = l;
	cow[v].r = r;
	cow[v].len = r - l + 1;
	if (l == r){
		return;
	}
	int mid = (l + r) / 2;
	build(v * 2, l, mid);
	build(v * 2 + 1, mid + 1, r);
}
int query(int v, int k)
{
	--cow[v].len;//长度减一
	if (cow[v].l == cow[v].r){ //找到叶子节点, 注意此处不可用cow[v].len == 0代替，否则单支情况将直接返回，导致未达到最末端
		return cow[v].r;
	}
	else if (cow[v * 2].len >= k){
		return query(v * 2, k);
	}
	else{
		return query(v * 2 + 1, k - cow[v * 2].len);
	}
}
int main()
{
	int n;
	while (~scanf("%d", &n))
	{
		for (int i = 2; i <= n; ++i)
		{
			scanf("%d", &s[i]);
		}
		s[1] = 0;
		build(1, 1, n);
		//从后往前, 对每个s[i] 的值表示此牛在剩余序列中排在第s[i] + 1
		for (int i = n; i >= 1; --i){
			ans[i] = query(1, s[i] + 1);
		}
		for (int i = 1; i <= n; ++i){
			printf("%d\n", ans[i]);
		}
	}
}
