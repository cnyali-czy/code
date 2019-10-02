#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <tr1/unordered_map>

using namespace std;

int n, MOD, an;
vector <vector<int> > t[233];
tr1::unordered_map <long long, int> id;

inline int power_pow(long long base, int b)
{
	long long ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}

inline long long Hash(int v[], int n)
{
	long long w(0);
	REP(i, 1, n)
		w *= (::n / i + 1) + v[n - i];
	return w * (::n + 1) + n;
}
inline long long Hash(vector<int> v)
{
	return Hash(v.data(), v.size());
}
vector <int> v;
void dfs(int d, int s)
{
	if (!s)
	{
		t[v.size()].push_back(v);
		return;
	}
	REP(l, d, s)
	{
		v.push_back(l);
		dfs(l, s - l);
		v.pop_back();
	}
}
int nx[23333], sb[23333];
bool vis[2333];

inline long long get_nx()
{
	REP(i, 1, n) vis[i] = 0;
	int cur(0);
	REP(i, 1, n) if (!vis[i])
	{
		int s(0);
		for (int j(i); !vis[j]; j = nx[j])
			vis[j] = 1, ++s;
		sb[cur++] = s;
	}
	sort(sb, sb + cur);
	return Hash(sb, cur);
}
int mat[2333][2333];
long long ww[23333];

int main()
{
#ifdef CraZYali
	freopen("ball.in", "r", stdin);
	freopen("ball.out", "w", stdout);
#endif
	int Ttt;
	cin >> n >> Ttt >> MOD;
	dfs(1, n);
	REP(i, 1, n)
	{
		sort(t[i].begin(),t[i].end());
		REP(j, 0, (int)t[i].size() - 1)
			id[Hash(t[i][j])] = ++an;
	}
	int pr=0;
	long long r=power_pow(n*(n-1)/2,MOD-2);
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<t[i].size();++j)
		{
			++pr;
			vector<int>& ww=t[i][j];
			int d=id[Hash(ww)];
			if(i==n)
			{
				(--mat[d][d])%=MOD;
				continue;
			}
			int g=0;
			for(int k=0;k<ww.size();++k)
			{
				int x=ww[k];
				for(int j=1;j<=x;++j)
					nx[g+j]=g+j%x+1;
				g+=x;
			}
			for(int p=1;p<=n;++p)
				for(int q=p+1;q<=n;++q)
				{
					swap(nx[p],nx[q]);
					(mat[d][id[get_nx()]]+=r)%=MOD;
					swap(nx[p],nx[q]);
				}
			(--mat[d][d])%=MOD;
			(++mat[d][0])%=MOD;
		}
	}
	for(int i=1;i<=an;++i)
	{
		{
			int G=-1;
			for(int j=i;j<=an;++j)
				if(mat[j][i]%MOD)
				{
					G=j; break;
				}
			if(G!=i)
			{
				for(int j=1;j<=an;++j)
					swap(mat[G][j],mat[i][j]);
			}
		}
		long long w=power_pow(mat[i][i],MOD-2);
		for(int j=0;j<=an;++j)
			mat[i][j]=mat[i][j]*w%MOD;
		int L=i,R=i;
		for(int j=1;j<=an;++j)
			if(mat[i][j]) L=min(L,j),R=max(R,j);
		for(int j=1;j<=an;++j) if(j!=i&&mat[j][i]%MOD)
		{
			long long w=mat[j][i];
			mat[j][0]=(mat[j][0]-mat[i][0]*(long long)w)%MOD;
			for(int p=L;p<=R;++p)
				mat[j][p]=(mat[j][p]-mat[i][p]*(long long)w)%MOD;
		}
	}
	for(int i=1;i<=an;++i)
		ww[i]=-mat[i][0]*power_pow(mat[i][i],MOD-2)%MOD;
	while(Ttt--)
	{
		for(int i=1;i<=n;++i)
			scanf("%d",nx+i);
		long long w=get_nx();
		int d=id[w];
		int aa=ww[d];
		aa=(aa%MOD+MOD)%MOD;
		printf("%d\n",aa);
	}
	return 0;
}
