#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007

//---------------------------------------------------------------------------------
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