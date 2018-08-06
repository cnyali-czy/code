#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

typedef long long LL;

const int N = 1e6 + 10, K = 105;
const int Mod = 1e9 + 7;
const LL LIM = 7e18;

int sz;

struct Matrix {

	LL A[K][K];

	Matrix (int id = 0) {
		memset(A, 0, sizeof A);
		if (id) For(i, 1, sz) A[i][i] = 1;
	}

	LL* operator[] (int x) { return A[x]; }

	Matrix operator * (Matrix B) {
		Matrix C;
		For(i, 1, sz) For(k, 1, sz) For(j, 1, sz) {
			C[i][j] += A[i][k] * B[k][j];
			if (C[i][j] >= LIM) C[i][j] %= Mod;
		}
		For(i, 1, sz) For(j, 1, sz) C[i][j] %= Mod;
		return C;
	}

	Matrix operator ^ (LL e) {
		Matrix ret(1), x = *this;
		while (e) {
			if (e & 1) ret = ret * x;
			x = x * x;
			e >>= 1;
		}
		return ret;
	}

}tr, ans;

int A[N], dp[N], rk[N];

bool cmp(int x, int y) {
	return dp[x] < dp[y];
}

int n, k;
LL m;
int coe[N];

int main() {

	scanf("%d%lld%d", &n, &m, &k);
	For(i, 1, n) scanf("%d", &A[i]);

	int sum = 0;
	For(i, 1, n) {
		int tmp = sum;
		sum = (Mod + 2ll * sum + 1 - dp[A[i]]) % Mod;
		dp[A[i]] = (tmp + 1) % Mod;
	}

	For(i, 1, k) rk[i] = i;
	sort(rk + 1, rk + k + 1, cmp);
	For(i, 1, k) ans[1][i] = dp[rk[i]];
	ans[1][k + 1] = 1;
	sz = k + 1;

	For(i, 1, k) {
		memset(coe, 0, sizeof coe);
		coe[i] = 1;
		sum = 1;
		For(j, 1, k) {
			int tmp = sum;
			sum = (Mod + 2ll * sum - coe[j]) % Mod;
			coe[j] = tmp;
		}
		For(j, 1, k) tr[i][j] = coe[j];
	}

	memset(coe, 0, sizeof coe);
	sum = 0;
	For(i, 1, k) {
		int tmp = sum;
		sum = (Mod + 2ll * sum - coe[i] + 1) % Mod;
		coe[i] = (tmp + 1) % Mod;
	}
	For(i, 1, k) tr[sz][i] = coe[i];
	tr[sz][sz] = 1; 

	ans = ans * (tr ^ (m / k));
	sum = 0;
	For(i, 1, k) dp[i] = ans[1][i], sum = (sum + dp[i]) % Mod;
	For(i, 1, m % k) {
		int tmp = sum;
		sum = (Mod + 2ll * sum - dp[i] + 1) % Mod;
		dp[i] = (tmp + 1) % Mod;
	}
	printf("%d\n", sum);

	return 0;
}
