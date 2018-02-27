#include<bits/stdc++.h>
using namespace std;
const int maxn = 100 + 10, maxm = 10000 + 10;
typedef pair<int, int> asdf;
#define sec second
#define fir first

int tot;
int n, m;
string word[maxn];
map<string, int>a;
map<int, string>b;
int d[maxm][2];
bool p[maxn][maxn];
int ans = -1;

queue<asdf> search(int len, queue<asdf>sen){
	for(int i = 1; i <= m; i++){
		if(p[d[i][0]][d[i][1]]) continue;
		if(len >= 1 && sen.back().sec != d[i][0]) continue;
		p[d[i][0]][d[i][1]] = true;
		sen.push(make_pair(d[i][0], d[i][1]));
		return search(len + 1, sen);
	}
	return sen;
}

int main(){
	freopen("language.in", "r", stdin);
	freopen("language.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		cin >> word[i];
		a[word[i]] = ++tot;
		b[tot] = word[i];
	}
	for(int i = 1; i <= m; i++){
		string s1, s2;
		cin >> s1 >> s2;
		d[i][0] = a[s1];
		d[i][1] = a[s2];
	}
	queue<asdf>lala;
	lala = search(0, lala);
	int len = 0, pd = 0;
	printf("%d\n", lala.size() + 1);
	while(!lala.empty()){
		int t1 = lala.front().fir, t2 = lala.front().sec;
		if(pd == 1) cout << b[t2] << ' ';
		if(!pd) cout << b[t1] << ' ' << b[t2] << ' ', pd = 1;
		lala.pop();
	}
	return 0;
}

