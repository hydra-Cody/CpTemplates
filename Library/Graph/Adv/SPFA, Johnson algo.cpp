#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//---------------------------------------------------------------------------------
/*
  SPFA
*/
//Modefied bellman in O(nm)
const ll N = 5050;
vector<pair<ll, ll>> g[N];
bool vis[N];
ll d[N];
bool spfa(ll u) {
  vis[u] = 1;
  for(auto e: g[u]) {
    ll w = e.second, v = e.first;
    if(d[u] + w < d[v]) {
      if(vis[v]) return 0;
      d[v] = d[u] + w;
      if(!spfa(v)) return 0;
    }
  }
  vis[u] = 0;
  return 1;
}

void spfa1(){
    ll n, m;
    cin >> n >> m;
    for(ll i = 0; i <= n; i++) g[i].clear();
    ll ans = 1e9;
    for(ll i = 1; i <= m; i++) {
      ll u, v, w; cin >> u >> v >> w;
      g[u].push_back({v, w});
      ans = min(ans, w);
    }
    if(ans >= 0) {
      cout << ans << '\n';
      return;
    }
    for(ll i = 1; i <= n; i++) g[0].push_back({i, 0});
    for(ll i = 0; i <= n; i++) d[i] = 1e10, vis[i] = 0;
    ll s = 0;
    d[s] = 0;
    if(spfa(s) == 0) cout << "-inf\n"; // negative cycle
    else {
      ll ans = d[1];
      for(ll i = 1; i <= n; i++) ans= min(ans, d[i]);
      cout << ans << '\n';
    }
}

// https://codeforces.com/gym/101498/problem/L


//---------------------------------------------------------------------------
/*
  Johnson's algorithm for all pair shortest paths with negative edges
  ->very similar to the Floyd-Warshall algorithm
  ->effective for sparse graphs (few edges)
  ->Complexity: O(N * M) + O(N * M * log(N))
*/

const int N = 1010;

const long long INF = 1e18;

struct edge {
  int u, v;
  long long w;
  edge(){}
  edge(int u, int v, long long w) : u(u), v(v), w(w){}
};

bool bellman_ford(int n, int s, vector <struct edge> ed, vector <long long> &d){
  d[s] = 0;
  for (int i = 0; i <= n; i++){
    int flag = 0;
    for (auto e: ed){
      if (d[e.u] + e.w < d[e.v]){
        flag = 1;
        d[e.v] = d[e.u] + e.w;
      }
    }
    if (flag == 0) return 1;
  }
  return 0;
}

vector <long long> dijkstra(int n, int s, vector <struct edge> ed, vector <long long> &h){
  vector <pair<int, long long> > g[n + 1];
  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
  for (auto e: ed){
    g[e.u].push_back({e.v, e.w + h[e.u] - h[e.v]});
  }
  vector <long long> d(n + 1, INF);vector<bool> vis(n + 1, 0);
  q.push({0, s});
  d[s] = 0;
  while(!q.empty()){
    auto x = q.top(); q.pop();
    int u = x.second;
    if(vis[u]) continue; vis[u] = 1;
    for(auto e: g[u]){
      int v = e.first; long long w = e.second;
      if(d[u] + w < d[v]){
        d[v] = d[u] + w; q.push({d[v], v});
      }
    }
  }
  for(int i = 1; i <= n; i++) if(d[i] < INF) d[i] -= h[s] - h[i];
  return d;
}

long long ans[N][N];
int johnson(int n, vector <struct edge> ed){
  vector <long long> potential(n + 1, INF);
  for (int i = 1; i <= n; i++) ed.push_back(edge(0, i, 0));
  if(bellman_ford(n, 0, ed, potential) == 0) return 0;
  cout << "yes\n\n";
  for(int i = 1; i <= n; i++){
    if(i > 1) cout << ' ';
    cout << potential[i];
  }
  cout << ' ' << potential[0] << "\n\n";
  for (int i = 1; i <= n; i++) ed.pop_back();
  for (int i = 1; i <= n; i++){
    vector <long long> d = dijkstra(n, i, ed, potential);
    for (int j = 1; j <= n; j++) ans[i][j] = d[j];
  }
  return 1;
}