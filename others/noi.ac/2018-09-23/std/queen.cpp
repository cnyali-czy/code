#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int N=100005;

int n,m,t[10],x[N],y[N],cnt[N];
int mxr[N],mir[N],mxc[N],mic[N],mxa[N*2],mia[N*2],mxb[N*2],mib[N*2];


int main()
{
	freopen("queen.in","r",stdin);
	freopen("queen.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	memset(mir,0x3f,sizeof(mir));
	memset(mic,0x3f,sizeof(mic));
	memset(mia,0x3f,sizeof(mia));
	memset(mib,0x3f,sizeof(mib));

	for (int i=1;i<=m;i++) 
	{
		scanf("%d%d",&x[i],&y[i]);
		mxr[x[i]]=max(mxr[x[i]],y[i]);
		mir[x[i]]=min(mir[x[i]],y[i]);

		mxc[y[i]]=max(mxc[y[i]],x[i]);
		mic[y[i]]=min(mic[y[i]],x[i]);
		
		mxa[x[i]-y[i]+N]=max(mxa[x[i]-y[i]+N],x[i]);
		mia[x[i]-y[i]+N]=min(mia[x[i]-y[i]+N],x[i]);

		mxb[x[i]+y[i]]=max(mxb[x[i]+y[i]],x[i]);
		mib[x[i]+y[i]]=min(mib[x[i]+y[i]],x[i]);
	}
	
	for (int i=1;i<=m;i++)
	{
		if (mxr[x[i]]!=y[i]) cnt[i]++;
		if (mir[x[i]]!=y[i]) cnt[i]++;

		if (mxc[y[i]]!=x[i]) cnt[i]++;
		if (mic[y[i]]!=x[i]) cnt[i]++;
		
		if (mxa[x[i]-y[i]+N]!=x[i]) cnt[i]++;
		if (mia[x[i]-y[i]+N]!=x[i]) cnt[i]++;
		
		if (mxb[x[i]+y[i]]!=x[i]) cnt[i]++;
		if (mib[x[i]+y[i]]!=x[i]) cnt[i]++;

		t[cnt[i]]++;
	}
	for (int i=0;i<=8;i++) printf("%d ",t[i]);
	return 0;
}
