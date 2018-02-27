#include<bits/stdc++.h>
using namespace std;

int t [1005];
int state[1005][2];
vector<int>to[1005];
vector<int>len[1005];

bool inside[1005];
queue<int>Q;

int main() {
	freopen("d.in","r",stdin);
	freopen("d.out","w",stdout);
	int n;
	cin >> n;
	for(int i = 0; i ^ n; i ++) {
		cin >> state[i][1] >> state[i][0];
		t[i + 1] = 100000005;
	}
	int m;
	cin >> m;
	for(int i = 1; i <= m; i ++) {
		int a,b,v;
		cin >> a >> b >> v;
		to[a].push_back(b);
		to[b].push_back(a);
		len[a].push_back(v);
		len[b].push_back(v);
	}
	Q.push(0);
	while(!Q.empty()) {
		int now = Q.front();
		Q.pop();
		inside[now] = false;
		for(int i = 0; i ^ to[now].size(); i ++) {
			int next = to[now][i];
			int ArrT = t[now] + len[now][i];
			int MinWait;
			if( next == n )MinWait = 0;
			else           MinWait = state[next][0] + state[next][1] - ArrT % ( state[next][0] + state[next][1] );
			if(MinWait >= state[next][1])MinWait = 0;
			if( ArrT + MinWait < t[next] ) {
				t[next] = ArrT + MinWait;
				if(!inside[next])Q.push(next);
				inside[next] = true;
			}
		}
	}
	cout << t[n];
	return 0;
}
