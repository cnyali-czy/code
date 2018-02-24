#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

const int N = 185;

int n, m;

struct Matrix {
	
	bool A[N][N];

	Matrix(int x = 0) {
		memset(A, false, sizeof A);
		if (x == 1) For(i, 1, n) A[i][i] = true;
	}

	Matrix operator * (const Matrix &B) const {
		Matrix ret;
		static bitset<N> r[N], c[N];
		For(i, 1, n) For(j, 1, n) r[i][j] = A[i][j], c[i][j] = B.A[j][i];
		For(i, 1, n) if (r[i].any()) 
			For(j, 1, n) ret.A[i][j] = (r[i] & c[j]).any();
		return ret;
	}

	Matrix operator ^ (int e) const {
		Matrix ret(1), x = *this;
		while (e) {
			if (e & 1) ret = ret * x;
			x = x * x;
			e >>= 1;
		}
		return ret;
	}

}now, G;

bool A[N][N][N];
int w[N], c;

int main() {

	scanf("%d%d%d", &n, &m, &c);
	For(i, 1, m) {
		int u, v, k;
		scanf("%d%d%d", &u, &v, &k);
		A[k][u][v] = true;
	}
	For(i, 1, c) scanf("%d", &w[i]);
	
	G.A[n][n] = true;
	now.A[1][1] = true;
	For(i, 0, c) {
		int e = i == c ? n : w[i + 1] - w[i];
		Matrix nxt = now * (G ^ e);
		if (nxt.A[1][n]) {
			For(j, 1, n) {
				now = now * G;
				if (now.A[1][n]) {
					printf("%d\n", j + w[i]);
					return 0;
				}
			}
			assert(false);
		} else if (i == c) {
			puts("Impossible");
			return 0;
		}
		now = nxt;
		For(x, 1, n) For(y, 1, n) G.A[x][y] |= A[i + 1][x][y];
	}

	return 0;
}
