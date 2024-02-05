#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007
//---------------------------------------------------------------------------------

/* DSU on tree  nlog^2(n)*/
ll n;
ll val[100100];
vector<ll> g[100100];
set<ll> cols[100100];
ll ans[100100];

ll merge(ll a,ll b){
	if(cols[a].size()<cols[b].size())swap(a,b);
	for(auto v:cols[b])cols[a].insert(v);
		cols[b].clear();
	return a;
}

ll dfs(ll nn,ll pp){
	ll cur_set = val[nn];
	for(auto v:g[nn]){
		if(v!=pp){
			cur_set=merge(cur_set,dfs(v,nn));
		}
	}
	ans[nn]=cols[cur_set].size();
	return cur_set;
}

/*cols[i].insert(x)  val[i]=i*/



// -------------------------------------------------

const int N = 1e5 + 9;
vector<int> g[N];
int ans[N], col[N], sz[N], cnt[N];
bool big[N];
void dfs(int u, int p) {
  sz[u] = 1;
  for (auto v : g[u]) {
    if (v == p) continue;
    dfs(v, u);
    sz[u] += sz[v];
  }
}
void add(int u, int p, int x) {
  cnt[col[u]] += x;
  for (auto v : g[u]) {
    if (v == p || big[v] == 1) continue;
    add(v, u, x);
  }
}
void dsu(int u, int p, bool keep) {
  int bigchild = -1, mx = -1;
  for (auto v : g[u]) {
    if (v == p) continue;
    if (sz[v] > mx) mx = sz[v], bigchild = v;
  }
  for (auto v : g[u]) {
    if (v == p || v == bigchild) continue;
    dsu(v, u, 0);
  }
  if (bigchild != -1) dsu(bigchild, u, 1), big[bigchild] = 1;
  add(u, p, 1);
  ans[u] = cnt[u];
  if (bigchild != -1) big[bigchild] = 0;
  if (keep == 0) add(u, p, -1);
}
