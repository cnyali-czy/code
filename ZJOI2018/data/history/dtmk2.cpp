#include <bits/stdc++.h>
using namespace std;
const int N=500000;
int n=10,father[N],a[N],w[N];
vector<pair<int,int> >b;
int main(){
	printf("%d %d\n",n,0);
	for (int i=2;i<=n;i++) father[i]=rand()%(i-1)+1;
	for (int i=1;i<=n;i++) w[i]=1,a[i]=i;
	for (int i=1;i<=n;i++){
		printf("%d",w[i]);
		if (i==n) puts(""); else putchar(' ');
	}
	for (int i=1;i<=n;i++) random_shuffle(a+2,a+n+1);
	for (int i=2;i<=n;i++) b.push_back(make_pair(a[i],a[father[i]]));
	random_shuffle(b.begin(),b.end());
	for (int i=0;i<b.size();i++){
		int k1=b[i].first,k2=b[i].second;
		if (rand()&1) swap(k1,k2);
		printf("%d %d\n",k1,k2);
	}
	return 0;
}
