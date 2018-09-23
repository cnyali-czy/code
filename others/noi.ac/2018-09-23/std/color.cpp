#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
const int N=500005;

int n,m,k,T,ans[N],a[N];
vector<int> p[N];int pos[N];

struct aa
{
	int l,r,id;
}t[N];

bool cmp(const aa &x,const aa &y) 
{
	return x.r<y.r;
}

int s[N];
void add(int p,int x) 
{
	for (int i=p;i;i-=i&-i) s[i]+=x;
}

int query(int p) 
{
	int ans=0;
	for (int i=p;i<=n;i+=i&-i) ans+=s[i];
	return ans;
}


int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	
	scanf("%d%d%d%d",&n,&m,&k,&T);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]),p[a[i]].push_back(i);

	for (int i=1;i<=m;i++) scanf("%d%d",&t[i].l,&t[i].r),t[i].id=i;
	sort(t+1,t+m+1,cmp);
	
	int now=0;
	for (int i=1;i<=n;i++)
	{
		int c=a[i];
		if (pos[c]-T-1>=0) add(p[c][pos[c]-T-1],1);

		if (pos[c]-T>=0) add(p[c][pos[c]-T],-2);

		if (pos[c]-T+1>=0) add(p[c][pos[c]-T+1],1);

		for (;t[now+1].r==i;) 
		{
			now++;
			ans[t[now].id]=query(t[now].l);
		}
		pos[c]++;
	}
	for (int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
