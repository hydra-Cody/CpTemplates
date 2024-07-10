#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//---------------------------------------------------------------------------
/* Lowest Common Ancestor-LCA (Binary Lifting) */

const ll N = 3e5 + 9, LG = 18;
vector<ll> g[N];
ll par[N][LG + 1], dep[N], sz[N];
void dfs(ll u, ll p = 0) {
  par[u][0] = p;
  dep[u] = dep[p] + 1;
  sz[u] = 1;
  for (ll i = 1; i <= LG; i++) {
    par[u][i] = par[par[u][i - 1]][i - 1];
  }
  for (auto v: g[u]){ 
    if (v != p) {
      dfs(v, u);
      sz[u] += sz[v];
    }
  }
}
ll lca(ll u, ll v) {
  if (dep[u] < dep[v]){ 
    swap(u, v);
  }
  for (ll k = LG; k >= 0; k--){
   if (dep[par[u][k]] >= dep[v]){
    u = par[u][k];
  }
}
  if (u == v){
   return u;
 }
  for (ll k = LG; k >= 0; k--){
    if (par[u][k] != par[v][k]){ 
      u = par[u][k];
      v = par[v][k];
    }
  }
  return par[u][0];
}
ll kth(ll u, ll k) {
  assert(k >= 0);
  for (ll i = 0; i <= LG; i++){
    if (k & (1 << i)){
      u = par[u][i];
    }
  }
  return u;
}
ll dist(ll u, ll v) {
  ll l = lca(u, v);
  return dep[u] + dep[v] - (dep[l] << 1);
}
//kth node from u to v, 0th node is u
ll go(ll u, ll v, ll k) {
  ll l = lca(u, v);
  ll d = dep[u] + dep[v] - (dep[l] << 1);
  assert(k <= d);
  if (dep[l] + k <= dep[u]) return kth(u, k);
  k -= dep[u] - dep[l];
  return kth(v, dep[v] - dep[l] - k);
}



//----------------------------------------------------------------------------------------
/*
  LCA in O(1)
*/

#include<bits/stdc++.h>
using namespace std;

template <class T>
struct RMQ { // 0-based
  vector<vector<T>> rmq;
  T kInf = numeric_limits<T>::max();
  void build(const vector<T>& V) {
    int n = V.size(), on = 1, dep = 1;
    while (on < n) on *= 2, ++dep;
    rmq.assign(dep, V);
 
    for (int i = 0; i < dep - 1; ++i)
      for (int j = 0; j < n; ++j) {
        rmq[i + 1][j] = min(rmq[i][j], rmq[i][min(n - 1, j + (1 << i))]);
      }
  }
  T query(int a, int b) { // [a, b)
    if (b <= a) return kInf;
    int dep = 31 - __builtin_clz(b - a); // log(b - a)
    return min(rmq[dep][a], rmq[dep][b - (1 << dep)]);
  }
};

struct LCA { // 0-based
  vector<int> enter, depth, exxit;
  vector<vector<int>> G;
  vector<pair<int, int>> linear;
  RMQ<pair<int, int>> rmq;
  int timer = 0;
  LCA() {} 
  LCA(int n) : enter(n, -1), exxit(n, -1), depth(n), G(n), linear(2 * n) {}
  void dfs(int node, int dep) {
    linear[timer] = {dep, node};
    enter[node] = timer++;
    depth[node] = dep;
    for (auto vec : G[node])
    if (enter[vec] == -1) {
      dfs(vec, dep + 1);
      linear[timer++] = {dep, node};
    }
    exxit[node] = timer;
  }
  void add_edge(int a, int b) {
    G[a].push_back(b);
    G[b].push_back(a);
  }
  void build(int root) {
    dfs(root, 0);
    rmq.build(linear);
  }
  int query(int a, int b) {
    a = enter[a], b = enter[b];
    return rmq.query(min(a, b), max(a, b) + 1).second;
  }
  int dist(int a, int b) {
    return depth[a] + depth[b] - 2 * depth[query(a, b)];
  }
};
 
LCA lca;

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  return 0;
}

