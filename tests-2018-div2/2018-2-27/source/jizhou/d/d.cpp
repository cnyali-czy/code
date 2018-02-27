#include<bits/stdc++.h>
using namespace std;
const int maxn = 777 + 10, maxm = 33333 + 10;

int n, m;
int b[maxn], c[maxn];
int a[maxn][maxn];
int ans = 2147483647;
bool p[maxn];

void search(int pos, int t){
	if(pos == n){
		ans = min(ans, t);
		return;
	} 
	for(int i = 1; i <= n; i++){
		if(i == pos || p[i] || a[pos][i] == -1) continue;
		p[i] = true;
		if(i == n) search(i, t + a[pos][i]);
		else{
			int asdf = b[i] + c[i];
			int tmp = (t + a[pos][i]) % asdf;
			if(tmp <= c[i]) search(i, t + a[pos][i]);
			else search(i, t + a[pos][i] + (asdf - tmp));
		}
		p[i] = false;
	}
}

int main(){
	freopen("d.in", "r", stdin);
	freopen("d.out", "w", stdout);
	memset(a, -1, sizeof(a));
	scanf("%d", &n);
	if(n == 0){
		printf("0");
		return 0;
	}
	for(int i = 0; i < n; i++) scanf("%d%d", &b[i], &c[i]);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++){
		int t, x, y;
		scanf("%d%d%d", &x, &y, &t);
		a[x][y] = a[y][x] = t;
	}
	search(0, 0);
	printf("%d", ans);
	return 0;
}

