#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
#define For(i,a,b) for(i=(a),i<=(b);++i)
#define Forward(i,a,b) for(i=(a),i>=(b);--i)
template<typename T>inline void read(T &x)
{
	T f=1;x=0;char c;
	for(c=getchar();!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=x*10+(c^48);
	x*=f;
}
using namespace std;

const int MAXN=2e5+7,mod=1e9;

static int n=100,m=1000,q=100,k=1e4;

static int p[MAXN],vis[MAXN],poi[MAXN],ss[MAXN],sp[MAXN],tp;

static vector<int>E[MAXN];

static map<unsigned long long,bool>Q;

int main()
{
	freopen("road1.in","w",stdout);
	cout<<n<<' '<<m<<' '<<q<<endl;
	Rep(i,1,n)p[i]=i;
	srand(time(NULL));
	random_shuffle(p+1,p+n+1);
	Rep(i,1,n-1)cout<<'-'<<p[i+1]<<" -"<<p[rand()*rand()%i+1]<<endl;
	static int l,r;
	Rep(i,n,m)
	{
		l=rand()*rand()%n+1;r=rand()*rand()%n+1;
		while(l==r)r=rand()*rand()%n+1;
		cout<<'-'<<l<<" -"<<r<<endl;
	}
	/*cout<<n<<' '<<n+k-1<<' '<<q<<endl;
	Rep(i,1,n+k)p[i]=i;
	srand(time(NULL));
	random_shuffle(p+1,p+n+k+1);
	static int u;
	Rep(i,1,n+k-1)
	{
		E[p[i+1]].push_back(u=p[rand()*rand()%i+1]);
		E[u].push_back(p[i+1]);
	}
	Rep(i,1,n+k-1)if(E[i].size()<=2)ss[i]=1;
	static int pre;
	Rep(i,1,k)
	{
		cerr<<i<<endl;
		do{u=rand()*rand()%n+1;}while(vis[u]||ss[u]);
		vis[u]=poi[u]=true;
		pre=0;
		for(int v:E[u])
		{
			if(pre)E[v].push_back(pre);
			vis[v]=true;pre=v;
		}
		E[E[u][0]].push_back(pre);
	}

	Rep(i,1,n+k)if(!poi[i])sp[i]=++tp;

	static int l,r;

	Rep(i,1,n+k)if(!poi[u=p[i]])for(int v:E[u])if(!poi[v])
	{
		//if(!sp[u])cout<<'-'<<u<<" -"<<poi[u]<<' '<<vis[u]<<endl;
		//if(!sp[v])cout<<'-'<<v<<" -"<<poi[v]<<' '<<vis[v]<<endl;
		l=min(u,v);r=max(u,v);
		if(Q[(unsigned long long)l*n+r])continue;
		Q[(unsigned long long)l*n+r]=true;
		printf("-%d -%d\n",sp[u],sp[v]);
	}*/
	Rep(i,1,n)cout<<rand()*rand()%mod+1<<' ';cout<<endl;
	Rep(i,1,q)cout<<rand()*rand()%n+1<<' ';cout<<endl;
	return 0;
}

