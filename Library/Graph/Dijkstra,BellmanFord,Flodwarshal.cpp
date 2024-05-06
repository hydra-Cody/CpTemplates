#include<bits/stdc++.h>
using namespace std;
#define ll long long 

//-----------------------------------------------------------------------
/*dijkstra 
 ->for single source shortest path to all vertices
 ->used for both directed and undirected graphs
 ->o(e+vlog(v)) 
 ->with no negative edge
*/
const ll N=1e5+10;
ll n,m;
vector<pair<ll,ll>> adj[N];
ll dist[N],vis[N],parent[N];
void dijkstra(ll s)
{  
    set<pair<ll,ll>> pq;
    for(ll i=0; i<n; i++){
        dist[i]=1e15; 
        vis[i]=0;
    }
    dist[s]=0;
    pq.insert({dist[s], s});
    while (!pq.empty()){
        ll u=(*pq.begin()).second;
        pq.erase(*pq.begin());
        if (vis[u]) continue;
        vis[u]=true;
        for(auto p: adj[u]){
            ll v=p.first;
            ll w=p.second;
            if(!vis[v] && dist[u] + w < dist[v]) {
                dist[v] =dist[u] + w;
                parent[v] = u;   
                pq.insert({dist[v], v});
            }
        }
    }
}

//-----------------------------------------------------------------------------------------------
/*Bellmanford 
  ->in case of negative egdes 
  ->used for both directed and undirected graphs
  ->with no negatice weight cycle 
  ->in O(nm)
*/
const ll INF = 2e9;
// const ll N = 3e5 + 9;
struct st {
  ll a, b, cost;
} e[N];
void Bellmanford() {
  ll n, m;
  cin>> n >> m;
  for(ll i = 0; i < m; i++){
    cin >> e[i].a >> e[i].b >> e[i].cost;
  }
  ll s;
  cin>>s;
  vector<int> d (n, INF);
  d[s] = 0;
  vector<int> p (n, -1);
  ll x;
  for(ll i=0; i<n; ++i) {
    x = -1;
    for (ll j=0; j<m; ++j) {
      if (d[e[j].a] < INF) {
        if (d[e[j].b] > d[e[j].a] + e[j].cost) {
          d[e[j].b] = max (-INF, d[e[j].a] + e[j].cost);
          p[e[j].b] = e[j].a;
          x = e[j].b;
        }
      }
    }
  }
  if (x == -1){
    cout << "No negative cycle from ";
  }else {
    ll y = x;
    for (ll i=0; i<n; ++i){
    y = p[y];
    } 
    vector<ll> path;
    for (ll cur=y; ; cur=p[cur]) {
      path.push_back (cur);
      if (cur == y && path.size() > 1) break;
    }
    reverse (path.begin(), path.end());
    cout << "Negative cycle: ";
    for (ll i=0; i<path.size(); ++i){
      cout << path[i] << ' ';
    }
  }

}

//------------------------------------------------------------------------------------
/*Flodwarshal 
  ->for all pair shortest path 
  ->works for both directed and undirected graphs
  ->doesn't work with graphs that have negative cycles. 
  ->V^3
*/
const ll MAX_N = 500 + 1;
// ll n, m, q;
ll dis[MAX_N][MAX_N];
void floyd_warshall() { 
    for (ll k = 1; k <= n; k++){
        for (ll i = 1; i <= n; i++){ 
            for (ll j = 1; j <= n; j++){
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
}


